#pragma once
#include <iostream>
using namespace std;
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\tFind User Screen");

		cout << "Enter Username: ";
		string Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username) == false)
		{
			cout << "User doesn't exist enter another username: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);
		User.Print();
	};

};

