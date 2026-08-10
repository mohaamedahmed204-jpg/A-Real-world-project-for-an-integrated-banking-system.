#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsScreen.h"
#include "clsManageUsers.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

class clsMainScreen:protected clsScreen {

    private:
        enum enMainMenueOptions {
            eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
            eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
            eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
        };

        static short _ReadMainMenueOption() {
            std::cout << std::setw(37) << std::left << "Choose what do you want to do? [1 to 10]\n";
            short Choice = clsInputValidate::ReadValidNumber<short>(1,10,"Enter Number between 1 to 10? ");
            return Choice;
        }

        static  void _GoBackToMainMenue() {
            std::cout << std::setw(37) << std::left << ""<<"\n\tPress Double Enter To Back To Main Menu........\n";
           
            clsUtil::PressEnterToContinue();   //system("pause>0");
            ShowMainMenue();
        }
       
        static void _ShowAllClientsScreen() {
            //std::cout << "\nClient List Screen Will be here...\n";
            clsClientListScreen::ShowClientsList();
        }

       static void _ShowAddNewClientsScreen() {
           //std::cout << "\nAdd New Client Screen Will be here...\n";
           clsAddNewClientScreen::ShowAddNewClientScreen();
        }

        static void _ShowDeleteClientScreen() {
           //std::cout << "\nDelete Client Screen Will be here...\n";
           clsDeleteClientScreen::ShowDeleteClientScreen(); 
        }

        static void _ShowUpdateClientScreen() {
           //std::cout << "\nUpdate Client Screen Will be here...\n";
           clsUpdateClientScreen::ShowUpdateClientScreen();
        }

        static void _ShowFindClientScreen() {
           //std::cout << "\nFind Client Screen Will be here...\n";
           clsFindClientScreen::ShowFindClientScreen();
        }

        static void _ShowTransactionsMenue() {
           //std::cout << "\nTransactions Menue Will be here...\n";
           clsTransactionsScreen::ShowTransactionsMenue();
        }

        static void _ShowManageUsersMenue() {
           //std::cout << "\nUsers Menue Will be here...\n";
           clsManageUsersScreen::ShowManageUsersMenue();
        }

        static void _ShowLoginRegisterScreen() {
            //std::cout << "\nLogin Register Will be here...\n";
           clsLoginRegisterScreen::ShowLoginRegisterList();
        }

        static void _ShowCurrencyExchangeScreen() {
            //std::cout << "\nCurrency Exchange Will be here...\n";
           clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainScreen();
        }

        // static void _ShowEndScreen() {
        //     std::cout << "\nEnd Screen Will be here...\n";
        // }
        
        static void _Logout() {
            CurrentUser = clsUser::Find("", "");
            //then it will go back to main function.
        }

        static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
            switch (MainMenueOption) {
                case enMainMenueOptions::eListClients:
                {
                    system("cls");
                    _ShowAllClientsScreen();
                    _GoBackToMainMenue();
                    break;
                }
                case enMainMenueOptions::eAddNewClient:
                    system("cls");
                    _ShowAddNewClientsScreen();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eDeleteClient:
                    system("cls");
                    _ShowDeleteClientScreen();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eUpdateClient:
                    system("cls");
                    _ShowUpdateClientScreen();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eFindClient:
                    system("cls");
                    _ShowFindClientScreen();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eShowTransactionsMenue:
                    system("cls");
                    _ShowTransactionsMenue();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eManageUsers:
                    system("cls");
                    _ShowManageUsersMenue();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eLoginRegister:
                    system("cls");
                    _ShowLoginRegisterScreen();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eCurrencyExchange:
                    system("cls");
                    _ShowCurrencyExchangeScreen();
                    _GoBackToMainMenue();
                    break;

                case enMainMenueOptions::eExit:
                    system("cls");
                    _Logout();
                    break;
            }
        }

	public:
        static void ShowMainMenue() {
           
            system("cls");
            _DrawScreenHeader("\t\tMain Screen");

            std::cout << std::setw(37) << std::left <<""<< "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t\t\tMain Menue\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t[1] Show Client List.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[2] Add New Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[4] Update Client Info.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[6] Transactions.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[7] Manage Users.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[8] Login Register.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[9] Currency Exchange.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[10] Logout.\n";
            
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";

            _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
        }

};
