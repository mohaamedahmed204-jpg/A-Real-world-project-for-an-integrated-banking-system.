#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <cctype> // Required for isalpha
#include "clsDate.h"

class clsInputValidate {
public:
    template <typename T>
    struct NumberLimits {
        static constexpr T INF_POS = std::numeric_limits<T>::max();
        static constexpr T INF_MIN = std::numeric_limits<T>::lowest();
    };

    static void ClearBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template<typename T>
    static bool IsNumberBetween(const T &Num, const T &From, const T &To) {
        T temp[] = {From, To};
        std::sort(temp, temp + 2);

        return !(Num < temp[0] || Num > temp[1]);
    }

    template <typename T>
    static T ReadValidNumber(const T &From = std::numeric_limits<T>::lowest(), const T &To = std::numeric_limits<T>::max(), const std::string &message = "") {
        T Num;
        std::cout << message;
         
        while(true) {
            std::cin >> Num;
            
            if(std::cin.fail() || std::cin.peek() != '\n') { // No chars or String.
                ClearBuffer();
                std::cout << "Enter Only a Number (No chars or String): ";
            }
            else if(!IsNumberBetween(Num, From, To)) {
                std::cout << "Enter a valid Number in range: ";
            }
            else {
                ClearBuffer();
                return Num;
            }
        }
    }

    static std::string ReadString(std::string Message) {        
        std::cout << Message;
        
        std::string Line;
        std::getline(std::cin >> std::ws, Line);
        
        return Line;
    }

    static char ReadChar(std::string Message) {        
        std::string Char;

        do {
            std::cout << Message;
            std::cin >> Char;
            ClearBuffer();

        } while(Char.size() != 1 && !(std::isalpha(Char[0])));
        
        return Char[0];
    }

    static bool GeneralYesOrNo(std::string Message) {
        char Choose;
        std::cout << Message;
        
        Choose = ReadChar("Only choose Y/y or N/n: ");
        Choose = toupper(Choose);
        
        return Choose == 'Y';
    }

    static clsDate ReadFullDate() {
    
        clsDate stDate1;
        
        stDate1.SetYear(ReadValidNumber<int>(1582, NumberLimits<int>::INF_POS, "Enter The Year(Not Less Than 1582):\n"));
        stDate1.SetMonth(ReadValidNumber<int>(1, 12, "Enter The Month(1-12):\n"));
        
        int MaxDays = clsDate::NumberOfDaysInMonth(stDate1.GetYear(), stDate1.GetMonth());
        stDate1.SetDay(ReadValidNumber<int>(1, MaxDays, "Enter The Day (1-" + std::to_string(MaxDays) + "):\n"));
        
        return stDate1;
    }

    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {
		//Date >= From && Date <= To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)) 
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
		  )
		{
			return true;
		}
		
		//Date >= To && Date <= From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)) 
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
		   )
		{
			return true;
		}

		return false;
	}
    
};