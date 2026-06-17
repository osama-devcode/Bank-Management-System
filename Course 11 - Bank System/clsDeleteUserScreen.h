#pragma once
#include <iostream>
using namespace std;
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\tDelete User Screen");

		cout << "Enter Username: ";
		string UserName = clsInputValidate::ReadString();
		char Answer;

		while (clsUser::IsUserExist(UserName) == false)
		{
			cout << "User doesn't exist enter another username: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		User.Print();

		cout << "\n\nAre you sure you want to delete this user? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "User Deleted Successfully\n";
			}
			else
			{
				cout << "Error User wasn't deleted\n";
			}
		}		

	}

};

