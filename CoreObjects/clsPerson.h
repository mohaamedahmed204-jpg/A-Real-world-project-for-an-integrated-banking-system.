#pragma once
#include <iostream>
#include <string>
#include "InterfaceCommunication.h"

class clsPerson : InterfaceCommunication {

private:
    std::string _FirstName;
    std::string _LastName;
    std::string _Email;
    std::string _Phone;

public:
    clsPerson( std::string FirstName, std::string LastName, std::string Email, std::string Phone) {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    //Property Set
    void SetFirstName(std::string FirstName) {
        _FirstName = FirstName;
    }

    //Property Get
    std::string GetFirstName() {
        return _FirstName;
    }
    
    //Property Set
    void SetLastName(std::string LastName) {
        _LastName = LastName;
    }

    //Property Get
    std::string GetLastName() {
        return _LastName;
    }
    
    //Property Set
    void SetEmail(std::string Email) {
        _Email = Email;
    }

    //Property Get
    std::string GetEmail() {
        return _Email;
    }
    
    //Property Set
    void SetPhone(std::string Phone) {
        _Phone = Phone;
    }

    //Property Get
    std::string GetPhone() {
        return _Phone;
    }
    
    std::string FullName() {
        return _FirstName + " " + _LastName;
    }

    void Print() {
        std::cout << "\nInfo:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName: " << _FirstName;
        std::cout << "\nLastName : " << _LastName;
        std::cout << "\nFull Name: " << FullName();
        std::cout << "\nEmail    : " << _Email;
        std::cout << "\nPhone    : " << _Phone;
        std::cout << "\n___________________\n";
    }

    void SendEmail(string Title, string Body) {
        std::cout << Title << '\n';
        std::cout << Body << '\n';
    }

    void SendFax(string Title, string Body) {
        std::cout << Title << '\n';
        std::cout << Body << '\n';
    }

    void SendSMS(string Title, string Body) {
        std::cout << Title << '\n';
        std::cout << Body << '\n';
    }

};
