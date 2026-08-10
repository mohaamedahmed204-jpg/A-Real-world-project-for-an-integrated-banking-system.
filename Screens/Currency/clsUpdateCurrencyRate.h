#pragma once

#include <iomanip>
#include <iostream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUPdateCurrencyScreen : protected clsScreen {

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

    static void UpdateCurrencysList() {

        std::string Title = "\t  Update Currency Rate";
        _DrawScreenHeader(Title, "");
        
        clsCurrency Curr;

        std::string Code = clsInputValidate::ReadString("\nplease Enter Currency Code: ");
        Code = clsString::UpperAllString(Code);
        Curr = clsCurrency::FindByCode(Code);
        
        if(Curr.IsEmpty()) {
            std::cout << "\nCurrency Not Found :-(\n";
        } else {
            std::cout << "\nCurrency Found :-)\n\n";
            _PrintCurrencyCard(Curr);
            
            if( clsInputValidate::GeneralYesOrNo("Are You Sure You Want To Update The Rate Of This Currency y/n ? ") )
            {
                std::cout << "\nUpdate Currency Rate: \n";
                std::cout << "___________________________\n\n";
                float UpdateRate = clsInputValidate::ReadValidNumber<float>(0.0, 100000.0, "Enter New Rate: ");
                Curr.UpdateRate(UpdateRate);

                std::cout << "\nCurrency Rate Updated Successfully :-)\n\n";
                _PrintCurrencyCard(Curr);
            }
        }
    }
};
