#pragma once
#include <iostream>
using namespace std;
#include "clsUser.h"
#include "clsScreen.h"

class clsTransferScreen : protected clsScreen
{
private:

	static string _ReadAccountNumber(string message = "Enter Account Number: ")
	{
		string AccountNumber = clsInputValidate::ReadString(message);
		return AccountNumber;
	}

public:

	static void ShowTransferScreen()
	{
		clsScreen::_DrawScreenHeader("\t\tTransfer Screen");

		string SenderAccountNumber = _ReadAccountNumber("Enter the account number to transfer from: ");
		while (!clsBankClient::IsClientExist(SenderAccountNumber))
		{
			cout << "client with " << SenderAccountNumber << " account number does not exist.\n";
			SenderAccountNumber = _ReadAccountNumber("Enter the account number to transfer from: ");
		}
		clsBankClient SenderClient = clsBankClient::Find(SenderAccountNumber);
		SenderClient.Print();

		string ReceiverAccountNumber = _ReadAccountNumber("\n\nEnter the account number to transfer to: ");
		while (!clsBankClient::IsClientExist(ReceiverAccountNumber))
		{
			cout << "client with " << ReceiverAccountNumber << " account number does not exist.\n";
			ReceiverAccountNumber = _ReadAccountNumber("Enter the account number to transfer to: ");
		}
		clsBankClient ReceiverClient = clsBankClient::Find(ReceiverAccountNumber);
		ReceiverClient.Print();

		double Amount = 0;
		cout << "\n\nEnter the amount you want to transfer: ";
		Amount = clsInputValidate::ReadNumberBetween <double>(0, SenderClient.AccountBalance, "Amount exceeds the available balance, Enter aonther number: ");

		cout << "\nAre you sure you want to perform this transaction? [y/n]?";
		char Answer = 'y';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if (SenderClient.Transfer(Amount, ReceiverAccountNumber) == true)
			{
				cout << "\nTransfer done successfully.";

				//transfer log save
			}
			else
			{
				cout << "\nError, Transfer Faild.";
			}
		}
	
		SenderClient = clsBankClient::Find(SenderAccountNumber);
		SenderClient.Print();
		ReceiverClient = clsBankClient::Find(ReceiverAccountNumber);
		ReceiverClient.Print();

	}
};

