#include "Account.h"
#include <sstream>

Account::Account()
{
    accountNumber = "";
    holderName = "";
    pin = "";
    balance = 0.0;
}

Account::Account(string accNo, string name, string userPin, double bal)
{
    accountNumber = accNo;
    holderName = name;
    pin = userPin;
    balance = bal;
}

string Account::getAccountNumber() const
{
    return accountNumber;
}

string Account::getHolderName() const
{
    return holderName;
}

string Account::getPin() const
{
    return pin;
}

double Account::getBalance() const
{
    return balance;
}

void Account::setPin(string newPin)
{
    pin = newPin;
}

void Account::setBalance(double amount)
{
    balance = amount;
}

void Account::deposit(double amount)
{
    balance += amount;

    stringstream ss;
    ss << "Deposited Rs. " << amount;

    history.push_back(ss.str());
}

bool Account::withdraw(double amount)
{
    if(amount > balance)
        return false;

    balance -= amount;

    stringstream ss;
    ss << "Withdrawn Rs. " << amount;

    history.push_back(ss.str());

    return true;
}

bool Account::transfer(Account &receiver, double amount)
{
    if(amount > balance)
        return false;

    balance -= amount;
    receiver.balance += amount;

    stringstream s1;
    s1 << "Transferred Rs. " << amount
       << " to " << receiver.accountNumber;

    history.push_back(s1.str());

    stringstream s2;
    s2 << "Received Rs. " << amount
       << " from " << accountNumber;

    receiver.history.push_back(s2.str());

    return true;
}

void Account::addTransaction(string transaction)
{
    history.push_back(transaction);
}

vector<string> Account::getTransactionHistory() const
{
    return history;
}

string Account::serialize() const
{
    stringstream ss;

    ss << accountNumber << "|"
       << holderName << "|"
       << pin << "|"
       << balance;

    return ss.str();
}

Account Account::deserialize(string line)
{
    stringstream ss(line);

    string accNo, name, pin, bal;

    getline(ss, accNo, '|');
    getline(ss, name, '|');
    getline(ss, pin, '|');
    getline(ss, bal);

    return Account(accNo, name, pin, stod(bal));
}