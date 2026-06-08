#include <iostream> 
#include "clsBankClient.h" 
#include "clsMainScreen.h" 
#include "clsUtil.h"
using namespace std;


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

