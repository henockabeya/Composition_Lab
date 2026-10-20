/**
 * @file BankAccount.cpp
 * @brief Implementation of member methods, operators, utilities, and transaction logging for BankAccount.
 * @author Henoc Kabeya
 * @date October 19, 2026
 *
 * ====================================================================================
 * PROGRAM PURPOSE:
 * ------------------------------------------------------------------------------------
 * Implements the core business logic, operator overloads, and transaction history tracking
 * for the BankAccount base class in the Bank of Modesto Account Management System.
 *
 * BASIC LOGIC & ARCHITECTURE:
 * ------------------------------------------------------------------------------------
 * 1. State Encapsulation:
 *    - Encapsulates private member fields (accountNumber, accountHolderName, Balance).
 *    - Implements the Rule of Three (Copy Constructor, Copy Assignment Operator, Destructor)
 *      to ensure memory safety, deep copies, and self-assignment defense.
 *
 * 2. Composition (Transaction Logging):
 *    - Maintains a private vector<Transaction> transactionHistory member variable.
 *    - Automatically generates timestamps (YYYY-MM-DD HH:MM:SS) using the <ctime> library.
 *    - Appends a new Transaction instance to transactionHistory upon:
 *        * Initial positive balance initialization.
 *        * Successful deposit operations.
 *        * Successful withdrawal deductions.
 *    - Exposes printHistory() to enumerate the audit trail and current account balance.
 *
 * 3. Operator Delegation:
 *    - operator+= delegates directly to deposit(amount) for consistency and unified logging.
 *    - operator-= delegates directly to withdraw(amount) for unified logging and dynamic dispatch.
 *    - Relational operators (==, <, >) enable equality checks by account number and
 *      ordering comparisons based on current monetary balance.
 * ====================================================================================
 */

#include "BankAccount.h"
#include <ctime>
#include <limits>
#include <iostream>

using namespace std;

/**
 * @brief Helper utility function to generate an automated timestamp string.
 * @details Reads the current system time using time(nullptr) and formats it into
 *          a standard ISO-like timestamp string: "YYYY-MM-DD HH:MM:SS".
 * @return Formatted string containing the current date and time.
 */
static string getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

/**
 * @brief Default constructor initializing members to empty strings and a balance of 0.0.
 */
BankAccount::BankAccount() {
    accountNumber = "";
    accountHolderName = "";
    Balance = 0.0;
}

/**
 * @brief Parameterized constructor assigning specified field values and logging initial deposit.
 * @param accNum Alphanumeric account number string.
 * @param accHolder Full legal name of the account holder.
 * @param initialBalance Starting monetary balance deposited into the account.
 */
BankAccount::BankAccount(string accNum, string accHolder, double initialBalance) {
    accountNumber = accNum;
    accountHolderName = accHolder;
    Balance = initialBalance;

    if (Balance > 0.0) {
        transactionHistory.push_back(Transaction("Initial Deposit", Balance, getCurrentTimestamp()));
    }
}

/**
 * @brief Virtual destructor for clean deallocation of base and derived account instances.
 */
BankAccount::~BankAccount() {}

/**
 * @brief Copy constructor copying attributes and transaction history from an existing instance.
 * @param other The existing BankAccount instance to copy from.
 */
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber),
      accountHolderName(other.accountHolderName),
      Balance(other.Balance),
      transactionHistory(other.transactionHistory) {}

/**
 * @brief Copy assignment operator guarding against self-assignment.
 * @param other The right-hand-side BankAccount to copy state from.
 * @return Reference to the updated BankAccount instance (*this).
 */
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        Balance = other.Balance;
        transactionHistory = other.transactionHistory;
    }
    return *this;
}

/**
 * @brief Returns the unique account number.
 * @return String representation of the account number.
 */
string BankAccount::getAccountNumber() const {
    return accountNumber;
}

/**
 * @brief Returns the name of the account holder.
 * @return String containing the account holder's name.
 */
string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

/**
 * @brief Returns the current balance.
 * @return Current monetary balance as a double.
 */
