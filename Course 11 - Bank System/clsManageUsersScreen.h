#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersScreen : protected clsScreen
{
	enum _enManageUsersMenueOptions { eListUsers = 1, eAddNewUser = 2,
		eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6	};

	static short _ReadManageUsersOption()
	{
		cout << setw(37) << left << "";
		cout << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadNumberBetween(1, 6);
		return Choice;
	}

	static void _GoBackToManageUsersScreen()
	{
		cout << "\n\nPress any key to go back to manage users screen...";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersScreen();
	}
	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}


	static void _PerformManageUsersMenueOption(_enManageUsersMenueOptions ManageUsersMenueOptions)
	{
		
		switch (ManageUsersMenueOptions)
		{
		case _enManageUsersMenueOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersScreen();
			break;
		}

		case _enManageUsersMenueOptions::eAddNewUser :
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersScreen();
			break;
		}

		case _enManageUsersMenueOptions::eDeleteUser :
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersScreen();
			break;
		}

		case _enManageUsersMenueOptions::eUpdateUser :
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersScreen();
			break;
		}

		case _enManageUsersMenueOptions::eFindUser :
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersScreen();
			break;
		}

		case _enManageUsersMenueOptions::eMainMenue :
		{
			break;
		}

		default:
		{
			break;
		}

		}
	}


public:

	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;// this will exit the function and it will not continue 
		}

		system("cls");
		clsScreen::_DrawScreenHeader("\tManage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Users List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";


		_PerformManageUsersMenueOption((_enManageUsersMenueOptions)_ReadManageUsersOption());
	}
};

