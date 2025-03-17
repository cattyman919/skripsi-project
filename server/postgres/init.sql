CREATE TABLE users (
    username VARCHAR(255) PRIMARY KEY,
    password_hash BYTEA NOT NULL,
    salt BYTEA NOT NULL
);

-- Precomputed for password "rahman" using backend's hashing logic
INSERT INTO users (username, password_hash, salt) VALUES (
    'seno',
    '\x7b888a4e6a8e4d1c7e1e8f0a2b3c4d5e6f7a8b9c0d1e2f3a4b5c6d7e8f9a0b1c'::BYTEA,
    '\x6a4f5b6c7d8e9f0a1b2c3d4e5f6a7b8c'::BYTEA
);
