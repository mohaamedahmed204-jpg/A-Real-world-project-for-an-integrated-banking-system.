#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen {

private:
    static void PrintCurrencyRecordLine(clsCurrency Currency ) {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(29) << std::left << Currency.Country();
        std::cout << "| " << std::setw(20) << std::left << Currency.CurrencyCode();
        std::cout << "| " << std::setw(40) << std::left << Currency.CurrencyName();
        std::cout << "| " << std::setw(20) << std::left << Currency.Rate();
    }

public:
    static void ShowCurrencysList() {

        std::vector <clsCurrency> vCurrency  = clsCurrency::GetCurrenciesList();
        std::string Title = "\t  Currencies List Screen";
        std::string SubTitle ="\t    (" + std::to_string(vCurrency .size()) + ") Currency(s).";

        _DrawScreenHeader(Title, SubTitle);
        
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________________\n" << std::endl;

        std::cout <<  std::setw(8) << std::left << "" << "| " << std::left << std::setw(29) << "Country";
        std::cout << "| " << std::left << std::setw(20) << "Currency Code";
        std::cout << "| " << std::left << std::setw(40) << "Currency Name";
        std::cout << "| " << std::left << std::setw(20) << "Rate/(1$)";
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________________\n" << std::endl;

        if (vCurrency .size() == 0)
            std::cout << "\t\t\t\tNo Currencys Available In the System!";
        else
            for (clsCurrency Currency  : vCurrency ) {
                PrintCurrencyRecordLine(Currency );
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________________\n" << std::endl;
    }

};
