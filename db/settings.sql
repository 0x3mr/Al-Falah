CREATE TABLE user_settings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    adhan_enabled BOOLEAN DEFAULT 1,
    adhan_sound TEXT DEFAULT 'default.mp3',
    FOREIGN KEY (user_id) REFERENCES users(id)
);