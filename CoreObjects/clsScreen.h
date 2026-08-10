#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"

class clsScreen {
protected :
    static void _DrawScreenHeader(const std::string &Title, const std::string &SubTitle ="") {
        std::cout << "\t\t\t\t\t______________________________________";
        std::cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "") {
            std::cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        std::cout << "\n\t\t\t\t\t______________________________________\n\n";
        std::cout << "\t\t\t\t\tUser: " << CurrentUser.GetUserName() << std::endl;
        std::cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate::GetCurrentDate()) << std::endl;
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission) {
     
        if(!CurrentUser.CheckAccessPermission(Permission)) {
            std::cout << "\t\t\t\t\t______________________________________";
            std::cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
            std::cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else {
            return true;
        }
    }
};
