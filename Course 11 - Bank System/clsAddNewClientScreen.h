#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{

private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter AccountBalance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber();


    }

    static void _AddNewClient()
    {
        string AccountNumber = "";

        cout << "Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client Already Exist, Enter another account number: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults Save;
        Save = NewClient.Save();

        switch (Save)
        {

        case clsBankClient::enSaveResults::svSucceeded:

            cout << "Client Added Successfuly\n";
            NewClient.Print();
            break;

        case clsBankClient::enSaveResults::svFailedEmptyObject:

            cout << "Error Account was not saved because it was Empty\n";
            break;

        case clsBankClient::enSaveResults::svFailedAccountNmuberExist:

            cout << "Error Accout was not saved because Account Number is used\n";
            break;

        default:
            break;

        }

    }

public:

    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue 
        }

        clsScreen::_DrawScreenHeader("\tAdd New Client Screen");

        _AddNewClient();
    }
};

