#pragma once
#include <iomanip>
#include <iostream>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUpdateCurrencyRate.h"
#include "clsFindCurrencyScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMainScreen : protected clsScreen {
private:
    enum enCurrencyExchangeMenueOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eShowMainMenue = 5
    };

    static short ReadCurrencyExchangeMenueOptions() {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 5]\n";
        short Choice = clsInputValidate::ReadValidNumber<short>(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _ShowListCurrencies() {
        //std::cout << "\n List Currencies Screen will be here.\n";
        clsCurrenciesListScreen::ShowCurrencysList();
    }

    static void _ShowFindCurrency() {
        //std::cout << "\n Find Currency Screen will be here.\n";
        clsFindCurrencyScreen::FindCurrencysList();
    }

    static void _ShowUpdateRateScreen() {
        //std::cout << "\n Update Rate Screen will be here.\n";
        clsUPdateCurrencyScreen::UpdateCurrencysList();
    }

    static void _ShowCurrencyCalculatorScreen() {
        //std::cout << "\n Currency Calculator Screen will be here.\n";
        clsCurrencyCalculatorScreen::CalculatorCurrencys();
    }

    static void _GoBackToCurrencyExchangeMenueMenue() {
        std::cout << "\n\nPress any key to go back to Currency Exchang Menue...";
        clsUtil::PressEnterToContinue();   //system("pause>0");
        ShowCurrencyExchangeMainScreen();
    }

    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyExchangeMenueMenueOption) {
        switch (CurrencyExchangeMenueMenueOption) {
            case enCurrencyExchangeMenueOptions::eListCurrencies: {
                system("cls");
                _ShowListCurrencies();
                _GoBackToCurrencyExchangeMenueMenue();
                break;
            }

            case enCurrencyExchangeMenueOptions::eFindCurrency: {
                system("cls");
                _ShowFindCurrency();
                _GoBackToCurrencyExchangeMenueMenue();
                break;
            }

            case enCurrencyExchangeMenueOptions::eUpdateRate: {
                system("cls");
                _ShowUpdateRateScreen();
                _GoBackToCurrencyExchangeMenueMenue();
                break;
            }

            case enCurrencyExchangeMenueOptions::eCurrencyCalculator: {
                system("cls");
                _ShowCurrencyCalculatorScreen();
                _GoBackToCurrencyExchangeMenueMenue();
                break;
            }

            case enCurrencyExchangeMenueOptions::eShowMainMenue: {
                //do nothing here the main screen will handle it :-) ;
            }
        }
    }

public:

    static void ShowCurrencyExchangeMainScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions)) {
            return;// this will exit the function and it will not continue
        }
        
        system("cls");
        _DrawScreenHeader("  Currency Exchange Main Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t\t  Currency Exchange Menue\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] List Currencies.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Find Currency.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Update Rate.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Currency Calculator.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Main Menue.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";

        _PerformCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)ReadCurrencyExchangeMenueOptions());
    }
};
