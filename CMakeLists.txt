cmake_minimum_required(VERSION 4.3)
project(Composition_Lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(Composition_Lab main.cpp
        SavingsAccount.cpp
        CheckingAccount.cpp
        SavingsAccount.h
        CheckingAccount.h
        BankAccount.cpp
        BankAccount.h
        Transaction.h
        Transaction.cpp)
