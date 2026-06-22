#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
	static void PrintTransferLogRecord(clsBankClient::stTransferLogRecord stTransferLogRecord)
	{
        cout << setw(8) << left << "" << "| " << setw(23) << left << stTransferLogRecord.DateAndTime;
        cout << "| " << setw(8) << left << stTransferLogRecord.SenderAccountNumber;
        cout << "| " << setw(8) << left << stTransferLogRecord.ReceiverAccountNumber;
        cout << "| " << setw(8) << left << stTransferLogRecord.Amount;
        cout << "| " << setw(10) << left << stTransferLogRecord.SenderNewBalance;
        cout << "| " << setw(10) << left << stTransferLogRecord.ReceiverNewBalance;
        cout << "| " << setw(8) << left << stTransferLogRecord.AdminUsername;
    }

public:

	static void ShowTransferLogScreen()
	{

        vector <clsBankClient::stTransferLogRecord> vLogs;
        vLogs = clsBankClient::LoadTransferLog();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vLogs.size()) + ") Record(s).";

        _DrawScreenHeader(Title,SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else
        {
            for (clsBankClient::stTransferLogRecord& stLog : vLogs)
            {
                PrintTransferLogRecord(stLog);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

