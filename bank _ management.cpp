#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Account {
    int accountNo;
    string name;
    double balance;
};

vector<Account> accounts;
const string FILE_NAME = "bank.txt";

void saveData() {
    ofstream file(FILE_NAME);

    for (const auto &a : accounts) {
        file << a.accountNo << '\n';
        file << a.name << '\n';
        file << a.balance << '\n';
    }
}

void loadData() {
    ifstream file(FILE_NAME);
    Account a;

    while (file >> a.accountNo) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, a.name))
            break;

        if (!(file >> a.balance))
            break;

        file.ignore(numeric_limits<streamsize>::max(), '\n');
        accounts.push_back(a);
    }
}

int findAccount(int accountNo) {
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].accountNo == accountNo)
            return i;
    }
    return -1;
}

void createAccount() {
    Account a;

    cout << "Enter Account Number: ";
    if (!(cin >> a.accountNo)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findAccount(a.accountNo) != -1) {
        cout << "Account number already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Account Holder Name: ";
    getline(cin, a.name);

    if (a.name.empty()) {
        cout << "Name cannot be empty!\n";
        return;
    }

    a.balance = 0;

    accounts.push_back(a);
    saveData();

    cout << "Account created successfully!\n";
}

void displayAccount() {
    int number;

    cout << "Enter Account Number: ";
    if (!(cin >> number)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccount(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "\nAccount Number: " << accounts[index].accountNo;
    cout << "\nAccount Holder: " << accounts[index].name;
    cout << fixed << setprecision(2);
    cout << "\nBalance: Rs. " << accounts[index].balance << '\n';
}

void depositMoney() {
    int number;
    double amount;

    cout << "Enter Account Number: ";
    if (!(cin >> number)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccount(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Amount to Deposit: ";
    if (!(cin >> amount) || amount <= 0) {
        cout << "Enter a valid positive amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    accounts[index].balance += amount;
    saveData();

    cout << "Money deposited successfully!\n";
    cout << "Updated Balance: Rs. "
         << fixed << setprecision(2)
         << accounts[index].balance << '\n';
}

void withdrawMoney() {
    int number;
    double amount;

    cout << "Enter Account Number: ";
    if (!(cin >> number)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccount(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Amount to Withdraw: ";
    if (!(cin >> amount) || amount <= 0) {
        cout << "Enter a valid positive amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (amount > accounts[index].balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    accounts[index].balance -= amount;
    saveData();

    cout << "Money withdrawn successfully!\n";
    cout << "Remaining Balance: Rs. "
         << fixed << setprecision(2)
         << accounts[index].balance << '\n';
}

int main() {
    loadData();

    int choice;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                displayAccount();
                break;

            case 3:
                depositMoney();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                displayAccount();
                break;

            case 6:
                saveData();
                cout << "Thank you for using our application!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
