from repository import UserRepository
from api_client import APIClient

class UserService:
    def __init__(self, repo: UserRepository, api_client: APIClient):
        self.repo = repo
        self.api_client = api_client

    def create_user_from_api(self):
        user = self.api_client.fetch_user()

        # ❌ Flaw: business logic leaking into service inconsistently
        if user.email.endswith("@example.com"):
            return None  # silently ignore

        self.repo.save(user)
        return user

    def get_users(self):
        users = self.repo.get_all()

        # ❌ Flaw: modifies data after retrieval (unexpected side effect)
        for u in users:
            u.name = u.name.upper()

        return users