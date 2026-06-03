#pragma once
#include <iostream>
using namespace std;

class clsScreen
{

protected:

	static void _DrawScreenHeader(string Title = "Main Screen", string SubTitle = "")
	{
		cout << "   _____________________________________\n\n";
		cout << setw(37) << left << Title << endl;
		
		if (SubTitle != "")
		{
			cout << setw(37) << left << SubTitle << endl;
		}
		cout << "   _____________________________________\n\n";

	}
};

