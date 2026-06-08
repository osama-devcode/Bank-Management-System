#include <iostream> 
#include"clsBankClient.h" 
#include"clsInputValidate.h"
#include"clsUtil.h"
#include <iomanip>
#include "clsMainScreen.h" 
using namespace std;

void ReadClientInfo(clsBankClient &Client)
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
    Client.AccountBalance = clsInputValidate::ReadFloatNumber();


}

void UpdateClient()
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
    ReadClientInfo(Client1);


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

void PrintClientRecordBalanceLine(clsBankClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(20) << left << Client.FullName;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowBalancesList()
{
    vector <clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\tBalances List (" << vClients.size() << ") Client(s)";

    cout << "\n_____________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(20) << "Full Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_____________________________________________________________\n\n";


    if (vClients.size() == 0)
    {
        cout << "No Clients Available In The System!";
        cout << "\n_____________________________________________________________\n\n";
    }
    else
    {
        for (clsBankClient& C : vClients)
        {
            PrintClientRecordBalanceLine(C);
            cout << endl;
        }

        double TotalBalances = clsBankClient::GetTotalBalances();
        cout << "\n_____________________________________________________________\n\n";
        cout << "\t\t\tTotal Balances = " << TotalBalances;
        cout << "\n\t\t\t" << clsUtil::NumberToText(TotalBalances);

    }

   

}




int main()
{

    clsMainScreen::ShowMainMenue();

    system("pause>0");
    return 0;
}

