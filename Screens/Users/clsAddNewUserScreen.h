#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen {
private:

    static void _ReadUserInfo(clsUser& User) {
        User.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName: "));

        User.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

        User.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

        User.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

        User.SetPassword(clsInputValidate::ReadString("\nEnter Password: "));

        User.SetPermissions(_ReadPermissionsToSet("\nEnter Permission: "));
    }

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

    static int _ReadPermissionsToSet(const std::string &message) {

        std::cout << message << '\n';
        int Permissions = 0;
        char Answer = 'n';

        if(clsInputValidate::GeneralYesOrNo("\nDo you want to give full access? y/n? ")) {
            return -1;
        }

        std::cout << "\nDo you want to give access to : \n ";

        if (clsInputValidate::GeneralYesOrNo("\nShow Client List? y/n? ")) {
            Permissions += clsUser::enPermissions::pListClients;
        }

        if (clsInputValidate::GeneralYesOrNo("\nAdd New Client? y/n? ")) {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        if (clsInputValidate::GeneralYesOrNo("\nDelete Client? y/n? ")) {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        if (clsInputValidate::GeneralYesOrNo("\nUpdate Client? y/n? ")) {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        if (clsInputValidate::GeneralYesOrNo("\nFind Client? y/n? ")) {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        if (clsInputValidate::GeneralYesOrNo("\nTransactions? y/n? ")) {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        if (clsInputValidate::GeneralYesOrNo("\nManage Users? y/n? ")) {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        if (clsInputValidate::GeneralYesOrNo("\nLogin Register? y/n? ")) {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        if (clsInputValidate::GeneralYesOrNo("\nCurrency Exchange? y/n? ")) {
            Permissions += clsUser::enPermissions::pCurrencyExchange;
        }

        return Permissions;
    }

public:

    static void ShowAddNewUserScreen() {
        _DrawScreenHeader("\t  Add New User Screen");

        std::string UserName = "";
        UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        
        while (clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("\nUserName Is Already Used, Choose another one: ");
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();

        switch (SaveResult) {
            case  clsUser::enSaveResults::svSucceeded:
            {
                std::cout << "\nUser Addeded Successfully :-)\n";
                _PrintUser(NewUser);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                std::cout << "\nError User was not saved because it's Empty";
                break;
            }
            case clsUser::enSaveResults::svFaildUserExists:
            {
                std::cout << "\nError User was not saved because UserName is used!\n";
                break;
            }
        }
    }
};