double BankAccount::getBalance() const {
    return Balance;
}

/**
 * @brief Mutator method to update the account holder's name.
 * @param newName The updated legal holder name.
 */
void BankAccount::setAccountHolderName(string newName) {
    accountHolderName = newName;
}

/**
 * @brief Credits a positive monetary amount to the balance and records the transaction.
 * @param amount Numeric value to deposit into the account (must be strictly positive).
 */
void BankAccount::deposit(double amount) {
    if (amount > 0.0) {
        Balance += amount;
        transactionHistory.push_back(Transaction("Deposit", amount, getCurrentTimestamp()));
        cout << "The deposit was successfully processed." << endl;
    } else {
        cout << "The deposit was unsuccessful. It must be positive." << endl;
    }
}

/**
 * @brief Withdraws funds from balance if positive and sufficient, logging the transaction.
 * @param amount Numeric value to withdraw from the account.
 */
void BankAccount::withdraw(double amount) {
    if (amount <= 0.0) {
        cout << "The withdrawal must be positive. Please, try again." << endl;
    } else if (amount > Balance) {
        cout << "Error. Insufficient funds in the account." << endl;
    } else {
        Balance -= amount;
        transactionHistory.push_back(Transaction("Withdrawal", amount, getCurrentTimestamp()));
        cout << "The withdrawal was successfully processed." << endl;
    }
}

/**
 * @brief Overloaded addition-assignment operator delegating to deposit().
 * @param amount The monetary value to deposit.
 * @return Reference to the modified BankAccount object (*this).
 */
BankAccount& BankAccount::operator+=(double amount) {
    deposit(amount);
    return *this;
}

/**
 * @brief Overloaded subtraction-assignment operator delegating to withdraw().
 * @param amount The monetary value to withdraw.
 * @return Reference to the modified BankAccount object (*this).
 */
BankAccount& BankAccount::operator-=(double amount) {
    withdraw(amount);
    return *this;
}

/**
 * @brief Displays the formatted transaction log and current account balance to standard output.
 */
void BankAccount::printHistory() const {
    cout << "\n--- Transaction History for Account #" << accountNumber
         << " (" << accountHolderName << ") ---" << endl;
    if (transactionHistory.empty()) {
        cout << "  No transactions recorded." << endl;
    } else {
        for (const auto& txn : transactionHistory) {
            txn.print();
        }
    }
    cout << "  Current Balance: $" << Balance << endl;
}

/**
 * @brief Compares two account IDs for equality.
 * @param other The account to compare against.
 * @return true if account numbers match; false otherwise.
 */
bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}

/**
 * @brief Determines if this account holds less money than another.
 * @param other The account to compare against.
 * @return true if this account's balance is lower; false otherwise.
 */
bool BankAccount::operator<(const BankAccount& other) const {
    return Balance < other.Balance;
}

/**
 * @brief Determines if this account holds more money than another.
 * @param other The account to compare against.
 * @return true if this account's balance is higher; false otherwise.
 */
bool BankAccount::operator>(const BankAccount& other) const {
    return Balance > other.Balance;
}

/**
 * @brief Prints account number, holder name, and balance to standard output.
 * @param account Constant reference to the BankAccount instance to display.
 */
void BankAccount::printAccount(const BankAccount& account) {
    cout << "Account Number: " << account.getAccountNumber() << endl;
    cout << "Account Holder: " << account.getAccountHolderName() << endl;
    cout << "Account Balance: $" << account.getBalance() << endl;
}

/**
 * @brief Prompts for user input via the console, validates, and instantiates a new account.
 * @return A newly constructed BankAccount instance populated with user data.
 */
BankAccount BankAccount::createAccountFromInput() {
    string accNum, accHolder;
    double initialBalance;
    cout << "Enter account number: ";
    cin >> accNum;
    cout << "Enter account holder name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, accHolder);
    cout << "Enter initial balance: ";
    cin >> initialBalance;

    return BankAccount(accNum, accHolder, initialBalance);
}