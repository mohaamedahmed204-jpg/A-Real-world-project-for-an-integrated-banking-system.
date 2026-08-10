#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "clsString.h"

class clsCurrency {
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;

	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(std::string Line, std::string Seperator = "#//#") {
        std::vector<std::string> vCurrencyData = clsString::SplitEachWordInVector(Line, Seperator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
    }

    static std::string _ConverCurrencyObjectToLine(clsCurrency Currency, std::string Seperator = "#//#") {
        std::string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Seperator;
        stCurrencyRecord += Currency.CurrencyCode() + Seperator;
        stCurrencyRecord += Currency.CurrencyName() + Seperator;
        stCurrencyRecord += std::to_string(Currency.Rate());
       
        return stCurrencyRecord;
    }

    static std::vector <clsCurrency> _LoadCurrencysDataFromFile() {
        std::vector <clsCurrency> vCurrencys;
        std::fstream MyFile;
        MyFile.open("Currencies.txt", std::ios::in); //read Mode

        if (MyFile.is_open()) {
            std::string Line;

            while (getline(MyFile, Line)) {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                vCurrencys.push_back(Currency);
            }
            MyFile.close();
        }
        return vCurrencys;
    }

    static void _SaveCurrencyDataToFile(std::vector <clsCurrency> vCurrencys) {
        std::fstream MyFile;
        MyFile.open("Currencies.txt", std::ios::out); //overwrite

        std::string DataLine;

        if (MyFile.is_open()) {
            for (clsCurrency C : vCurrencys) {
                 DataLine = _ConverCurrencyObjectToLine(C);
                    MyFile << DataLine << std::endl;
            }
            MyFile.close();
        }
    }

    void _Update() {
        std::vector <clsCurrency> _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (clsCurrency& C : _vCurrencys) {
            if (C.CurrencyCode() == CurrencyCode()) {
                C = *this;
                break;
            }
        }
        _SaveCurrencyDataToFile(_vCurrencys);
    }

    static clsCurrency _GetEmptyCurrencyObject() {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:

	clsCurrency(enMode Mode, std::string Country, std::string CurrencyCode, std::string CurrencyName, float Rate) {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
	}

    clsCurrency() {
        _Mode = enMode::EmptyMode;
        _Country = "";
        _CurrencyCode = "";
        _CurrencyName = "";
        _Rate = 0;
	}

	static std::vector <clsCurrency> GetAllUSDRates() {
        return _LoadCurrencysDataFromFile();
	}

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    std::string Country() {
        return _Country;
    }
 
    std::string CurrencyCode() {
        return _CurrencyCode;
    }
    
    std::string CurrencyName() {
        return _CurrencyName;
    }
   
    void UpdateRate(float NewRate) {
        _Rate = NewRate;
        _Update();
    }

    float Rate() {
        return _Rate;
    }

    static clsCurrency FindByCode(std::string CurrencyCode) {
     
        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        std::fstream MyFile;
        MyFile.open("Currencies.txt", std::ios::in);//read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode) {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(std::string Country) {
        Country = clsString::UpperAllString(Country);

        std::fstream MyFile;
        MyFile.open("Currencies.txt", std::ios::in);//read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                std::string limit = Currency.Country();
                if ( clsString::UpperAllString(limit) == Country) {
                    MyFile.close();
                    return Currency;
                }
            }
          MyFile.close();
        }
      return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(std::string CurrencyCode) {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());
    }

    static std::vector <clsCurrency> GetCurrenciesList() {
      return _LoadCurrencysDataFromFile();
    }

    float ConvertToUSD(float Amount) {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD") {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());
    }
};

