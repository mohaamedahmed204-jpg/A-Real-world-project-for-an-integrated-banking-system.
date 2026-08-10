#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsLoginRegisterScreen : protected clsScreen {

private:
    static void PrintClientRecordLine(stLoginRegister LR) {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(30) << std::left << LR._DateAndTime;
        std::cout << "| " << std::setw(20) << std::left << LR._UserName;
        std::cout << "| " << std::setw(25) << std::left << LR._PassWord;
        std::cout << "| " << std::setw(26) << std::left << LR._Permissions;
    }

public:
    static void ShowLoginRegisterList() {

        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister)) {
            return;// this will exit the function and it will not continue
        }

        std::vector <stLoginRegister> vLoginRegisters = clsUser::GetLoginRegister();
        std::string Title = "\t  Login Register list Screen";
        std::string SubTitle ="\t    (" + std::to_string(vLoginRegisters.size()) + ") Records(s).";

        _DrawScreenHeader(Title, SubTitle);
        
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        std::cout <<  std::setw(8) << std::left << "" << "| " << std::left << std::setw(30) << "Date/Time";
        std::cout << "| " << std::left << std::setw(20) << "UserName";
        std::cout << "| " << std::left << std::setw(25) << "Password";
        std::cout << "| " << std::left << std::setw(30) << "Permissions";
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        if (vLoginRegisters.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (stLoginRegister LR : vLoginRegisters) {
                PrintClientRecordLine(LR);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;
    }

};
