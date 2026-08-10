#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen {
private:
    
    static void _PrintClient(clsBankClient Client) {
        std::cout << "\nClient Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << Client.GetFirstName();
        std::cout << "\nLastName    : " << Client.GetLastName();
        std::cout << "\nFull Name   : " << Client.FullName();
        std::cout << "\nEmail       : " << Client.GetEmail();
        std::cout << "\nPhone       : " << Client.GetPhone();
        std::cout << "\nAcc. Number : " << Client.AccountNumber();
        std::cout << "\nPassword    : " << Client.GetPinCode();
        std::cout << "\nBalance     : " << Client.GetAccountBalance();
        std::cout << "\n___________________\n";
    }

    static std::string _ReadAccountNumber() {
        std::string AccountNumber = "";
        std::cout << "\nPlease enter AccountNumber? ";
        std::cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen() {
        
        _DrawScreenHeader("\t   Withdraw Screen");
        std::string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            std::cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        Amount = clsInputValidate::ReadValidNumber<double>(1, 1000000, "\nPlease enter Withdraw amount? ");

        if(clsInputValidate::GeneralYesOrNo("\nAre you sure you want to perform this transaction? "))
        {
            if(Client1.Withdraw(Amount)) { 
                std::cout << "\nAmount Withdrew Successfully.\n";
                std::cout << "\nNew Balance Is: " << Client1.GetAccountBalance();
            }
            else {
               std::cout << "\nCannot withdraw, Insuffecient Balance!\n";
               std::cout << "\nAmout to withdraw is: " << Amount;
               std::cout << "\nYour Balance is: " << Client1.GetAccountBalance(); 
            }
        }
        else {
            std::cout << "\nOperation was cancelled.\n";
        }
    }
};
