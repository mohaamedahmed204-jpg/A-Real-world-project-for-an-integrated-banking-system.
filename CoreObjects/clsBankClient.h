#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"

struct stLoginTransfer {
    std::string _DateAndTime;
    std::string _Client1AccountNum, _Client2AccountNum;
    std::string _TransferAmount, _FromC1, _ToC2;
    std::string _CUser;
};


class clsBankClient : public clsPerson {
public:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

private:

    enMode _Mode;
    std::string _AccountNumber;
    std::string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    // Abstraction
    static clsBankClient _ConvertLinetoClientObject(std::string Line, std::string Seperator = "#//#") {

        std::vector<std::string> vClientData;
        vClientData = clsString::SplitEachWordInVector(Line, Seperator);

        // التحقق من أن السطر يحتوي على كافة الحقول المطلوبة (7 حقول)
        if (vClientData.size() < 7) {
            return _GetEmptyClientObject();
        }

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    // Abstraction
    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static std::string _ConverClientObjectToLine(clsBankClient Client, std::string Seperator = "#//#") {

        std::string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.GetPinCode() + Seperator;
        stClientRecord += std::to_string(Client.GetAccountBalance());

        return stClientRecord;
    }

    static std::vector <clsBankClient> _LoadClientsDataFromFile() {

        std::vector <clsBankClient> vClients;

        std::fstream MyFile;
        MyFile.open("Clients.txt", std::ios::in); //read Mode

        if (MyFile.is_open()) {
            std::string Line;

            while (std::getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.emplace_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    static void _SaveCleintsDataToFile(std::vector <clsBankClient> vClients) {
        std::fstream MyFile;
        MyFile.open("Clients.txt", std::ios::out); //overwrite

        std::string DataLine;

        if (MyFile.is_open()) {
            for (clsBankClient C : vClients) {
                if (C.MarkedForDeleted() == false) {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << std::endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update() {
        std::vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);
    }

    void _AddDataLineToFile(std::string  stDataLine) {
        std::fstream MyFile;
        MyFile.open("Clients.txt", std::ios::out | std::ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << std::endl;
            MyFile.close();
        }
    }

    void _AddNew() {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    std::string ConvertTransferLoginToString(clsBankClient C1, clsBankClient C2, double TransAmount, const std::string &Seperator = "#//#") {
        clsDate CDate;
        return clsDate::DateToString(CDate) + " - " + clsDate::TimeToString(CDate) + Seperator + C1.AccountNumber() + Seperator + C2.AccountNumber()
        + Seperator + std::to_string(TransAmount) + Seperator + std::to_string(C1.GetAccountBalance()) + Seperator + std::to_string(C2.GetAccountBalance())
        + Seperator + CurrentUser.GetUserName() + '\n';
    }

    static stLoginTransfer _ConvertLinetoLoginTransferStruct(std::string Line) {
        std::vector<std::string> vData = clsString::SplitEachWordInVector(Line, "#//#");
        stLoginTransfer LR;
        LR._DateAndTime = vData[0];
        LR._Client1AccountNum = vData[1];
        LR._Client2AccountNum = vData[2];
        LR._TransferAmount = vData[3];
        LR._FromC1 = vData[4]; LR._ToC2 = vData[5];
        LR._CUser = vData[6];
        return LR;
    }

    static std::vector <stLoginTransfer> _LoadLoginTransferFromFile() {
        std::vector <stLoginTransfer> vLoginRegisters;

        std::fstream MyFile;
        MyFile.open("TransferLog.txt", std::ios::in);    //read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                stLoginTransfer RL = _ConvertLinetoLoginTransferStruct(Line);
                vLoginRegisters.push_back(RL);
            }
            MyFile.close();
        }
        return vLoginRegisters;
    }

public:

    clsBankClient(enMode Mode, std::string FirstName, std::string LastName, std::string Email,
        std::string Phone, std::string AccountNumber, std::string PinCode, float AccountBalance)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted() {
        return _MarkedForDelete;
    }

    // ---------------------------------------------------------- //

    // Read only
    std::string AccountNumber() {
        return _AccountNumber;
    }

    void SetPinCode(std::string PinCode) {
        _PinCode = PinCode;
    }

    std::string GetPinCode() {
        return _PinCode;
    }

    void SetAccountBalance(float AccountBalance) {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance() {
        return _AccountBalance;
    }

    // No print method in the class person
    // No print method in logial operation only in UI/UX
    
    // void Print() {
    //     std::cout << "\nClient Card:";
    //     std::cout << "\n___________________";
    //     std::cout << "\nFirstName       : " << GetFirstName();
    //     std::cout << "\nLastName        : " << GetLastName();
    //     std::cout << "\nFull Name       : " << FullName();
    //     std::cout << "\nEmail           : " << GetEmail();
    //     std::cout << "\nPhone           : " << GetPhone();
    //     std::cout << "\nAccount Number  : " << _AccountNumber;
    //     std::cout << "\nPassword        : " << _PinCode;
    //     std::cout << "\nBalance         : " << _AccountBalance;
    //     std::cout << "\n___________________\n";

    // }

    static void ReadClientInfo(clsBankClient& Client) {
     
        Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName: "));

        Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

        Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

        Client.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

        Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode: "));

        Client.SetAccountBalance(clsInputValidate::ReadValidNumber<float>(0, 1000000, "\nEnter Account Balance (0-1000000): "));
    }

    static clsBankClient Find(std::string AccountNumber) {

        std::fstream MyFile;
        MyFile.open("Clients.txt", std::ios::in);  //read Mode

        if (MyFile.is_open()) {
            std::string Line;

            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);

                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                } 
            }
            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(std::string AccountNumber, std::string PinCode) {

        std::fstream MyFile;
        MyFile.open("Clients.txt", std::ios::in);//read Mode

        if (MyFile.is_open()) {
            std::string Line;

            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                
                if (Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode) {
                    MyFile.close();
                    return Client;
                } 
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(std::string AccountNumber) {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults Save() {

        switch (_Mode) {
            case enMode::EmptyMode: {
                return enSaveResults::svFaildEmptyObject;
            }
            case enMode::UpdateMode: {
                _Update();
                return enSaveResults::svSucceeded;
                break;
            }
            case enMode::AddNewMode: {
                //This will add new record to file or database
                if (clsBankClient::IsClientExist(_AccountNumber)) {
                    return enSaveResults::svFaildAccountNumberExists;
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

    static clsBankClient GetAddNewClientObject(std::string AccountNumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    // This mark for Delete then actualy delete it.......
    bool Delete() {
        std::vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);
        *this = _GetEmptyClientObject();

        return true; // For safety
    }

    static std::vector <clsBankClient> GetClientsList() {
        return _LoadClientsDataFromFile();
    }

    static void PrintClientRecordLine(clsBankClient &Client) {
        std::cout << "| " << std::setw(15) << std::left << Client.AccountNumber();
        std::cout << "| " << std::setw(20) << std::left << Client.FullName();
        std::cout << "| " << std::setw(12) << std::left << Client.GetPhone();
        std::cout << "| " << std::setw(20) << std::left << Client.GetEmail();
        std::cout << "| " << std::setw(10) << std::left << Client.GetPinCode();
        std::cout << "| " << std::setw(12) << std::left << Client.GetAccountBalance();
    }

    static void ShowClientsList(){
        std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        std::cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        std::cout << "| " << std::left << std::setw(15) << "Accout Number";
        std::cout << "| " << std::left << std::setw(20) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(20) << "Email";
        std::cout << "| " << std::left << std::setw(10) << "Pin Code";
        std::cout << "| " << std::left << std::setw(12) << "Balance";
        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        if (vClients.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (clsBankClient &Client : vClients) {
                PrintClientRecordLine(Client);
                std::cout << std::endl;
            }

        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;
    }

    static float GetTotalBalances() {
        std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;
        for (clsBankClient Client : vClients) {

            TotalBalances += Client.GetAccountBalance();
        }

        return TotalBalances;
    }

    static void PrintClientRecordBalanceLine(clsBankClient &Client) {
        std::cout << "| " << std::setw(15) << std::left << Client.AccountNumber();
        std::cout << "| " << std::setw(40) << std::left << Client.FullName();
        std::cout << "| " << std::setw(12) << std::left << Client.GetAccountBalance();
    }


    static void ShowTotalBalances() {
        std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        std::cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        std::cout << "| " << std::left << std::setw(15) << "Accout Number";
        std::cout << "| " << std::left << std::setw(40) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Balance";
        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (clsBankClient Client : vClients) {
                PrintClientRecordBalanceLine(Client);
                std::cout << std::endl;
            }

        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;
        std::cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << std::endl;
        std::cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }

    void Deposit(double Amount) {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount) {
        if(_AccountBalance < Amount) {
            return false;
        }
        else {
            _AccountBalance -= Amount;
            Save();
        }
        return true;
    }

    void Transfer(double Amount, clsBankClient &Target) {
        this->Withdraw(Amount);
        Target.Deposit(Amount);
    }

    void _TransferLogins(clsBankClient C1, clsBankClient C2, double TransAmount) {
        std::fstream MyFile;
        MyFile.open("TransferLog.txt", std::ios::out | std::ios::app);  // add one item
        std::string DataLine = ConvertTransferLoginToString(C1, C2, TransAmount);
        if (MyFile.is_open()) {
            MyFile << DataLine;
            MyFile.close();
        }
    }

    static std::vector <stLoginTransfer> GetLoginTransfer() {
        return _LoadLoginTransferFromFile();
    }
};
