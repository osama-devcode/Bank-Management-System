#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << setw(40) << left << "" << "______________________________________";
        cout << endl << endl << setw(40) << left << "" << Title;
        if (SubTitle != "")
        {
            cout << endl << endl << setw(40) << left << "" << SubTitle;
        }
        cout << endl << setw(40) << left << "" << "______________________________________\n\n";
     
        cout << setw(40) << left << "" << "User: " << CurrentUser.UserName << endl;
        cout << setw(40) << left << "" << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
    
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};

