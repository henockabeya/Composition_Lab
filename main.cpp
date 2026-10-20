/**
* @file main.cpp
 * @brief Driver testing transaction history composition on CheckingAccount and SavingsAccount.
 * @author Henoc Kabeya
 * @date October 19, 2026
 */

#include <iostream>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

using namespace std;

int main() {
    cout << "=====================================================" << endl;
    cout << "     Testing Transaction History with Composition    " << endl;
    cout << "=====================================================\n" << endl;

    // 1. Instantiate CheckingAccount ($2.50 fee) and SavingsAccount (5% interest)
    CheckingAccount checking("CHK-1001", "Henoc Kabeya", 500.0, 2.50);
    SavingsAccount savings("SAV-2002", "Henoc Kabeya", 1000.0, 0.05);

    // 2. Perform transactions on CheckingAccount
    cout << ">>> Performing CheckingAccount Transactions..." << endl;
    checking.deposit(150.00);  // Deposit $150.00
    checking -= 50.00;         // Withdraw $50.00 + $2.50 fee = $52.50
    checking -= 100.00;        // Withdraw $100.00 + $2.50 fee = $102.50

    // 3. Perform transactions on SavingsAccount
    cout << "\n>>> Performing SavingsAccount Transactions..." << endl;
    savings.deposit(500.00);    // Deposit $500.00
    savings.withdraw(200.00);   // Withdraw $200.00
    savings.calculateInterest(); // Accrues 5% interest on $1300.00 ($65.00) and deposits it

    // 4. Print transaction histories for both derived objects
    cout << "\n>>> Displaying Transaction Histories:" << endl;
    checking.printHistory();
    savings.printHistory();

    return 0;
}