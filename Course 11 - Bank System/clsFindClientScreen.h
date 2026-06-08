#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:


public:

	static void ShowFindClientScreen()
	{
		clsScreen::_DrawScreenHeader("\tFind Client Screen");

		cout << "Enter the client account number: ";
		string AccountNumber = clsInputValidate::ReadString();

		if (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			cout << "Client Found :)\n\n";
		}
		else
		{
			cout << "Client was not found :(\n\n";
		}

		Client.Print();

	}
};

