#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositScreen : protected clsScreen

{
private:

	static string _ReadAccountNumber()
	{ 
		string AccountNumber = clsInputValidate::ReadString("Enter Account Number: ");
		return AccountNumber;
	}

public:

	static void ShowDepositScreen()
	{
		clsScreen::_DrawScreenHeader("\t     Deposit Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "client with " << AccountNumber << " account number does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();

		double Amount = 0;
		cout << "\n\nEnter the amout you want to deposit: ";
		Amount = clsInputValidate::ReadNumber <double> ();

		cout << "\nAre you sure you want to perform this transaction? [y/n]?";
		char Answer = 'y';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\nAmount deposit succefuly.";
			cout << "\nNew balance is: " << Client.AccountBalance;
		}
	}
};

