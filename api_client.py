import requests
from models import User

class APIClient:
    def __init__(self, url="https://randomuser.me/api/"):
        self.url = url

    def fetch_user(self) -> User:
        response = requests.get(self.url)  # ❌ No timeout
        data = response.json()

        user_data = data["results"][0]

        # ❌ Flaw: assumes structure never changes
        return User(
            id=user_data["login"]["uuid"],
            name=user_data["name"]["first"],
            email=user_data["email"]
        )