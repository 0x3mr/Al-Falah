CREATE TABLE prayer_times (
    user_id INTEGER NOT NULL,
    prayer_name TEXT CHECK(prayer_name IN ('Fajr','Dhuhr','Asr','Maghrib','Isha')),
    adhan_time TEXT NOT NULL,
    PRIMARY KEY (user_id, prayer_name),
    FOREIGN KEY (user_id) REFERENCES users(id)
);