#include "FileManager.h"
#include <fstream>
#include <iostream>

vector<Account> FileManager::loadAccounts()
{
    vector<Account> accounts;

    ifstream file("accounts.txt");

    if(!file.is_open())
    {
        return accounts;
    }

    string line;

    while(getline(file,line))
    {
        if(line.length() > 0)
        {
            accounts.push_back(Account::deserialize(line));
        }
    }

    file.close();

    return accounts;
}

void FileManager::saveAccounts(const vector<Account>& accounts)
{
    ofstream file("accounts.txt");

    if(!file.is_open())
    {
        cout<<"Unable to save accounts.\n";
        return;
    }

    for(const Account &acc : accounts)
    {
        file<<acc.serialize()<<endl;
    }

    file.close();
}