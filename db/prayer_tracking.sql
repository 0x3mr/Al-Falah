CREATE TABLE prayer_tracking (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    prayer_name TEXT NOT NULL,
    date TEXT NOT NULL,

    status TEXT DEFAULT 'missed', 
    -- 'prayed', 'missed', 'late'

    prayed_at TEXT, 
    -- actual time user marked it done

    FOREIGN KEY(user_id) REFERENCES users(id)
);