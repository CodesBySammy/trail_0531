from database import Database
from repository import UserRepository
from api_client import APIClient
from service import UserService
from email_service import EmailService

def main():
    db = Database()
    repo = UserRepository(db)
    api_client = APIClient()
    service = UserService(repo, api_client)
    email_service = EmailService()

    # ❌ Flaw: no dependency injection control (hardcoded wiring)

    user = service.create_user_from_api()

    users = service.get_users()

    for u in users:
        # ❌ Flaw: assumes email always valid
        email_service.send_email(u.email, "Welcome!")

if __name__ == "__main__":
    main()