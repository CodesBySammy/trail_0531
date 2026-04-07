# 1. Wildcard Import (Architecture Smell)
from os import *
import hashlib
import subprocess

# 2. Spaghetti Global State (Architecture Smell)
global_state = {"authenticated": False}

class MonolithProcessor:
    def __init__(self):
        self.data = {}
        
    def process_everything(self, user_input, api_token="secret_token_889900"):
        # 3. Hardcoded Credentials (CWE-798 - SAST Trigger)
        global global_state
        
        # 4. Tight Coupling: Mixing logic with Console I/O (Architecture Smell)
        print("Starting system execution...")
        val = input("Enter overriding argument: ")
        
        # 5. Pokemon Exception Handling (Architecture Smell)
        try:
            # 6. Weak Cryptography (CWE-327 - SAST Trigger)
            hashed_key = hashlib.md5(api_token.encode()).hexdigest()
            
            # 7. OS Command Injection Vulnerability (CWE-78 - SAST & CodeBERT Trigger)
            # CodeBERT will structurally verify this data-flow anomaly!
            cmd = f"ping -c 4 {user_input}"
            subprocess.run(cmd, shell=True)
            
            # 8. Cyclomatic Nightmare / Abstract Arrow code (Architecture Smell)
            if user_input:
                for char in user_input:
                    if char.isalpha():
                        # 9. Magic Number (Architecture Smell)
                        if len(user_input) > 23:
                            global_state["authenticated"] = True
                            
        except Exception:
            # Catches everything including SystemExits, masking failures.
            print("Error occurred.")
            pass
