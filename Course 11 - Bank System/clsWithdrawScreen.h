#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:

	static string _ReadAccountNumber()
	{
		string AccountNumber = clsInputValidate::ReadString("Enter Account Number: ");
		return AccountNumber;
	}


public:

	static void ShowWithdrawScreen()
	{
		clsScreen::_DrawScreenHeader("\t   Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "client with " << AccountNumber << " account number does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();

		double Amount = 0;
		cout << "\n\nEnter the amount you want to withdraw: ";
		Amount = clsInputValidate::ReadNumberBetween <double> (0,Client.AccountBalance,"Enter aonther number: ");

		cout << "\nAre you sure you want to perform this transaction? [y/n]?";
		char Answer = 'y';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if(Client.Withdraw(Amount) == true)
			{
				cout << "\nAmount deposit successfully.";
				cout << "\nNew balance is: " << Client.AccountBalance;
			}
			else
			{
				cout << "\nError, Transaction was not made.";
			}
		}
	}
};

