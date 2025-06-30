#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

class Transaction {
public:
    std::string type;
    double amount;
    std::string timestamp;

    Transaction(const std::string& t, double amt) {
        type = t;
        amount = amt;

        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline
    }

    void display() const {
        std::cout << std::left << std::setw(12) << type
                  << std::setw(10) << amount
                  << timestamp << '\n';
    }
};

class Account {
private:
    int accountNumber;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account(int accNum) : accountNumber(accNum), balance(0.0) {}

    int getAccountNumber() const { return accountNumber; }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        std::cout << "✅ Deposited: " << amount << "\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            std::cout << "❌ Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdraw", amount);
        std::cout << "✅ Withdrawn: " << amount << "\n";
        return true;
    }

    bool transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            transactions.emplace_back("Transfer", amount);
            return true;
        }
        return false;
    }

    void showBalance() const {
        std::cout << "Current Balance: " << balance << "\n";
    }

    void showTransactions(int count = 5) const {
        std::cout << "\nRecent Transactions:\n";
        std::cout << std::left << std::setw(12) << "Type"
                  << std::setw(10) << "Amount"
                  << "Timestamp\n";
        std::cout << "------------------------------------------\n";

        int n = transactions.size();
        for (int i = std::max(0, n - count); i < n; ++i) {
            transactions[i].display();
        }
    }
};

class Customer {
private:
    std::string name;
    int customerID;
    Account account;

public:
    Customer(const std::string& n, int id) : name(n), customerID(id), account(id + 1000) {}

    int getID() const { return customerID; }
    Account& getAccount() { return account; }

    void showInfo() const {
        std::cout << "Customer Name: " << name << "\n";
        std::cout << "Customer ID: " << customerID << "\n";
        std::cout << "Account Number: " << account.getAccountNumber() << "\n";
    }
};

// Global storage of customers
std::vector<Customer> customers;

Customer* findCustomerByID(int id) {
    for (auto& c : customers) {
        if (c.getID() == id)
            return &c;
    }
    return nullptr;
}

// ----------------------------- Main Menu -----------------------------

int main() {
    int choice;
    int customerIDCounter = 100;

    do {
        std::cout << "\n========== BANKING SYSTEM MENU ==========\n";
        std::cout << "1. Create Customer\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Transfer Funds\n";
        std::cout << "5. View Account Info\n";
        std::cout << "6. View Transactions\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cout << "Enter Customer Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            customers.emplace_back(name, customerIDCounter++);
            std::cout << "✅ Customer created with ID: " << (customerIDCounter - 1) << "\n";
        }

        else if (choice >= 2 && choice <= 6) {
            int id;
            std::cout << "Enter your Customer ID: ";
            std::cin >> id;
            Customer* cust = findCustomerByID(id);

            if (!cust) {
                std::cout << "❌ Customer not found.\n";
                continue;
            }

            Account& acc = cust->getAccount();

            if (choice == 2) {
                double amt;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amt;
                acc.deposit(amt);
            } else if (choice == 3) {
                double amt;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amt;
                acc.withdraw(amt);
            } else if (choice == 4) {
                int targetID;
                double amt;
                std::cout << "Enter target Customer ID: ";
                std::cin >> targetID;
                Customer* targetCust = findCustomerByID(targetID);

                if (!targetCust) {
                    std::cout << "❌ Target customer not found.\n";
                    continue;
                }

                std::cout << "Enter amount to transfer: ";
                std::cin >> amt;
                acc.transfer(targetCust->getAccount(), amt);
            } else if (choice == 5) {
                cust->showInfo();
                acc.showBalance();
            } else if (choice == 6) {
                acc.showTransactions();
            }
        }

    } while (choice != 0);

    std::cout << "Thank you for using the Banking System.\n";
    return 0;
}
