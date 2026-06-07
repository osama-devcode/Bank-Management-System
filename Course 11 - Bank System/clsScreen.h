#pragma once
#include <iostream>


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
    }


};

