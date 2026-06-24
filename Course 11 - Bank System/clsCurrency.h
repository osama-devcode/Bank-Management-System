#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsCurrency
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;

    string _Country = "";
    string _CurrencyCode = "";
    string _CurrencyName = "";
    float _Rate = 0;

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#") 
    {
        vector <string> vCurrency;
        vCurrency =  clsString::Split(Line, Seperator);

        clsCurrency Currency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
        return Currency;
    }

    static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") 
    {
        string Line = "";

        Line += Currency.Country() + Seperator;
        Line += Currency.CurrencyCode() + Seperator;
        Line += Currency.CurrencyName() + Seperator;
        Line += to_string(Currency.Rate());

        return Line;
    }

    static vector<clsCurrency> _LoadCurrencysDataFromFile() 
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);
        
        vector <clsCurrency> vCurrencies;
        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                vCurrencies.push_back(_ConvertLinetoCurrencyObject(Line));
            }

            MyFile.close();
        }

        return vCurrencies;
    }

    static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);
       
        if(MyFile.is_open())
        {
            string Line = "";

            for (clsCurrency& C : vCurrencies)
            {
                Line = _ConverCurrencyObjectToLine(C);
                MyFile << Line << endl;
            }

            MyFile.close();
        }

    }

    void _Update() 
    {
        vector <clsCurrency> vCurrencies = _LoadCurrencysDataFromFile();

        for (clsCurrency& C : vCurrencies)
        {
            if (C.Country() == this->Country())
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyDataToFile(vCurrencies);
    }

    static clsCurrency _GetEmptyCurrencyObject() 
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
   
    clsCurrency(enMode Mode, string Country, 
        string CurrencyCode, string CurrencyName, float Rate) 
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    static vector <clsCurrency> GetAllUSDRates() 
    {
        return _LoadCurrencysDataFromFile();
    }

    bool IsEmpty() 
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country() 
    {
        return _Country;
    }

    string CurrencyCode() 
    {
        return _CurrencyCode;
    }

    string CurrencyName() 
    {
        return _CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        this->_Rate = NewRate;
        _Update();
    }

    float Rate() 
    {
        return _Rate;
    }

    static clsCurrency FindByCode(string CurrencyCode) 
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);


        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

                if (clsString::UpperAllString(Currency.CurrencyCode()) == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

        }

        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country) 
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);


        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

                if (clsString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }


        }

        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode) 
    {
        clsCurrency Currency = FindByCode(CurrencyCode);
        return (!Currency.IsEmpty());
    }

    static vector<clsCurrency> GetCurrenciesList() 
    {
        return _LoadCurrencysDataFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());

    }
};