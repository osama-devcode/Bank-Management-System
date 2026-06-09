#pragma once 
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
using namespace std;

class clsTransactionsScreen : protected clsScreen

{
private:
	enum _enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2,
		eShowTotalBalances = 3, eShowMainMenue = 4	};

	static short _ReadTransactionMenueOption()
	{
		cout << setw(37) << left << "" << "choose what you want to do? [1 to 4]?";
		short choice = clsInputValidate::ReadShortNumberBetween(1, 4);
		return choice;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWhitdrawScreen()
	{
		cout << "\n\nWithdraw Screen will be here...";
	}
	static void _ShowTotalBalancesScreen()
	{
		cout << "\n\nTotal Balances Screen will be here...";
	}
	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to transactions menue...";
		system("pause>0");
		ShowTransactionsMenueScreen();
	}

	static void _PerformTransactionMenueOption(_enTransactionsMenueOptions TransactionsMenueOptions)
	{
		switch (TransactionsMenueOptions)
		{
		case _enTransactionsMenueOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsMenueOptions::eWithdraw:
			system("cls");
			_ShowWhitdrawScreen();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsMenueOptions::eShowTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsMenueOptions::eShowMainMenue:
			break;

		default:
			break;

		}
	}

public:

	static void ShowTransactionsMenueScreen()
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\t   Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t      Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Whitdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Show Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Main Menue.\n";
		_PerformTransactionMenueOption((_enTransactionsMenueOptions)_ReadTransactionMenueOption());
	}

};

