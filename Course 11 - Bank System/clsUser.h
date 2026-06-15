#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsString.h"
#include <string>
using namespace std;

class clsUser : public clsPerson
{
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

		if (this->_Mode == _enMode::eEmpty)
		{
			return enSaveResults::svFaildEmptyObject;
		}
		else
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

};

