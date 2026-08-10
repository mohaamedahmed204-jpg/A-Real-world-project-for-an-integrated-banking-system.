#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen {
private:
    static void _PrintUser(clsUser User) {
        std::cout << "\nUser Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << User.GetFirstName();
        std::cout << "\nLastName    : " << User.GetLastName();
        std::cout << "\nFull Name   : " << User.FullName();
        std::cout << "\nEmail       : " << User.GetEmail();
        std::cout << "\nPhone       : " << User.GetPhone();
        std::cout << "\nPassword    : " << User.GetPassword();
        std::cout << "\nPermissions : " << User.GetPermissions();
        std::cout << "\n___________________\n";
    }

public:

    static void ShowFindUserScreen() {

        _DrawScreenHeader("\t  Find User Screen");

        std::string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty()) {
            std::cout << "\nUser Found :-)\n";
        }
        else {
            std::cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);
    }
};
