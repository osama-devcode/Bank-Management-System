#pragma once
#include <iostream>
using namespace std;

#include "clsScreen.h"
#include"clsUser.h"

class clsListUsersScreen : protected clsScreen
{

private:

	static void _PrintUserRecordLine(clsUser User)
	{
		cout << "\t| " << setw(10) << User.UserName;
		cout << "| " << setw(25) << User.FullName;
		cout << "| " << setw(10) << User.Phone;
		cout << "| " << setw(20) << User.Email;
		cout << "| " << setw(10) << User.Password;
		cout << "| " << setw(15) << User.Permissions;
	}

public:

	static void ShowUsersScreen()
	{
		vector <clsUser> vUsers =  clsUser::GetUsersList();
		string subTitle = "\t     (" + to_string(vUsers.size()) + ") User(s)";

		clsScreen::_DrawScreenHeader("\t   User list Screen", subTitle);

		cout << "\n\t____________________________________________________________";
		cout << "________________________________________\n\n";

		cout << "\t| " << setw(10) << "UserName";
		cout << "| " << setw(25) << "FullName";
		cout << "| " << setw(10) << "Phone";
		cout << "| " << setw(20) << "Email";
		cout << "| " << setw(10) << "Password";
		cout << "| " << setw(15) << "Permissions";

		cout << "\n\t____________________________________________________________";
		cout << "________________________________________\n\n";

		for (clsUser& U : vUsers)
		{
			_PrintUserRecordLine(U);
			cout << endl;
		}

		cout << "\t____________________________________________________________";
		cout << "________________________________________\n";
	}
};

