#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

// Structure to store fake transactions
struct FakeTransaction {
    int fakeAccountNumber;
    string description;
    float amount;
    time_t timestamp;
};

// Create a class for bank account
class Account {
private:
    string name;
    int accountNumber;
    float balance;
    string password;
    vector<FakeTransaction> fakeTransactions;

public:
    // Constructor to initialize the account details
    Account(string name, int accountNumber, float balance, string password) {
        this->name = name;
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->password = password;
    }

    // Function to get the account name
    string getName() {
        return name;
    }

    // Function to get the account number
    int getAccountNumber() {
        return accountNumber;
    }

    // Function to get the account balance
    float getBalance() {
        return balance;
    }

    // Function to deposit money into the account
    void deposit(float amount) {
        balance += amount;
    }

    // Function to withdraw money from the account
    void withdraw(float amount) {
        balance -= amount;
    }

    // Function to check if the provided password matches the account's password
    bool authenticate(string enteredPassword) {
        return password == enteredPassword;
    }

    // Function to transfer money to a fake account
    void transferToFakeAccount(int fakeAccountNumber, float amount, string description) {
        FakeTransaction transaction;
        transaction.fakeAccountNumber = fakeAccountNumber;
        transaction.amount = amount;
        transaction.description = description;
        transaction.timestamp = time(nullptr);
        fakeTransactions.push_back(transaction);
        balance -= amount;
    }

    // Function to view past fake transactions
    void viewPastFakeTransactions() {
        cout << "Past Fake Transactions:\n" << endl;
        for (const auto& transaction : fakeTransactions) {
            cout << "Account Number: " << transaction.fakeAccountNumber << ", Amount: " << transaction.amount << ", Description: " << transaction.description << ", Timestamp: " << asctime(localtime(&transaction.timestamp));
        }
    }
};

// Vector to store all the created accounts
vector<Account> accounts;

// Function to create a new account
void createAccount() {
    string name, password;
    float balance;

    cout << "Creating New Account\n\n";

    cout << "Enter the account holder's name: ";
    cin >> name;

    // Generate a unique account number
    int accountNumber = accounts.size() + 1;

    cout << "Enter the initial balance: ";
    cin >> balance;

    cout << "Enter the account password: ";
    cin >> password;

    cout << "Your Unique Account Number: " << accountNumber <<" \n\n";

    usleep(1000000);

    // Create a new account object and store it in the vector
    Account newAccount(name, accountNumber, balance, password);
    accounts.push_back(newAccount);

    cout << "Account created successfully! \a" << endl;
}

// Function to login to an existing account
void login() {
    int accountNumber;
    string password;

    cout << "Logging To The Account\n\n";

    cout << "Enter the account number: ";
    cin >> accountNumber;

    cout << "Enter the account password: ";
    cin >> password;

    // Search for the account with the provided account number
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accountNumber) {
            // Account found, check the password
            if (account.authenticate(password)) {
                cout<<" \n\n";
                cout << "Login successful! \a" << endl;

                usleep(1000000);

                while (true) {
                    usleep(2000000);
                    system("clear");
                    cout << "Please Select From One Option \n\n";
                    cout << "1. Withdraw Money" << endl;
                    cout << "2. Transfer Money" << endl;
                    cout << "3. View Report" << endl;
                    cout << "4. Check Current Balance" << endl;
                    cout << "5. Logout" << endl;

                    int choice;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cout<<" \n\n";

                    usleep(500000);

                    switch (choice) {
                        case 1: {
                            usleep(500000);
                            system("clear");
                            float amount;
                            cout << "Enter the amount to withdraw: ";
                            cin >> amount;
                            cout<<"\n";
                            account.withdraw(amount);
                            cout << "Amount withdrawn successfully! \a" << endl;
                            break;
                        }
                        case 2: {
                            usleep(500000);
                            system("clear");
                            int fakeAccountNumber;
                            float amount;
                            string description;
                            cout << "Enter the account number: ";
                            cin >> fakeAccountNumber;
                            cout << "Enter the amount to transfer to the account: ";
                            cin >> amount;
                            cout << "Enter a description for the transaction: ";
                            cin.ignore();
                            getline(cin, description);
                            account.transferToFakeAccount(fakeAccountNumber, amount, description);\
                            cout<<" \n\n";
                            cout << "Amount transferred to account successfully! \a" << endl;
                            break;
                        }
                        case 3:
                            usleep(500000);
                            system("clear");
                            account.viewPastFakeTransactions();
                            usleep(2000000);
                            break;
                        case 4:
                            usleep(500000);
                            system("clear");
                            cout << "Current Balance: " << account.getBalance() << endl;
                            usleep(1000000);
                            break;
                        case 5:
                            cout << "Logged out successfully! \a" << endl;
                            return;
                        default:
                            usleep(500000);
                            system("clear");
                            cout << "Invalid choice! \a" << endl;
                    }
                }
            } else {
                cout << "Incorrect password. Login failed! \a" << endl;
                return;
            }
        }
    }

    // Account not found
    cout << "Account not found. Login failed! \a" << endl;
}

// Function to display the main menu
void displayMainMenu() {
    cout << "Welcome to the Bank!\n\n" << endl;
    cout << "Please select from the following options:" << endl;
    cout << "1. Create new account" << endl;
    cout << "2. Login to existing account" << endl;
    cout << "3. Quit" << endl;
}

// Function to process the user's selection
void processUserSelection() {
    int selection;
    cout << "Enter your selection: ";
    cin >> selection;

    switch (selection) {
        case 1:
            usleep(500000);
            system("clear");
            createAccount();
            break;
        case 2:
            usleep(500000);
            system("clear");
            login();
            break;
        case 3:
            cout<<"Bye Bye :) \a\a";
            usleep(500000);
            system("clear");
            exit(0);
            break;
        default:
            usleep(500000);
            system("clear");
            cout << "Invalid selection! \a" << endl;
    }
}

int main() {
    while (true) {
        usleep(2000000);
        system("clear");
        displayMainMenu();
        processUserSelection();
        cout << endl;
    }

    return 0;
}