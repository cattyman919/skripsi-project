package main

import (
	"crypto/rand"
	"crypto/sha256"
	"crypto/subtle"
	"database/sql"
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/gin-gonic/gin"
	_ "github.com/jackc/pgx/v4/stdlib" // Add blank identifier to register driver
	"golang.org/x/crypto/pbkdf2"
)

const (
	iterations = 100000
	keyLength  = 32
)

type LoginRequest struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

var db *sql.DB

func main() {
	// Initialize database connection
	var err error
	db, err = sql.Open("pgx", os.Getenv("DB_CONNECTION"))
	if err != nil {
		log.Fatal("Failed to connect to database:", err)
	}
	defer db.Close()

	router := gin.Default()

	router.POST("/login", loginHandler)
	router.POST("/register", registerHandler)

	fmt.Println("Server running on :9090")
	router.Run(":9090")
}

func loginHandler(c *gin.Context) {
	var req LoginRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
		return
	}

	// Get stored salt and hash
	var storedSalt, storedHash []byte
	err := db.QueryRow(
		"SELECT salt, password_hash FROM users WHERE username = $1",
		req.Username,
	).Scan(&storedSalt, &storedHash)

	if err != nil {
		c.JSON(http.StatusUnauthorized, gin.H{"error": "Invalid credentials"})
		return
	}

	// Generate hash from received password
	generatedHash := pbkdf2.Key(
		[]byte(req.Password),
		storedSalt,
		iterations,
		keyLength,
		sha256.New,
	)

	// Secure comparison
	if subtle.ConstantTimeCompare(storedHash, generatedHash) == 1 {
		c.JSON(http.StatusOK, gin.H{"success": true})
	} else {
		c.JSON(http.StatusUnauthorized, gin.H{"error": "Invalid credentials"})
	}
}

func registerHandler(c *gin.Context) {
	var req struct {
		Username string `json:"username"`
		Password string `json:"password"`
	}

	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
		return
	}

	// Generate random salt
	salt := make([]byte, 16)
	if _, err := rand.Read(salt); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to generate salt"})
		return
	}

	// Generate password hash
	hash := pbkdf2.Key(
		[]byte(req.Password),
		salt,
		iterations,
		keyLength,
		sha256.New,
	)

	// Store in database
	_, err := db.Exec(
		"INSERT INTO users (username, password_hash, salt) VALUES ($1, $2, $3)",
		req.Username, hash, salt,
	)

	if err != nil {
		c.JSON(http.StatusConflict, gin.H{"error": "User already exists"})
		return
	}

	c.JSON(http.StatusCreated, gin.H{"message": "User created"})
}

