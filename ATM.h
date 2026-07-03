#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <vector>
#include "Account.h"
#include "FileManager.h"

using namespace std;

class ATM
{
private:

    vector<Account> accounts;
    int currentIndex;

public:

    ATM();

    void run();

private:

    void loadData();
    void saveData();

    void mainMenu();
    void login();
    void createAccount();

    void userMenu();

    void checkBalance();
    void deposit();
    void withdraw();
    void transferMoney();
    void changePIN();
    void showTransactions();

    int searchAccount(string accountNo);
};

#endif