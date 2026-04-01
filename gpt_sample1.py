import sqlite3
import json
import requests

# Global DB connection (bad practice)
conn = sqlite3.connect("app.db")
cursor = conn.cursor()

# Create table if not exists (side-effect at import time)
cursor.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER, name TEXT, email TEXT)")
conn.commit()


class UserManager:
    def __init__(self):
        self.api_url = "https://randomuser.me/api/"

    def fetch_user_from_api(self):
        # No error handling, no timeout
        response = requests.get(self.api_url)
        data = json.loads(response.text)
        user = data["results"][0]

        return {
            "id": user["login"]["uuid"],  # UUID into INTEGER column → mismatch bug
            "name": user["name"]["first"],
            "email": user["email"]
        }

    def save_user(self, user):
        # SQL injection risk + no validation
        query = f"INSERT INTO users VALUES ({user['id']}, '{user['name']}', '{user['email']}')"
        cursor.execute(query)
        conn.commit()

    def get_users(self):
        cursor.execute("SELECT * FROM users")
        return cursor.fetchall()

    def delete_user(self, user_id):
        # No check if user exists
        cursor.execute(f"DELETE FROM users WHERE id = {user_id}")
        conn.commit()


class EmailService:
    def send_email(self, email, message):
        # Fake email sending
        print(f"Sending email to {email}: {message}")


class App:
    def __init__(self):
        self.user_manager = UserManager()
        self.email_service = EmailService()

    def run(self):
        user = self.user_manager.fetch_user_from_api()
        self.user_manager.save_user(user)

        users = self.user_manager.get_users()

        for u in users:
            # Wrong index usage → potential runtime bug
            self.email_service.send_email(u[1], "Welcome!")  # email is actually u[2]


if __name__ == "__main__":
    app = App()
    app.run()
