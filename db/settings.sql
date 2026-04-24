CREATE TABLE user_settings (
    user_id INTEGER PRIMARY KEY,
    adhan_enabled BOOLEAN DEFAULT 1,
    adhan_sound TEXT DEFAULT 'default.mp3',
    FOREIGN KEY (user_id) REFERENCES users(id)
);