#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTranferScreen : protected clsScreen {

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

    static std::string _ReadAccountNumber(const std::string & FromOrTo = "") {
        std::string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number To Transfer " + FromOrTo + ": ");
        return AccountNumber;
    }

public:

    static void ShowTransferScreen() {
        _DrawScreenHeader("\t   Transfer Screen");

        std::string AccountNumber1 = _ReadAccountNumber("From");

        while (!clsBankClient::IsClientExist(AccountNumber1)) {
            std::cout << "\nClient with [" << AccountNumber1 << "] does not exist.\n";
            AccountNumber1 = _ReadAccountNumber("From");
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber1);
        _PrintClient(Client1);

        //----------------------------------------------------------------------------------------------//

        std::string AccountNumber2 = _ReadAccountNumber("To");

        while (!clsBankClient::IsClientExist(AccountNumber2)) {
            std::cout << "\nClient with [" << AccountNumber2 << "] does not exist.\n";
            AccountNumber2 = _ReadAccountNumber("To");
        }

        clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
        _PrintClient(Client2);

        double Amount = 0, limit = Client1.GetAccountBalance();
        Amount = clsInputValidate::ReadValidNumber<double>(1, limit, "\nPlease enter Transfer amount between (1-"+ std::to_string(limit) + "): ");

        if(clsInputValidate::GeneralYesOrNo("\nAre you sure you want to perform this transaction? ")) {
            Client1.Transfer(Amount, Client2);
            Client1._TransferLogins(Client1, Client2, Amount);
            std::cout << "\nTransfer done Successfully.\n";
            _PrintClient(Client1);
            _PrintClient(Client2);
        }
        else {
            std::cout << "\nOperation was cancelled.\n";
        }
    }
};
