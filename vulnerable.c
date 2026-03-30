#include <iostream>
#include <vector>
using namespace std;

class OrderSystem {
public:
    vector<string> orders;

    void addOrder(string item) {
        orders.push_back(item);
        cout << "Order added: " << item << endl;
    }

    void processPayment(string item) {
        cout << "Processing payment for " << item << endl;
        // Assume always success
    }

    void sendEmail(string item) {
        cout << "Sending email for order: " << item << endl;
    }

    void placeOrder(string item) {
        addOrder(item);
        processPayment(item);
        sendEmail(item);
    }

    void showOrders() {
        for (auto o : orders) {
            cout << o << endl;
        }
    }
};

int main() {
    OrderSystem system;
    system.placeOrder("Laptop");
    system.placeOrder("Phone");
    system.showOrders();
}
