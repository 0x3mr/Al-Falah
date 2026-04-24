CREATE TABLE prayer_records (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    prayer_name TEXT CHECK(prayer_name IN ('Fajr','Dhuhr','Asr','Maghrib','Isha')),
    prayer_date DATE NOT NULL,
    completed BOOLEAN DEFAULT 0,
    completed_at DATETIME,
    FOREIGN KEY (user_id) REFERENCES users(id),
    UNIQUE(user_id, prayer_name, prayer_date)
);