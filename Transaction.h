//
// Created by Henoc Kabeya on 10/19/26.
//

#ifndef COMPOSITION_LAB_TRANSACTION_H
#define COMPOSITION_LAB_TRANSACTION_H

#include <string>
#include <iostream>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string timestamp;

    Transaction();
    Transaction(std::string t, double a, std::string ts);
    void print() const;
};


#endif //COMPOSITION_LAB_TRANSACTION_H
