#pragma once
#include <iostream>
using namespace std;
#include "clsUser.h"
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
	static void _PrintUserLoginRecord(clsUser::stLoginRegisterRecord& stLoginRecord)
	{
		cout << "\t| " << setw(22) << stLoginRecord.DateTime;
		cout << "| " << setw(10) << stLoginRecord.UserName;
		cout << "| " << setw(10) << stLoginRecord.Password;
		cout << "| " << setw(15) << stLoginRecord.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;// this will exit the function and it will not continue 
		}

		_DrawScreenHeader("Login Register List Screen");

		cout << "\n\t____________________________________________________________";
		cout << "________________________________________\n\n";

		cout << "\t| " << setw(22) << "Date and Time";
		cout << "| " << setw(10) << "UserName";
		cout << "| " << setw(10) << "Password";
		cout << "| " << setw(15) << "Permissions";

		cout << "\n\t____________________________________________________________";
		cout << "________________________________________\n\n";

		vector <clsUser::stLoginRegisterRecord> vLogins = clsUser::LoadLoginRecordsList();

		for (clsUser::stLoginRegisterRecord &stLogin :vLogins)
		{
			_PrintUserLoginRecord(stLogin);
			cout << endl;
		}

		cout << "\t____________________________________________________________";
		cout << "________________________________________\n";
	}
};

