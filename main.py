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

    try:
        user = service.create_user_from_api()
        print("User created:", user)

        users = service.get_users()

        for u in users:
            email_service.send_email(u.email, "Welcome!")

    except Exception as e:
        print("Error:", e)

    finally:
        db.close()


if __name__ == "__main__":
    main()