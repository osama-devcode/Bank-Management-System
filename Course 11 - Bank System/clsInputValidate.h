#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:

	
	template <typename T> static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}
	template <typename T> static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		T Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number =  ReadNumber <T> ()  ;

		while (!IsNumberBetween <T> (Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber <T> ();
		}
		return Number;
	}

	static string ReadString(string message = "")
	{
		string  S1 = "";
		cout << message;
		getline(cin >> ws, S1);
		return S1;
	}

	static bool IsDateBetween(const clsDate& Date, const clsDate& From, const clsDate& To)
	{
		clsDate ActualFrom = From;
		clsDate ActualTo = To;

		if (clsDate::IsDate1AfterDate2(ActualFrom, ActualTo))
		{
			clsDate temp = ActualTo;
			ActualTo = ActualFrom;
			ActualFrom = temp;
		}

		return (!clsDate::IsDate1BeforeDate2(Date, From) && !clsDate::IsDate1AfterDate2(Date, To));
	}
	static bool IsValidDate(const clsDate& Date)
	{
		return clsDate::IsValidDate(Date);
	}

};