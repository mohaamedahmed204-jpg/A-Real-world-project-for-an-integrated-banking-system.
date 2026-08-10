#pragma once

#include <iomanip>
#include <iostream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen {

private:
    static void _PrintCurrencyCard(clsCurrency Currency) {
        std::cout << "Currency Card:\n";
        std::cout << "______________________________________\n\n";
        std::cout << "Country     : " << Currency.Country() << '\n';
        std::cout << "Code        : " << Currency.CurrencyCode() << '\n';
        std::cout << "Name        : " << Currency.CurrencyName() << '\n';
        std::cout << "Rate(1$) =  : " << Currency.Rate() << '\n';
        std::cout << "______________________________________\n\n";
    }

    static void _ReadValidCode(clsCurrency &Curr, const string &Order) {
        bool FirstTime = true;
        do {
            if(!FirstTime) std::cout << "Please Enter valid Code\n";
            std::string Code = clsInputValidate::ReadString("\nplease Enter Currency" + Order + " Code: ");
            Code = clsString::UpperAllString(Code);
            Curr = clsCurrency::FindByCode(Code);
            FirstTime = false;
            
        } while( Curr.IsEmpty() );
    }

public:

    static void CalculatorCurrencys() {
        
        do {

            system("cls");

            std::string Title = "\t   Currency Calculator Screen";
            _DrawScreenHeader(Title, "");

            clsCurrency Curr1, Curr2;
            _ReadValidCode(Curr1, "1"), _ReadValidCode(Curr2, "2");
            
            float ExchangeAmount = clsInputValidate::ReadValidNumber<float>(0.0, 100000000, "\nEnter Amount To Exchange: ");
            
            std::cout << "\nConvert From:\n";
            _PrintCurrencyCard(Curr1);

            std::cout << ExchangeAmount << ' ' << Curr1.CurrencyCode() << " = " << Curr1.ConvertToUSD(ExchangeAmount) << ' ' << "USD\n\n";

            if(Curr2.CurrencyCode() != "USD") {
                std::cout << "\nConverting From USD To:\n";
                _PrintCurrencyCard(Curr2);

                std::cout << ExchangeAmount << ' ' << Curr1.CurrencyCode() << " = "
                << Curr1.ConvertToOtherCurrency(ExchangeAmount, Curr2) << ' ' << Curr2.Country() << "\n\n";
            }

        } while( clsInputValidate::GeneralYesOrNo("Do You Want To Perform Another Calculation? ") );
    }
};
