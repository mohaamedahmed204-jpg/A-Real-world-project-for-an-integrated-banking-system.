#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen :protected clsScreen {
private:
    
    static void _PrintClient(clsBankClient Client) {
        std::cout << "\nClient Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << Client.GetFirstName();
        std::cout << "\nFull Name   : " << Client.FullName();
        std::cout << "\nEmail       : " << Client.GetEmail();
        std::cout << "\nPhone       : " << Client.GetPhone();
        std::cout << "\nAcc. Number : " << Client.AccountNumber();
        std::cout << "\nPassword    : " << Client.GetPinCode();
        std::cout << "\nBalance     : " << Client.GetAccountBalance();
        std::cout << "\n___________________\n";

    }

public:

    static void ShowUpdateClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        std::string AccountNumber = "";
        AccountNumber = clsInputValidate::ReadString("\nPlease Enter client Account Number: ");

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        if (clsInputValidate::GeneralYesOrNo("\nAre you sure you want to update this client y/n? ")) {

            std::cout << "\n\nUpdate Client Info:";
            std::cout << "\n____________________\n";

            clsBankClient::ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client1.Save();

            switch (SaveResult) {
                case  clsBankClient::enSaveResults::svSucceeded:
                {
                    std::cout << "\nAccount Updated Successfully :-)\n";
                
                    _PrintClient(Client1);
                    break;
                }
                case clsBankClient::enSaveResults::svFaildEmptyObject:
                {
                    std::cout << "\nError account was not saved because it's Empty";
                    break;
                }
            }
        }
    }
};
