#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "Account.h"

using namespace std;

class FileManager
{
public:

    static vector<Account> loadAccounts();

    static void saveAccounts(const vector<Account>& accounts);

};

#endif