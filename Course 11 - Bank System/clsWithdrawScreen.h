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
		cout << "\n\nEnter the amout you want to withdraw: ";
		Amount = clsInputValidate::ReadDblNumberBetween(0,Client.AccountBalance,"amount is bigger than your balance, Enter aonther number: ");

		cout << "\nAre you sure you want to perform this transaction? [y/n]?";
		char Answer = 'y';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if(Client.Withdraw(Amount) == true)
			{
				cout << "\nAmount deposit succefuly.";
				cout << "\nNew amount is: " << Client.AccountBalance;
			}
			else
			{
				cout << "\nEror, Transaction was not made.";
			}
		}
	}
};

