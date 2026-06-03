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

void AddNewClient()
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

    ReadClientInfo(NewClient);
    
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

void DeleteClient()
{
    string AccountNumber = "";
    
    cout << "Enter The Account number of the client you want to delete: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "Account Number is not fount, Please enter the right one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    char Answer = 'N';

    cout << "\n\nAre you sure you want to delete this client y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        if(Client.Delete())
        {
            cout << "\nClient Deleted Successfuly.\n";

            Client.Print();
        }
        else
        {
            cout << "\nError client was not deleted.\n";
        }

    }
   

     
}

void PrintClientRecordLine(clsBankClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(20) << left << Client.FullName;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(20) << left << Client.Email;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowClientsList()
{
    vector <clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s)";
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
            PrintClientRecordLine(C);
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________";
    cout << "__________________________________________________\n";

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

