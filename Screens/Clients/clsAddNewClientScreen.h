#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
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

public:

    static void ShowAddNewClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Add New Client Screen");

        std::string AccountNumber = "";
        AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");

        while (clsBankClient::IsClientExist(AccountNumber)) {
            AccountNumber = clsInputValidate::ReadString("\nAccount Number Is Already Used, Choose another one: ");
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        clsBankClient::ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult) {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                std::cout << "\nAccount Addeded Successfully :-)\n";
                _PrintClient(NewClient);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                std::cout << "\nError account was not saved because it's Empty";
                break;

            }
            case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            {
                std::cout << "\nError account was not saved because account number is used!\n";
                break;

            }
        }
    }
};
