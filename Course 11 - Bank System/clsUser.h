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
	int _Permessions = 0;

	//setters

	void _setUserName(int UserName)
	{
		_UserName = UserName;
	}
	void _setPassword(int Password)
	{
		_Password = Password;
	}
	void _setPermessions(int Permessions)
	{
		_Permessions = Permessions;
	}

	//getters

	string _getUserName()
	{
		return _UserName;
	}
	string _getPassword()
	{
		return _Password;
	}
	int _getPermessions()
	{
		return _Permessions;
	}

	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector <string> vUser = clsString::Split(Line,Seperator);
		clsUser User(_enMode::eUpdate, vUser[0], vUser[1], vUser[2], vUser[3],
			vUser[4], vUser[5], stoi(vUser[6]));

		return User;
	}

	string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User[0] + Seperator;
		UserRecord += User[1] + Seperator;
		UserRecord += User[2] + Seperator;
		UserRecord += User[3] + Seperator;
		UserRecord += User[4] + Seperator;
		UserRecord += User[5] + Seperator;

	}

	
public:

	//decspecs
	__declspec(property(get = _getUserName, put = _setUserName)) string UserName;
	__declspec(property(get = _getPassword, put = _setPassword)) string Password;
	__declspec(property(get = _getPermessions, put = _setPermessions)) int Permessions;


	clsUser(_enMode Mode,string FirstName, string LastName, 
		string Email, string Phone, string UserName, string Password, 
		int Permessions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permessions = Permessions;
	}

	clsUser Find(string UserName)
	{

	}

	clsUser Find(string UserName, string Password)
	{

	}


	static void AddNewUser()
	{

	}

	static void DeleteUser()
	{

	}

	bool IsUserExists(string UserName)
	{

	}

	void Save()
	{

	}

	
};

