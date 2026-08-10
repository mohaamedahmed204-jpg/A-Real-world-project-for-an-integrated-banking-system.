#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsListUsersScreen : protected clsScreen {

private:
    static void _PrintUserRecordLine(clsUser User) {
        std::cout << std::setw(8) << std::left << "| " << std::setw(12) << std::left << User.GetUserName();
        std::cout << "| " << std::setw(25) << std::left << User.FullName();
        std::cout << "| " << std::setw(12) << std::left << User.GetPhone();
        std::cout << "| " << std::setw(20) << std::left << User.GetEmail();
        std::cout << "| " << std::setw(10) << std::left << User.GetPassword();
        std::cout << "| " << std::setw(12) << std::left << User.GetPermissions();
    }

public:

    static void ShowUsersList() {

        std::vector <clsUser> vUsers = clsUser::GetUsersList();

        std::string Title = "\t  User List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        std::cout << std::setw(8) << std::left << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << std::endl;

        std::cout << std::setw(8) << std::left << "| " << std::left << std::setw(12) << "UserName";
        std::cout << "| " << std::left << std::setw(25) << "Full Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(20) << "Email";
        std::cout << "| " << std::left << std::setw(10) << "Password";
        std::cout << "| " << std::left << std::setw(12) << "Permissions";
        std::cout << std::setw(8) << std::left << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << std::endl;

        if (vUsers.size() == 0)
            std::cout << "\t\t\t\tNo Users Available In the System!";
        else
            for (clsUser User : vUsers) {
                _PrintUserRecordLine(User);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << std::endl;
    }
};
