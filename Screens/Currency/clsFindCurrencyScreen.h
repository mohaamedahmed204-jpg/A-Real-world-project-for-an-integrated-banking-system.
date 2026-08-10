#pragma once

#include <iomanip>
#include <iostream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen {

private:
    static void _PrintCurrencyCard(clsCurrency Currency ) {
        std::cout << "Currency Card:\n";
        std::cout << "______________________________________\n\n";
        std::cout << "Country     : " << Currency.Country() << '\n';
        std::cout << "Code        : " << Currency.CurrencyCode() << '\n';
        std::cout << "Name        : " << Currency.CurrencyName() << '\n';
        std::cout << "Rate(1$) =  : " << Currency.Rate() << '\n';
        std::cout << "______________________________________\n\n";
    }

public:

    enum eCodeOrCountry {eCode = 1, eCountry = 2};

    static void FindCurrencysList() {

        std::string Title = "\t  Find Currency Screen";
        _DrawScreenHeader(Title, "");
        
        short Choose = clsInputValidate::ReadValidNumber<short>(1, 2, "\nFind By: [1] Code or [2] Country ? ");
        clsCurrency Curr;

        if(Choose == eCodeOrCountry::eCode) {
            std::string Code = clsInputValidate::ReadString("\nplease Enter Currency Code: ");
            Code = clsString::UpperAllString(Code);
            Curr = clsCurrency::FindByCode(Code);
        }
        else if(Choose == eCodeOrCountry::eCountry) {
            std::string Country = clsInputValidate::ReadString("\nplease Enter Country Name: ");
            Country = clsString::LowerAllString(Country);
            Country = clsString::UpperCaseEachFirstLetterInWord(Country);
            Curr = clsCurrency::FindByCountry(Country);
        }

        if(Curr.IsEmpty()) {
            std::cout << "\nCurrency Not Found :-(\n";
        } else {
            std::cout << "\nCurrency Found :-)\n\n";
            _PrintCurrencyCard(Curr);
        }
    }
};
