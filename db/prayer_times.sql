CREATE TABLE prayer_times (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    prayer_name TEXT NOT NULL UNIQUE,
    adhan_time TEXT NOT NULL,
);