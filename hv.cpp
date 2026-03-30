#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
using namespace std;

class Logger {
public:
    static Logger* instance;

    static Logger* getInstance() {
        if (!instance)
            instance = new Logger(); // ❌ never deleted (leak)
        return instance;
    }

    void log(const char* msg) {
        cout << msg << endl;
    }
};

Logger* Logger::instance = nullptr;

// God Class: DB + Business Logic + Memory + Threads
class UserManager {
private:
    char* buffer;
    vector<string>* users;

public:
    UserManager() {
        buffer = (char*)malloc(100); // ❌ C-style allocation
        users = new vector<string>(); // ❌ raw pointer
    }

    void addUser(const char* name) {
        strcpy(buffer, name); // ❌ buffer overflow risk
        users->push_back(string(buffer));
        Logger::getInstance()->log("User added");
    }

    void processUsers() {
        thread t([this]() {
            for (auto& u : *users) {
                cout << "Processing " << u << endl;
            }
        });
        t.detach(); // ❌ detached thread → lifetime issues
    }

    ~UserManager() {
        // ❌ memory leaks: buffer + users not freed
    }
};

int main() {
    UserManager* manager = new UserManager(); // ❌ raw pointer

    manager->addUser("Alice");
    manager->addUser("Bob");

    manager->processUsers();

    // ❌ manager never deleted
    return 0;
}
