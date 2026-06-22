#pragma once 
#include<iostream> 
#include"clsPerson.h" 
#include"clsString.h" 
#include <vector> 
#include <string> 
#include <fstream> 
#include "Global.h"
using namespace std;

class clsBankClient : public clsPerson
{
public:
    struct stTransferLogRecord
    {
        string DateAndTime = "";
        string SenderAccountNumber = "";
        string ReceiverAccountNumber = "";
        double Amount = 0;
        double SenderNewBalance = 0;
        double ReceiverNewBalance = 0;
        string AdminUsername = "";
    };

private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    //variables 
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    double _AccountBalance;
    bool _MarkedForDelete = false;


    //other functions 
    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
    {
        vector <string> vClientData;

        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
            vClientData[2], vClientData[3], vClientData[4], vClientData[5], (double)stod(vClientData[6]));
    }
    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") 
    {
        return Client.get_FirstName()
            + Seperator + Client.get_LastName()
            + Seperator + Client.get_Email()
            + Seperator + Client.get_Phone()
            + Seperator + Client._AccountNumber
            + Seperator + Client._PinCode
            + Seperator + to_string(Client._AccountBalance);
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static vector<clsBankClient>_LoadClientDataFromFile()
    {
        vector <clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while(getline(MyFile,Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;
    }
    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }
    static void _SaveClientsDataToFile(vector<clsBankClient>& vClients) 
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            string DataLine;

            for (clsBankClient& C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
                
            }

            MyFile.close();
        }

    }
   
    string _PrepareTransferLogRecord(clsBankClient ReceiverClient, double Amount, string Seperator = "#//#")
    {
        string LineRecord = "";
        LineRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LineRecord += AccountNumber + Seperator;
        LineRecord += ReceiverClient.AccountNumber + Seperator;
        LineRecord += to_string(Amount) + Seperator;
        LineRecord += to_string(AccountBalance) + Seperator;
        LineRecord += to_string(ReceiverClient.AccountBalance) + Seperator;
        LineRecord += CurrentUser.UserName;

        return LineRecord;
    }
    void _RegisterTransferLog(clsBankClient ReceiverClient, double Amount)
    {
        fstream MyFile;
        MyFile.open("Transfer Log.txt", ios::out);
        if (MyFile.is_open())
        {
            string LineLog = _PrepareTransferLogRecord(ReceiverClient, Amount);
            MyFile << LineLog << endl;
            MyFile.close();
        }

    }
    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferLogRecord TransferLogRecord;

        vector <string> vTransferLogRecordLine = clsString::Split(Line, Seperator);
        TransferLogRecord.DateAndTime = vTransferLogRecordLine[0];
        TransferLogRecord.SenderAccountNumber = vTransferLogRecordLine[1];
        TransferLogRecord.ReceiverAccountNumber = vTransferLogRecordLine[2];
        TransferLogRecord.Amount = stod(vTransferLogRecordLine[3]);
        TransferLogRecord.SenderNewBalance = stod(vTransferLogRecordLine[4]);
        TransferLogRecord.ReceiverNewBalance = stod(vTransferLogRecordLine[5]);
        TransferLogRecord.AdminUsername = vTransferLogRecordLine[6];

        return TransferLogRecord;

    }

    void _Update()
    {
        vector <clsBankClient> vClients;
        vClients = _LoadClientDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C = *this;
            }
        }

        _SaveClientsDataToFile(vClients);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }


public:

    //constructors 
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
        , string AccountNumber, string PinCode, double AccountBalance)
        :clsPerson(FirstName, LastName, Email, Phone) {

        this->_Mode = Mode;
        this->_AccountNumber = AccountNumber;
        this->_PinCode = PinCode;
        this->_AccountBalance = AccountBalance;
    }

    //setters 
    void set_Mode(enMode Mode) { _Mode = Mode; }
    void set_AccountNumber(string AccountNumber) {_AccountNumber = AccountNumber; }
    void set_PinCode(string PinCode) {_PinCode = PinCode; }
    void set_AccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }

    //getters 
    enMode get_Mode() { return this->_Mode; }
    string get_AccountNumber() { return this->_AccountNumber; }
    string get_PinCode() { return this->_PinCode; }
    double get_AccountBalance() { return this->_AccountBalance; }

    //declspec 
    __declspec(property(get = get_Mode, put = set_Mode))enMode Mode;
    __declspec(property(get = get_AccountNumber, put = set_AccountNumber))string AccountNumber;
    __declspec(property(get = get_PinCode, put = set_PinCode))string PinCode;
    __declspec(property(get = get_AccountBalance, put = set_AccountBalance))double AccountBalance;

    //client functions 
    bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n-------------------";
        cout << "\nFirstName   :" << get_FirstName();
        cout << "\nLastName    :" << this->get_LastName();
        cout << "\nFullName    :" << this->get_FullName();;
        cout << "\nEmail       :" << this->get_Email();
        cout << "\nPhone       :" << this->get_Phone();
        cout << "\nAcc. Number :" << this->_AccountNumber;
        cout << "\nPassword    :" << this->_PinCode;
        cout << "\nBalance     :" << this->_AccountBalance;
        cout << "\n-------------------";
    }

    static clsBankClient Find(string AccountNumber) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open()) 
        {

            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client._AccountNumber == AccountNumber) 
                {
                    MyFile.close();
                    return Client;
                }

            }
        }

        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber, string PinCode) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open()) 
        {

            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client._AccountNumber == AccountNumber && Client._PinCode == PinCode) 
                {
                    MyFile.close();
                    return Client;
                }

            }
            return _GetEmptyClientObject();
        }
    }

    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNmuberExist = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {

        case clsBankClient::EmptyMode:
       
            return enSaveResults::svFailedEmptyObject;
            break;

        case clsBankClient::UpdateMode:
        
            _Update();
            return enSaveResults::svSucceeded;
            break;
        
        case clsBankClient::AddNewMode:

            if (IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFailedAccountNmuberExist;
            }
            else
            {
                _AddNew();
                return enSaveResults::svSucceeded;
            }

        default:
            return enSaveResults::svFailedEmptyObject;
            break;
        }
    }

    static bool IsClientExist(string AccountNumber) {

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    static clsBankClient GetAddNewClient(string AccountNumber)
    {
        return clsBankClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }
    bool Delete()
    {
        vector <clsBankClient> _vClients;

        _vClients = _LoadClientDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);
        *this = _GetEmptyClientObject();

        return true;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient& C : vClients)
        {
            TotalBalances += C.AccountBalance;
        }

        return TotalBalances;
    }
    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
        
    }
    bool Transfer(double Amount, string AccountNumber)
    {
        if (this->Withdraw(Amount) == true)
        {
            clsBankClient Client = Find(AccountNumber);
            Client.Deposit(Amount);
            _RegisterTransferLog(Client, Amount);
            return true;
        }
        return false;
    }

    static vector <stTransferLogRecord> LoadTransferLog()
    {
        fstream MyFile;
        MyFile.open("Transfer Log.txt", ios::in);
        vector <stTransferLogRecord> vLogs;

        if (MyFile.is_open())
        {
            stTransferLogRecord stTransferLog;
            string LineLog = "";

            while (getline(MyFile, LineLog))
            {
                stTransferLog = _ConvertTransferLogLineToRecord(LineLog);
                vLogs.push_back(stTransferLog);
            }

            MyFile.close();
        }

        return vLogs;
    }

};
