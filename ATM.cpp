#include "ATM.h"

ATM::ATM()
{
    currentIndex = -1;
    loadData();
}

void ATM::loadData()
{
    accounts = FileManager::loadAccounts();
}

void ATM::saveData()
{
    FileManager::saveAccounts(accounts);
}

int ATM::searchAccount(string accountNo)
{
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNo)
        {
            return i;
        }
    }

    return -1;
}

void ATM::run()
{
    mainMenu();
}

void ATM::mainMenu()
{
    int choice;

    while(true)
    {
        cout << "\n==================================";
        cout << "\n          ATM SIMULATOR";
        cout << "\n==================================";
        cout << "\n1. Login";
        cout << "\n2. Create Account";
        cout << "\n3. Exit";
        cout << "\nEnter Choice: ";

        cin >> choice;

        switch(choice)
        {
            case 1:
                login();
                break;

            case 2:
                createAccount();
                break;

            case 3:
                saveData();
                cout << "\nThank you for using ATM.\n";
                return;

            default:
                cout << "\nInvalid Choice.\n";
        }
    }
}

void ATM::createAccount()
{
    string accNo;
    string name;
    string pin;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    if(searchAccount(accNo) != -1)
    {
        cout << "\nAccount already exists.\n";
        return;
    }

    cout << "Enter Holder Name: ";
    cin >> name;

    cout << "Enter 4 Digit PIN: ";
    cin >> pin;

    Account newAccount(accNo, name, pin, 0);

    accounts.push_back(newAccount);

    saveData();

    cout << "\nAccount Created Successfully.\n";
}

void ATM::login()
{
    string accNo;
    string pin;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter PIN: ";
    cin >> pin;

    int index = searchAccount(accNo);

    if(index == -1)
    {
        cout << "\nAccount Not Found.\n";
        return;
    }

    if(accounts[index].getPin() != pin)
    {
        cout << "\nIncorrect PIN.\n";
        return;
    }

    currentIndex = index;

    cout << "\nLogin Successful.\n";

    userMenu();
}
void ATM::userMenu()
{
    int choice;

    while(true)
    {
        cout<<"\n===================================";
        cout<<"\n         USER MENU";
        cout<<"\n===================================";
        cout<<"\n1. Check Balance";
        cout<<"\n2. Deposit Money";
        cout<<"\n3. Withdraw Money";
        cout<<"\n4. Transfer Money";
        cout<<"\n5. Change PIN";
        cout<<"\n6. Transaction History";
        cout<<"\n7. Logout";
        cout<<"\nEnter Choice : ";

        cin>>choice;

        switch(choice)
        {
            case 1:
                checkBalance();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                transferMoney();
                break;

            case 5:
                changePIN();
                break;

            case 6:
                showTransactions();
                break;

            case 7:
                saveData();
                currentIndex=-1;
                return;

            default:
                cout<<"\nInvalid Choice.\n";
        }
    }
}

void ATM::checkBalance()
{
    cout<<"\nCurrent Balance : Rs. "
        <<accounts[currentIndex].getBalance()
        <<endl;
}

void ATM::deposit()
{
    double amount;

    cout<<"\nEnter Amount : ";
    cin>>amount;

    if(amount<=0)
    {
        cout<<"Invalid Amount.\n";
        return;
    }

    accounts[currentIndex].deposit(amount);

    saveData();

    cout<<"\nMoney Deposited Successfully.\n";
}

void ATM::withdraw()
{
    double amount;

    cout<<"\nEnter Amount : ";
    cin>>amount;

    if(amount<=0)
    {
        cout<<"Invalid Amount.\n";
        return;
    }

    if(accounts[currentIndex].withdraw(amount))
    {
        saveData();

        cout<<"\nWithdrawal Successful.\n";
    }
    else
    {
        cout<<"\nInsufficient Balance.\n";
    }
}
void ATM::transferMoney()
{
    string receiver;
    double amount;

    cout<<"\nReceiver Account Number : ";
    cin>>receiver;

    int index=searchAccount(receiver);

    if(index==-1)
    {
        cout<<"\nReceiver Account Not Found.\n";
        return;
    }

    if(index==currentIndex)
    {
        cout<<"\nCannot Transfer To Same Account.\n";
        return;
    }

    cout<<"Enter Amount : ";
    cin>>amount;

    if(amount<=0)
    {
        cout<<"Invalid Amount.\n";
        return;
    }

    if(accounts[currentIndex].transfer(accounts[index],amount))
    {
        saveData();

        cout<<"\nTransfer Successful.\n";
    }
    else
    {
        cout<<"\nInsufficient Balance.\n";
    }
}

void ATM::changePIN()
{
    string oldPin,newPin;

    cout<<"\nEnter Current PIN : ";
    cin>>oldPin;

    if(oldPin!=accounts[currentIndex].getPin())
    {
        cout<<"\nIncorrect PIN.\n";
        return;
    }

    cout<<"Enter New PIN : ";
    cin>>newPin;

    accounts[currentIndex].setPin(newPin);

    saveData();

    cout<<"\nPIN Changed Successfully.\n";
}
void ATM::showTransactions()
{
    vector<string> history=
        accounts[currentIndex].getTransactionHistory();

    cout<<"\n===================================";
    cout<<"\n     TRANSACTION HISTORY";
    cout<<"\n===================================\n";

    if(history.empty())
    {
        cout<<"No Transactions Found.\n";
        return;
    }

    for(int i=0;i<history.size();i++)
    {
        cout<<i+1<<". "<<history[i]<<endl;
    }
}
