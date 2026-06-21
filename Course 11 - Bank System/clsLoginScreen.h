#pragma once
#include <iostream>
using namespace std;
#include "clsUser.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsScreen.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFailed = false;
		int FaildLoginCount = 0;

		do
		{
			string Username;
			string Password;

			if (LoginFailed)
			{
				FaildLoginCount++;
				
				cout << "\nUsername/Password is invalid";
				cout << "\nYou have (" << (3 - FaildLoginCount) << ") Trails to login\n\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\nYour are Locked after 3 faild trails \n\n";
				return false;
			}

			cout << "Enter Username: ";
			Username = clsInputValidate::ReadString();

			cout << "Enter Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);

		//save the login data after here to make sure that the save is ouccured after the successfull login
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		return _Login();
		 
	}

};

