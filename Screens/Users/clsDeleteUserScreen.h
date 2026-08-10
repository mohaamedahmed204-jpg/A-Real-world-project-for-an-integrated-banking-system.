#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen {
private:
    static void _PrintUser(clsUser User) {
        std::cout << "\nUser Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << User.GetFirstName();
        std::cout << "\nLastName    : " << User.GetLastName();
        std::cout << "\nFull Name   : " << User.FullName();
        std::cout << "\nEmail       : " << User.GetEmail();
        std::cout << "\nPhone       : " << User.GetPhone();
        std::cout << "\nUser Name   : " << User.GetUserName();
        std::cout << "\nPassword    : " << User.GetPassword();
        std::cout << "\nPermissions : " << User.GetPermissions();
        std::cout << "\n___________________\n";
    }

public:
    static void ShowDeleteUserScreen() {
        _DrawScreenHeader("\tDelete User Screen");

        std::string UserName = "";
        UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("\nUser is not found, choose another one: ");
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        if (clsInputValidate::GeneralYesOrNo("\nAre you sure you want to delete this User y/n? ")) {

            if (User1.Delete()) {
                std::cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else {
                std::cout << "\nError User Was not Deleted\n";
            }
        }
    }
};
