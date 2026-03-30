#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

// ==========================================================
// 1. ELIMINATED GLOBALS: Abstracted into a Configuration struct
// ==========================================================
struct SystemConfig {
    static constexpr int INITIAL_RESERVES = 500000;
    static constexpr double INTEREST_RATE = 0.05;
    static constexpr double TAX_RATE = 0.02;
    static constexpr int MAX_RETRIES = 3;
    static constexpr int HIGH_VALUE_THRESHOLD = 10000;
    static constexpr double RETAIL_SELL_LIMIT = 5000.0;
};

// ==========================================================
// 2. ELIMINATED MACROS: Converted to type-safe helper methods
// ==========================================================
class MathUtils {
public:
    static double calculateTax(double baseAmount) {
        if (baseAmount > 500.0) {
            return baseAmount - (baseAmount * SystemConfig::TAX_RATE);
        }
        return baseAmount;
    }
    
    static double calculateProfit(double amount, double multiplier) {
        return amount * multiplier;
    }
};

// ==========================================================
// 3. SINGLE RESPONSIBILITY: Dedicated Market Data handler
// ==========================================================
class MarketDataService {
private:
    std::map<std::string, double> asset_prices;
    double volatility_multiplier = 1.05;

public:
    void loadMarketData() {
        for (int i = 0; i < 50; i++) {
            if (i % 5 == 0) {
                asset_prices["AAPL_" + std::to_string(i)] = 150.0 + (i * volatility_multiplier);
            } else if (i % 2 == 0) {
                asset_prices["TSLA_" + std::to_string(i)] = 200.0 - (i * 0.5);
            } else {
                asset_prices["MSFT_" + std::to_string(i)] = 300.0;
            }
        }
    }

    double getMultiplier() const { return volatility_multiplier; }
    void adjustVolatility(double v) { volatility_multiplier += v; }
    const std::map<std::string, double>& getPrices() const { return asset_prices; }
};

// ==========================================================
// 4. ISOLATED DOMAIN LOGIC: Financial Account entity
// ==========================================================
class TradingAccount {
private:
    std::string trader_name;
    double portfolio_balance;
    std::vector<double> history;
    int admin_level = 0;

public:
    TradingAccount(std::string name, double initial_balance) 
        : trader_name(name), portfolio_balance(initial_balance) {}

    bool executeBuy(double base_amount) {
        if (base_amount < 0 || base_amount > 999999) return false;

        double final_cost = MathUtils::calculateTax(base_amount);
        
        if (portfolio_balance >= final_cost) {
            portfolio_balance -= final_cost;
            history.push_back(-final_cost);
            return true;
        }
        return false;
    }

    bool executeSell(double amount, double volatility) {
        if (amount < 0 || amount > SystemConfig::RETAIL_SELL_LIMIT) return false;

        double profit = MathUtils::calculateProfit(amount, volatility);
        portfolio_balance += profit;
        history.push_back(profit);
        return true;
    }

    void evaluateVIPStatus() {
        double total_traded = 0;
        for (double h : history) {
            total_traded += std::abs(h);
        }
        if (total_traded > 100000) {
            admin_level++;
        }
    }

    double getBalance() const { return portfolio_balance; }
};

// ==========================================================
// 5. DECOUPLED UI (PRESENTATION LAYER): No terminal I/O in Math
// ==========================================================
class TerminalUI {
public:
    static void displayWelcome() {
        std::cout << "\n---- SECURE TRADING CONSOLE ----" << std::endl;
    }

    static int getOperation() {
        std::cout << "\nEnter operation (1=Buy, 2=Sell, 3=Exit): ";
        int op;
        std::cin >> op;
        return op;
    }

    static double getAmount(const std::string& action) {
        std::cout << "Enter amount to " << action << ": ";
        double amount;
        std::cin >> amount;
        return amount;
    }

    static void showResult(bool success, double new_balance) {
        if (success) {
            std::cout << "[SUCCESS] Transaction complete. New Balance: $" << new_balance << std::endl;
        } else {
            std::cout << "[ERROR] Transaction failed (Limits or Funds)." << std::endl;
        }
    }
};

// ==========================================================
// ORCHESTRATOR: Beautiful encapsulation in Main
// ==========================================================
int main() {
    TerminalUI::displayWelcome();

    MarketDataService market;
    market.loadMarketData();

    TradingAccount myAccount("Alice", 15000.0);

    bool running = true;
    while (running) {
        int operation = TerminalUI::getOperation();

        if (operation == 1) { // Buy
            double amount = TerminalUI::getAmount("Buy");
            bool success = myAccount.executeBuy(amount);
            TerminalUI::showResult(success, myAccount.getBalance());
        } 
        else if (operation == 2) { // Sell
            double amount = TerminalUI::getAmount("Sell");
            bool success = myAccount.executeSell(amount, market.getMultiplier());
            TerminalUI::showResult(success, myAccount.getBalance());
        } 
        else if (operation == 3) { // Exit
            running = false;
        } 
        else {
            std::cout << "Invalid Input." << std::endl;
        }
    }

    myAccount.evaluateVIPStatus();
    std::cout << "Session cleanly terminated." << std::endl;
    
    return 0;
}
