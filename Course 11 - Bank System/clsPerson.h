#pragma once
#include <iostream>
using namespace std;

class clsPerson
{

private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;


public:

	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	
	//setters
	void set_FirstName(string FirstName) { _FirstName = FirstName; }
	void set_LastName(string LastName) { _LastName = LastName; }
	void set_Email(string Email) { _Email = Email; }
	void set_Phone(string Phone) { _Phone = Phone; }

	//getters
	string get_FirstName() { return _FirstName; }
	string get_LastName() { return _LastName; }
	string get_Email() { return _Email; }
	string get_Phone() { return _Phone; }
	string get_FullName() { return _FirstName + " " + _LastName; }

	//declspec 
	__declspec(property(get = get_FirstName, put = set_FirstName))string FirstName;
	__declspec(property(get = get_LastName, put = set_LastName))string LastName;
	__declspec(property(get = get_Email, put = set_Email))string Email;
	__declspec(property(get = get_Phone, put = set_Phone))string Phone;
	__declspec(property(get = get_FullName))string FullName;

	void Print()
	{
		cout << "Info";

		cout << "\n_______________________________";
		cout << "\nFirst Name : " << FirstName;
		cout << "\nLast Name  : " << LastName;
		cout << "\nFull Name  : " << FullName;
		cout << "\nEmail      : " << Email;
		cout << "\nPhone      : " << Phone;
		cout << "\n_______________________________\n";
	}

	void SendEmail(string Subject, string Body)
	{
		cout << "\nThe following message sent succefully to email: " << Email;
		cout << "\nSubject: " << Subject;
		cout << "\nBody: " << Body << endl;
	}

	void SendSMS(string Message)
	{
		cout << "\nThe following message sent succefully to phone: " << Phone;
		cout << endl << Message << endl;
	}
};




