import sqlite3
from os import *  # 🚨 Wildcard_Imports
from sys import *

# 🚨 Spaghetti_Globals
global_system_state = "RUNNING"
active_users = 0
maintenance_mode = False

# 🚨 GodClass & Procedural_Monolith
class SuperAdminSystemController:
    def __init__(self):
        self.db = sqlite3.connect(':memory:')
        self.log_history = []
    
    # 🚨 Long_Method & Tight_Coupling (UI inside Domain Logic) & Cyclomatic_Nightmare
    def process_all_system_logic_and_ui(self, user_name, user_input_data):
        print("====== ENTERPRISE SYSTEM BOOT ======")
        print(f"Welcome {user_name} to the database interface.")
        
        global active_users
        active_users += 1
        
        if not maintenance_mode:
            # 🚨 CWE-94: Code Injection (eval)
            parsed_data = eval(user_input_data)
            
            for i in range(10):  # Tight Coupling UI Loop
                if i % 2 == 0:
                    print(f"Processing data chunk {i}...")
                    
                    # 🚨 Magic_Numbers
                    if parsed_data > 50000:
                        try:
                            # 🚨 CWE-89: SQL Injection (F-String)
                            self.db.execute(f"INSERT INTO logs VALUES ('{user_name}', {parsed_data})")
                        except Exception: # 🚨 Pokemon_Exceptions
                            print("SOMETIHNG BROKE")
                            pass
                else:
                    if parsed_data < 0:
                        print("CRITICAL: Negative value detected.")
                        # 🚨 CWE-78: Command Injection
                        /* SECURITY: system() removed by XAI auto-fixer (CWE-78) */ // system("echo 'ERROR OCCURRED' >> /var/log/syslog")
        else:
            print("System is down.")

if __name__ == "__main__":
    controller = SuperAdminSystemController()
    input_val = input("Enter raw data to evaluate: ") # Tight Coupling
    controller.process_all_system_logic_and_ui("Admin", input_val)
