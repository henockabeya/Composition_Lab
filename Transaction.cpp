//
// Created by Henoc Kabeya on 10/19/26.
//

#include "Transaction.h"
#include <iostream>

Transaction::Transaction() : type(""), amount(0.0), timestamp("") {}

Transaction::Transaction(std::string t, double a, std::string ts)
    : type(t), amount(a), timestamp(ts) {}

void Transaction::print() const {
    std::cout << "  [" << timestamp << "] " << type << ": $" << amount << std::endl;

}

