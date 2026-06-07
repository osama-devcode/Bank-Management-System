#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

    static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(20) << left << Client.FullName;
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }

public:

    static void ShowClientsList()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t Client List Screen";
        string subTitle = "\t (" + to_string(vClients.size()) + ") Client(s)";
        clsScreen::_DrawScreenHeader(Title, subTitle);

        cout << "\n_______________________________________________________";
        cout << "__________________________________________________\n\n";

        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";

        cout << "\n_________________________________________";
        cout << "________________________________________________________________\n\n";

        if (vClients.size() == 0)
        {
            cout << "No Clients Available In The System!";
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordLine(C);
                cout << endl;
            }
        }

        cout << "\n_______________________________________________________";
        cout << "__________________________________________________\n";

    }

};

