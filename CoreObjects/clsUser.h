#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsEncryptKey.h"
#include <vector>
#include <fstream>

struct stLoginRegister {
    std::string _DateAndTime;
    std::string _UserName;
    std::string _PassWord;
    std::string _Permissions;
};

class clsUser : public clsPerson {
private:

    //struct stLoginRegister;

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    std::string _UserName;
    std::string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(std::string Line, std::string Seperator = "#//#") {
        std::vector<std::string> vUserData = clsString::SplitEachWordInVector(Line, Seperator);
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
             vUserData[4], clsUtil::Decryption(vUserData[5], EncryptKey), stoi(vUserData[6]));
    }

    static std::string _ConverUserObjectToLine(clsUser User, std::string Seperator = "#//#") {
        std::string UserRecord = "";
        UserRecord += User.GetFirstName() + Seperator;
        UserRecord += User.GetLastName() + Seperator;
        UserRecord += User.GetEmail() + Seperator;
        UserRecord += User.GetPhone() + Seperator;
        UserRecord += User.GetUserName() + Seperator;
        UserRecord += clsUtil::Encryption(User.GetPassword(), EncryptKey) + Seperator;
        UserRecord += std::to_string(User.GetPermissions());

        return UserRecord;
    }

    static  std::vector <clsUser> _LoadUsersDataFromFile() {
        std::vector <clsUser> vUsers;

        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);    //read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {

                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static stLoginRegister _ConvertLinetoLoginRegisterStruct(std::string Line) {
        std::vector<std::string> vData = clsString::SplitEachWordInVector(Line, "#//#");
        stLoginRegister LR;
        LR._DateAndTime = vData[0];
        LR._UserName = vData[1];
        LR._PassWord = clsUtil::Decryption(vData[2], EncryptKey);
        LR._Permissions = vData[3];
        return LR;
    }

    static std::vector <stLoginRegister> _LoadLoginRegisterFromFile() {
        std::vector <stLoginRegister> vLoginRegisters;

        std::fstream MyFile;
        MyFile.open("RegisterLogins.txt", std::ios::in);    //read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                stLoginRegister RL = _ConvertLinetoLoginRegisterStruct(Line);
                vLoginRegisters.push_back(RL);
            }
            MyFile.close();
        }
        return vLoginRegisters;
    }

    static void _SaveUsersDataToFile(std::vector <clsUser> vUsers) {

        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::out);     //overwrite
        std::string DataLine;

        if (MyFile.is_open()) {
            for (clsUser U : vUsers) {
                if (U.MarkedForDeleted() == false) {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << std::endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update() {
        std::vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers) {
            if (U.GetUserName() == _UserName) {
                U = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew() {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(std::string  stDataLine) {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::out | std::ios::app);  // add one item

        if (MyFile.is_open()) {

            MyFile << stDataLine << std::endl;
            MyFile.close();
        }
    }
    
    std::string ConvertRegisterLoginToString(const std::string &Seperator = "#//#") {
        clsDate CDate;
        return clsDate::DateToString(CDate) + " - " + clsDate::TimeToString(CDate) + Seperator + _UserName
        + Seperator + clsUtil::Encryption(_Password, EncryptKey) + Seperator + std::to_string(_Permissions) + "\n";
    }

    static clsUser _GetEmptyUserObject() {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8,
        pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128, pCurrencyExchange = 256
    };

    clsUser(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone, std::string UserName,
        std::string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted() {
        return _MarkedForDelete;
    }

    std::string GetUserName() {
        return _UserName;
    }

    void SetUserName(std::string UserName) {
        _UserName = UserName;
    }

    void SetPassword(std::string Password) {
        _Password = Password;
    }

    std::string GetPassword() {
        return _Password;
    }

    void SetPermissions(int Permissions) {
        _Permissions = Permissions;
    }

    int GetPermissions() {
        return _Permissions;
    }

    static clsUser Find(std::string UserName) {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);      //read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName) {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(std::string UserName, std::string Password) {

        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);//read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName && User.GetPassword() == Password) {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save() {
        switch (_Mode)
        {
            case enMode::EmptyMode: {
                if (IsEmpty()) {
                    return enSaveResults::svFaildEmptyObject;
                }
            }

            case enMode::UpdateMode: {
                _Update();
                return enSaveResults::svSucceeded;
                break;
            }

            case enMode::AddNewMode: {
                //This will add new record to file or database
                if (clsUser::IsUserExist(_UserName)) {
                    return enSaveResults::svFaildUserExists;
                }
                else {
                    _AddNew();
                    //We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
                break;
            }
        }
        return enSaveResults::svFaildEmptyObject;
    }

    static bool IsUserExist(std::string UserName) {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete() {
        std::vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers) {
            if (U.GetUserName() == _UserName) {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();
        return true;
    }

    static clsUser GetAddNewUserObject(std::string UserName) {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static std::vector <clsUser> GetUsersList() {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission) {
        if (this->_Permissions == enPermissions::eAll)
            return true;

        return ((Permission & this->_Permissions) == Permission);
    }

    void _RegisterLogins() {
        std::fstream MyFile;
        MyFile.open("RegisterLogins.txt", std::ios::out | std::ios::app);  // add one item
        std::string DataLine = ConvertRegisterLoginToString();
        if (MyFile.is_open()) {
            MyFile << DataLine;
            MyFile.close();
        }
    }

    static std::vector <stLoginRegister> GetLoginRegister() {
        return _LoadLoginRegisterFromFile();
    }
};