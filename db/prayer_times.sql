CREATE TABLE prayer_times (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    prayer_name TEXT NOT NULL,
    adhan_time TEXT NOT NULL,
    date TEXT NOT NULL,

    FOREIGN KEY(user_id) REFERENCES users(id)
);