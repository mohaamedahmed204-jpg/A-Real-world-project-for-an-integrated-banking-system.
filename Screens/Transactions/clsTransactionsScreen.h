#pragma once
#include <iomanip>
#include <iostream>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsInputValidate.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsLoginTransferScreen.h"
#include "clsTotalBalancesScreen.h"

class clsTransactionsScreen :protected clsScreen {
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3,
        eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6
    };

    static short ReadTransactionsMenueOption() {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 5]\n";
        short Choice = clsInputValidate::ReadValidNumber<short>(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowDepositScreen() {
        //std::cout << "\n Deposit Screen will be here.\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {
        //std::cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen() {
        //std::cout << "\n Balances Screen will be here.\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen() {
        //std::cout << "\n Transfer Screen will be here.\n";
        clsTranferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        //std::cout << "\n Transfer Log Screen will be here.\n";
        clsLoginTransferScreen::ShowLoginTransferList();
    }

    static void _GoBackToTransactionsMenue() {
        std::cout << "\n\nPress any key to go back to Transactions Menue...";
        clsUtil::PressEnterToContinue();   //system("pause>0");
        ShowTransactionsMenue();
    }

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption) {
        switch (TransactionsMenueOption) {
            case enTransactionsMenueOptions::eDeposit: {
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eWithdraw: {
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eShowTotalBalance: {
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eTransfer: {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eTransferLog: {
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eShowMainMenue: {
                //do nothing here the main screen will handle it :-) ;
            }
        }
    }

public:

    static void ShowTransactionsMenue() {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions)) {
            return;// this will exit the function and it will not continue
        }
        
        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t\t  Transactions Menue\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] Deposit.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Withdraw.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Total Balances.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Transfer.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Transfer Login.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menue.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }
};
