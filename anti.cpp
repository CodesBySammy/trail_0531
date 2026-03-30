#include <iostream>
#include <string>
#include <vector>

// 🚨 SPAGHETTI GLOBALS
int user_balance = 1000;
bool is_admin = false;
std::string global_log_state = "";
int server_retries = 0;

// 🚨 MACRO ABUSE
#define VALIDATE_AND_EXECUTE(x, y) \
    if (x > y) { \
        user_balance -= y; \
        std::cout << "Transaction processed!" << std::endl; \
    } else { \
        server_retries++; \
    }

// 🚨 GOD CLASS & TIGHT COUPLING
class SystemController {
public:
    int id;
    std::string db_connection;
    std::vector<int> cached_ids;
    
    // 🚨 LONG METHOD & MAGIC NUMBERS
    void processEverythingAndRenderUI(int amount) {
        std::cout << "Enter admin password: "; // 🚨 Tight Coupling (UI in Domain)
        std::string input;
        std::cin >> input;
        
        if (input == "admin123") {
            is_admin = true;
        }

        if (is_admin && amount < 50000) { // 🚨 Magic Numbers
            VALIDATE_AND_EXECUTE(user_balance, amount);
            global_log_state = "Success";
        } else {
            std::cout << "Critical Error!" << std::endl;
        }
    }
};

int main() {
    SystemController godObj;
    godObj.processEverythingAndRenderUI(400);
    return 0;
}
