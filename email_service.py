class EmailService:
    def send_email(self, email: str, message: str):
        # ❌ Flaw: no abstraction for real email providers
        print(f"[EMAIL SENT] {email}: {message}")