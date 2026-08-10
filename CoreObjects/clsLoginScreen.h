#pragma once

#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"

class clsLoginScreen :protected clsScreen {
private :

    static void _Login() {
        bool LoginFaild = false;
        short Trials = 3;

        do {
            if (LoginFaild) {
                std::cout << "\nInvlaid Username/Password!\n";
                std::cout << "You have " << --Trials << " trial(s) to login.\n\n";
                if(!Trials) {
                    std::cout << "You are locked after 3 failed trials\n\n";
                    exit(0);
                }
            }

            std::string Username = clsInputValidate::ReadString("Enter Username? ");
            std::string Password = clsInputValidate::ReadString("Enter Password? ");
            
            CurrentUser = clsUser::Find(Username, Password);
            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser._RegisterLogins();
        clsMainScreen::ShowMainMenue();
    }

public:

    static void ShowLoginScreen() {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();
    }
};
