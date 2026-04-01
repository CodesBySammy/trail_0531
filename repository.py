from models import User

class UserRepository:
    def __init__(self, db):
        self.db = db

    def save(self, user: User):
        # ❌ Flaw: overwrites silently (no conflict handling)
        self.db.execute(
            "INSERT OR REPLACE INTO users (id, name, email) VALUES (?, ?, ?)",
            (user.id, user.name, user.email)
        )

    def get_all(self):
        rows = self.db.fetchall("SELECT * FROM users")
        
        # ❌ Flaw: assumes fixed DB order blindly
        return [User(row[0], row[1], row[2]) for row in rows]

    def delete(self, user_id: str):
        # ❌ Flaw: no feedback if delete failed
        self.db.execute("DELETE FROM users WHERE id = ?", (user_id,))