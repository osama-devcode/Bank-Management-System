#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
class clsUpdateClientScreen : protected clsScreen
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
        Client.AccountBalance = clsInputValidate::ReadNumber <float> ();


    }

    static void _UpdateClient()
    {
        string AccountNumber = "";
        cout << "Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is not fount, Please enter the right one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        Client1.Print();

        cout << "\n\nUpdate Client Info::";
        cout << "\n___________________\n";
        _ReadClientInfo(Client1);


        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client1.Save();

        switch (SaveResult)
        {

        case clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << "Error account was not saved because it was empty\n";

            break;

        case clsBankClient::enSaveResults::svSucceeded:
            cout << "Account Updated Succesfuly :)\n";
            Client1.Print();
            break;

        default:
            break;
        }

    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue 
        }
        _DrawScreenHeader("\tUpdate Client Screen");

        _UpdateClient();
    }
};

