#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsLoginTransferScreen : protected clsScreen {

private:
    static void PrintClientRecordLine(stLoginTransfer LR) {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(25) << std::left << LR._DateAndTime;
        std::cout << "| " << std::setw(15) << std::left << LR._Client1AccountNum;
        std::cout << "| " << std::setw(20) << std::left << LR._Client2AccountNum;
        std::cout << "| " << std::setw(21) << std::left << LR._TransferAmount;
        std::cout << "| " << std::setw(15) << std::left << LR._FromC1;
        std::cout << "| " << std::setw(20) << std::left << LR._ToC2;
        std::cout << "| " << std::setw(21) << std::left << LR._CUser;
    }

public:
    static void ShowLoginTransferList() {

        std::vector <stLoginTransfer> vLoginTransfers = clsBankClient::GetLoginTransfer();
        std::string Title = "\t  Login Transfer list Screen";
        std::string SubTitle ="\t    (" + std::to_string(vLoginTransfers.size()) + ") Records(s).";

        _DrawScreenHeader(Title, SubTitle);
        
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "________________________________________________________________________________\n" << std::endl;

        std::cout <<  std::setw(8) << std::left << "" << "| " << std::left << std::setw(25) << "Date/Time";
        std::cout << "| " << std::left << std::setw(15) << "s.Acct";
        std::cout << "| " << std::left << std::setw(20) << "b.Acct";
        std::cout << "| " << std::left << std::setw(21) << "Amount";
        std::cout << "| " << std::left << std::setw(15) << "s.Balance";
        std::cout << "| " << std::left << std::setw(20) << "b.Balance";
        std::cout << "| " << std::left << std::setw(21) << "User";
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "________________________________________________________________________________\n" << std::endl;

        if (vLoginTransfers.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (stLoginTransfer LR : vLoginTransfers) {
                PrintClientRecordLine(LR);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "________________________________________________________________________________\n" << std::endl;
    }

};
