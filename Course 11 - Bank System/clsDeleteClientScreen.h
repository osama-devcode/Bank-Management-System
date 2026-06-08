#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:

    static void DeleteClient()
    {
        string AccountNumber = "";

        cout << "Enter The Account number of the client you want to delete: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is not fount, Please enter the right one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();

        char Answer = 'N';

        cout << "\n\nAre you sure you want to delete this client y/n? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfuly.\n";

                Client.Print();
            }
            else
            {
                cout << "\nError client was not deleted.\n";
            }

        }



    }


public:

	static void ShowDeleteClientScreen()
	{
        clsScreen::_DrawScreenHeader("\tDelete Client Screen");

        DeleteClient();
	}
};

