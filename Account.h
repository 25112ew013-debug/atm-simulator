#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account
{
private:
    string accountNumber;
    string holderName;
    string pin;
    double balance;
    vector<string> history;

public:

    // Constructors
    Account();
    Account(string accNo, string name, string userPin, double bal);

    // Getters
    string getAccountNumber() const;
    string getHolderName() const;
    string getPin() const;
    double getBalance() const;

    // Setters
    void setPin(string newPin);
    void setBalance(double amount);

    // Banking Operations
    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account &receiver, double amount);

    // Transaction History
    void addTransaction(string transaction);
    vector<string> getTransactionHistory() const;

    // File Handling
    string serialize() const;
    static Account deserialize(string line);
};

#endif