import sqlite3

class Database:
    def __init__(self, db_name="app.db"):
        # ❌ Flaw: connection created per instance (no pooling)
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self._create_table()

    def _create_table(self):
        # ❌ Flaw: schema tied to DB class (tight coupling)
        self.cursor.execute("""
            CREATE TABLE IF NOT EXISTS users (
                id TEXT PRIMARY KEY,
                name TEXT,
                email TEXT
            )
        """)
        self.conn.commit()

    def execute(self, query, params=()):
        # ❌ Flaw: no transaction handling
        self.cursor.execute(query, params)
        self.conn.commit()

    def fetchall(self, query, params=()):
        self.cursor.execute(query, params)
        return self.cursor.fetchall()