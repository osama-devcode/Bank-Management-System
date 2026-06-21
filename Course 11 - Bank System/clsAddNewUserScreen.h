#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen

{
private:

	static void _ReadUserInfo(clsUser& User) 
	{
		cout << "\nEnter First Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();
		
		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions : ";
		User.Permissions = _ReadPermissionsToSet();
	
	}

	static int _ReadPermissionsToSet()
	{
		char Answer;
		int Permissions = 0;

		cout << "do you want to give the user full permissions? [y/n]?";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Clients List? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd new client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		cout << "\nfind Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nShow Login Register? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\tAdd New User Screen");

		string UserName;
		cout << "\nEnter username: ";
		UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUsername already exist choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(User);

		clsUser::enSaveResults svResult = User.Save();

		switch (svResult)
		{
		case clsUser::enSaveResults::svSucceeded:
			cout << "User Added Successfuly\n";
			break;

		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "\nError User was not saved because it's Empty";
			break;

		case clsUser::enSaveResults::svFaildUserExists:
			cout << "\nError User was not saved because UserName is used!\n";
			break;
		}
		
		User.Print();

	}

};

