#include <iostream>
#include <string>
#include <map>
using namespace std;

class Account {
public:
    string accountNumber;
    string accountHolder;
    double balance;

    Account() : accountNumber(""), accountHolder(""), balance(0.0) {} // Default constructor

    Account(string accNum, string holder, double bal)
        : accountNumber(accNum), accountHolder(holder), balance(bal) {}

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: INR " << amount << ". New Balance: INR " << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds. Current Balance: INR " << balance << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrawn: INR " << amount << ". New Balance: INR " << balance << endl;
        return true;
    }

    bool transfer(Account &toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "Transferred: INR " << amount << " to " << toAccount.accountHolder << endl;
            return true;
        }
        return false;
    }

    void displayBalance() const {
        cout << "Account Holder: " << accountHolder << ", Account Number: " << accountNumber << ", Balance: INR " << balance << endl;
    }
};

class BankingSystem {
private:
    map<string, Account> accounts;

    string generateAccountNumber() {
        static int counter = 1000;
        return "IN" + to_string(counter++);
    }

public:
    void createAccount(const string &holder) {
        string accountNumber = generateAccountNumber();
        accounts[accountNumber] = Account(accountNumber, holder, 0.0);
        cout << "Account created for " << holder << ". Account Number: " << accountNumber << endl;
    }

    Account* findAccount(const string &accountNumber) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end())
            return &it->second;
        return nullptr;
    }

    void deposit(const string &accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->deposit(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void withdraw(const string &accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->withdraw(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void transfer(const string &fromAccount, const string &toAccount, double amount) {
        Account* sender = findAccount(fromAccount);
        Account* receiver = findAccount(toAccount);
        if (sender && receiver) {
            sender->transfer(*receiver, amount);
        } else {
            cout << "One or both accounts not found." << endl;
        }
    }

    void displayBalance(const string &accountNumber) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->displayBalance();
        } else {
            cout << "Account not found." << endl;
        }
    }
};

void displayMenu() {
    cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Display Balance\n6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BankingSystem bank;
    int choice;
    string accountNumber, holder, toAccount;
    double amount;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // Ignore the newline character left in the input buffer

        switch (choice) {
            case 1:
                cout << "Enter account holder name: ";
                getline(cin, holder);
                bank.createAccount(holder);
                break;
            case 2:
                cout << "Enter account number: ";
                getline(cin, accountNumber);
                cout << "Enter amount to deposit: ";
                cin >> amount;
                cin.ignore();  // Ignore the newline character left in the input buffer
                bank.deposit(accountNumber, amount);
                break;
            case 3:
                cout << "Enter account number: ";
                getline(cin, accountNumber);
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                cin.ignore();  // Ignore the newline character left in the input buffer
                bank.withdraw(accountNumber, amount);
                break;
            case 4:
                cout << "Enter your account number: ";
                getline(cin, accountNumber);
                cout << "Enter recipient's account number: ";
                getline(cin, toAccount);
                cout << "Enter amount to transfer: ";
                cin >> amount;
                cin.ignore();  // Ignore the newline character left in the input buffer
                bank.transfer(accountNumber, toAccount, amount);
                break;
            case 5:
                cout << "Enter account number: ";
                getline(cin, accountNumber);
                bank.displayBalance(accountNumber);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
   
