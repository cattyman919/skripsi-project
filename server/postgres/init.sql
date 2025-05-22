CREATE TABLE users (
    username VARCHAR(255) PRIMARY KEY,
    password_hash BYTEA NOT NULL,
    salt BYTEA NOT NULL
);
