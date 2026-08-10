#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen {
private:
    static void PrintClientRecordBalanceLine(clsBankClient Client) {
        std::cout << std::setw(25) << std::left << "" << "| " << std::setw(15) << std::left << Client.AccountNumber();
        std::cout << "| " << std::setw(40) << std::left << Client.FullName();
        std::cout << "| " << std::setw(12) << std::left << Client.GetAccountBalance();
    }

public:

    static void ShowTotalBalances() {
        
        std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        std::string Title = "\t  Balances List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        std::cout << std::setw(25) << std::left << "\n\t\t_______________________________________________________";
        std::cout << "__________________________\n" << std::endl;

        std::cout << std::setw(25) << std::left << "| " << std::left << std::setw(17) << "Accout Number";
        std::cout << "| " << std::left << std::setw(40) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Balance";
        std::cout << std::setw(25) << std::left << "\n\t\t_______________________________________________________";
        std::cout << "__________________________\n" << std::endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else {
            for (clsBankClient Client : vClients) {
                PrintClientRecordBalanceLine(Client);
                std::cout << std::endl;
            }
        }

        std::cout << std::setw(25) << std::left << "" << "\n\t\t_______________________________________________________";
        std::cout << "__________________________\n" << std::endl;
        
        std::cout << std::setw(8) << std::left << "" << "\t\t\t\t\t     Total Balances = " << TotalBalances << std::endl;
        std::cout << std::setw(8) << std::left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }
};
