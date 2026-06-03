#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum _enMainMenueOptions {eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6, eManageUsers = 7, eExit = 8};

	static short _ReadMainMenueOption()
	{
		cout << setw(27) << left << "Choose what you want to do? [1 to 8]?";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 8);
		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(27) << left << "Press any key to go back to the main menu...";
		system ("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		cout << "Clients list screen will be here\n";
	}
	static void _ShowAddNewClientScreen()
	{
		cout << "Add New Client screen will be here\n";
	}
	static void _ShowDeleteClientScreen()
	{
		cout << "Delete Client screen will be here\n";
	}
	static void _ShowUpdateClientScreen()
	{
		cout << "Update client screen will be here\n";
	}
	static void _ShowFindClientScreen()
	{
		cout << "Find client screen will be here\n";
	}
	static void _ShowTransactionsMenue()
	{
		cout << "Transactions menue will be here\n";
	}
	static void _ShowManageUsersMenue()
	{
		cout << "Manage Users menue will be here\n";
	}
	static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will be here...\n";

	}

	static void _PerformMainMenueOption(_enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{ 
		
		case _enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eDeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eShowTransactionsMenu:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eManageUsers:
		{
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		}

		case _enMainMenueOptions::eExit:
		{
			system("cls");
			_ShowEndScreen();
			//login()
			break;
		}

		default:
		{
			system("cls");
			_GoBackToMainMenue();
			break;
		}
		}
			



	}


	public:

	static void ShowMainMenue()
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\t\tMain Screen");

		cout << "===========================================\n";
		cout << "\t\tMain Menue\n";
		cout << "===========================================\n";
		cout << "\t[1] Show Client List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] Logout.\n";
		cout << "===========================================\n";

		_PerformMainMenueOption((_enMainMenueOptions)_ReadMainMenueOption());
	}
};

