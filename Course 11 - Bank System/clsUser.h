#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsString.h"
#include <string>
#include "clsDate.h"
using namespace std;

class clsUser : public clsPerson
{
public:
	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;

		// Constructor added to fix C26495 uninitialized member warning
		stLoginRegisterRecord() : DateTime(""), UserName(""), Password(""), Permissions(0) {}
	};

private:

	enum _enMode { eEmpty = 1, eUpdate = 2, eAddNew = 3 };

	//properties
	_enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions = 0;

	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector <string> vUser = clsString::Split(Line,Seperator);
		clsUser User(_enMode::eUpdate, vUser[0], vUser[1], vUser[2], vUser[3],
			vUser[4], vUser[5], stoi(vUser[6]));

		return User;
	}
	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += User.Password + Seperator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;
	}
	static vector <clsUser> _LoadUsersDataFromFile()
	{
		fstream MyFile;

		vector <clsUser> vUsers;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile,Line))
			{
				vUsers.push_back(_ConvertLineToUserObject(Line));
			}
			MyFile.close();
		}

		return vUsers;
	}
	static void _SaveUsersDataToFile(vector <clsUser>& vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsUser& U : vUsers)
			{
				if (U.MarkedForDeleted() == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
			
			MyFile.close();
		}
	}
	static void _AddDataLineToFile(string  DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}
	void _Update()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (C.UserName == this->UserName)
			{
				C = *this;
				_SaveUsersDataToFile(vUsers);
				return;
			}
		}
	
	}
	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(_enMode::eEmpty, "", "", "", "", "", "", 0);
	}

	string _PrepareLogInRecord(string delimiter = "#//#")
	{
		string stLineRecord = "";

		stLineRecord += clsDate::GetSystemDateTimeString() + delimiter;
		stLineRecord += UserName + delimiter;
		stLineRecord += Password + delimiter;
		stLineRecord += to_string(Permissions);

		return stLineRecord;
	}
	static stLoginRegisterRecord ConvertLoginRecordToStruct(string LineRecord)
	{
		vector <string> vRecord = clsString::Split(LineRecord,"#//#");

		stLoginRegisterRecord stRecord;
		stRecord.DateTime = vRecord[0];
		stRecord.UserName = vRecord[1];
		stRecord.Password = vRecord[2];
		stRecord.Permissions = stoi(vRecord[3]);

		return stRecord;
	}

public:
	clsUser(_enMode Mode,string FirstName, string LastName, 
		string Email, string Phone, string UserName, string Password, 
		int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	
	enum enPermissions
	{
		eAll = -1, 
		pListClients = 1,
		pAddNewClient = 2,
		pDeleteClient = 4,
		pUpdateClients = 8,
		pFindClient = 16,
		pTranactions = 32,
		pManageUsers = 64,
		pLoginRegister = 128
	};

	bool IsEmpty()
	{
		return (_Mode == _enMode::eEmpty);
	}
	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	//setters and getters
	void _setUserName(string UserName)
	{
		_UserName = UserName;
	}
	void _setPassword(string Password)
	{
		_Password = Password;
	}
	void _setPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	string _getUserName()
	{
		return _UserName;
	}
	string _getPassword()
	{
		return _Password;
	}
	int _getPermissions()
	{
		return _Permissions;
	}

	//decspecs
	__declspec(property(get = _getUserName, put = _setUserName)) string UserName;
	__declspec(property(get = _getPassword, put = _setPassword)) string Password;
	__declspec(property(get = _getPermissions, put = _setPermissions)) int Permissions;

	void Print()
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << this->FirstName;
		cout << "\nLastName    : " << this->LastName;
		cout << "\nFull Name   : " << this->FullName;
		cout << "\nEmail       : " << this->Email;
		cout << "\nPhone       : " << this->Phone;
		cout << "\nUser Name   : " << this->UserName;
		cout << "\nPassword    : " << this->Password;
		cout << "\nPermissions : " << this->Permissions;
		cout << "\n___________________\n";
	}

	static clsUser Find(string UserName)
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (C.UserName == UserName)
			{
				return C;
			}
		}

		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password)
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (C.UserName == UserName && C.Password == Password)
			{
				return C;
			}
		}

		return _GetEmptyUserObject();
	}


	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
	enSaveResults Save()
	{

		switch(_Mode)

		{
		case _enMode::eEmpty:
			return enSaveResults::svFaildEmptyObject;
			break;

		case _enMode::eUpdate:

			_Update();
			return enSaveResults::svSucceeded;
			break;

		case _enMode::eAddNew:
			if (IsUserExist(UserName) == true)
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				this->_Mode = _enMode::eUpdate;
				return enSaveResults::svSucceeded;

			}
			break;


		default:
			break;
		}
		
		{
			vector <clsUser> vUsers = _LoadUsersDataFromFile();

			for (clsUser& C : vUsers)
			{
				if (C.UserName == this->UserName)
				{
					C = *this;
					_SaveUsersDataToFile(vUsers);
					return enSaveResults::svSucceeded;
				}
			}
			return enSaveResults::svFaildUserExists;
		}
	}

	static bool IsUserExist(string UserName)
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (C.UserName == UserName)
			{
				return true;
			}
		}
		return false;
	}
	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (this->UserName == C.UserName)
			{
				C._MarkedForDelete = true;
				_SaveUsersDataToFile(vUsers);
				return true;
			}
		}


		return false;
	}
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(_enMode::eAddNew, "", "", "", "", UserName, "", 0);
	}
	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		else if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}
	void RegisterLogin()
	{
		fstream MyFile;

		MyFile.open("Logins Log.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string stLoginLine = _PrepareLogInRecord();
			MyFile << stLoginLine << endl;
			MyFile.close();
		}

	}
	static vector <stLoginRegisterRecord> LoadLoginRecordsList()
	{
		fstream MyFile;
		MyFile.open("Logins Log.txt", ios::in);

		vector <stLoginRegisterRecord> vLogin;

		if (MyFile.is_open())
		{
			string LineRecord;
			while (getline(MyFile, LineRecord))
			{
				vLogin.push_back(ConvertLoginRecordToStruct(LineRecord));
			}

			MyFile.close();
		}

		return vLogin;
	}

};

