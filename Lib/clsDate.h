#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <iomanip>
#include "clsString.h"

class clsDate {
private:
    int _Day;
    int _Month;
    int _Year;
    short _DayOrder;
    std::string _DayName;

	int _Hour;
    int _Minute;
    int _Second;

public:
    static short DetermineDayOrder(const int &Year, const int &Month, const int &Day) {
        int e = (14 - Month) / 12;
        
        int y = Year - e;
        int m = Month + 12 * e - 2;
        
        // Gregorian:
        //0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;
    }

    short DetermineDayOrder() {
        return DetermineDayOrder(_Year, _Month, _Day);
    }

    static std::string DetermineDayName(const short &DayOrder) {
        std::string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        return arrDayNames[DayOrder];
    }

    static std::string DetermineDayName(const int &Day, const int &Month, const int &Year) {
        std::string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        return arrDayNames[DetermineDayOrder(Year, Month, Day)];
    }

    std::string DetermineDayName() {
        return DetermineDayName(_Year, _Month, _Day);
    }

    static std::string DeterMineMonthName(int Month) {
        
        std::string MonthName[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return MonthName[Month];
    }

    std::string DeterMineMonthName() {
        return DeterMineMonthName(_Month);
    }

    static bool CheckItLeapYear(const int &Year) {
        // if year is divisible by 4 AND not divisible by 100
        // OR if year is divisible by 400
        // then it is a leap year
        
        return ( (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0) );
    }

    bool CheckItLeapYear() {
        return CheckItLeapYear(_Year);
    }

    static int NumberOfDaysInYear(const int &Year) {
        return CheckItLeapYear(Year) ? 366 : 365;
    }

    int NumberOfDaysInYear() {
        return NumberOfDaysInYear(_Year);
    }

    static int NumberOfHoursInYear(const int &Year) {
        return NumberOfDaysInYear(Year) * 24;
    }

    int NumberOfHoursInYear() {
        return NumberOfHoursInYear(_Year);
    }

    static int NumberOfMinutesInYear(const int &Year) {
        return NumberOfHoursInYear(Year) * 60;
    }

    int NumberOfMinutesInYear() {
        return NumberOfMinutesInYear(_Year);
    }

    static int NumberOfSecondsInYear(const int &Year) {
        return NumberOfMinutesInYear(Year) * 60;
    }

    int NumberOfSecondsInYear() {
        return NumberOfSecondsInYear(_Year);
    }

    static int NumberOfDaysInMonth(const int &Year, const int &Month) {
        static const short Days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month == 2 && CheckItLeapYear(Year) ? 29 : Days[Month]);
    }

    int NumberOfDaysInMonth() {
        return NumberOfDaysInMonth(_Year, _Month);
    }

    static int NumberOfHoursInMonth(const int &Month, const int &Year) {
        return NumberOfDaysInMonth(Month, Year) * 24;
    }

    int NumberOfHoursInMonth() {
        return NumberOfDaysInMonth(_Month, _Year) * 24;
    }

    static int NumberOfMinutesInMonth(const int &Month, const int &Year) {
        return NumberOfHoursInMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInMonth() {
        return NumberOfHoursInMonth(_Month, _Year) * 60;
    }

    static int NumberOfSecondsInMonth(const int &Month, const int &Year) {
        return NumberOfMinutesInMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInMonth() {
        return NumberOfMinutesInMonth(_Month, _Year) * 60;
    }

    static clsDate GetCurrentDate() {
        clsDate Date;

        // System Date        
        time_t t = time(0);
        tm* loctime = localtime(&t);
        
        Date._Year = loctime -> tm_year + 1900;
        Date._Month = loctime -> tm_mon + 1;
        Date._Day = loctime -> tm_mday;

		// جلب الوقت الحالي
        Date._Hour   = loctime->tm_hour;
        Date._Minute = loctime->tm_min;
        Date._Second = loctime->tm_sec;
        
        Date._DayOrder = DetermineDayOrder(Date._Year, Date._Month, Date._Day);
        Date._DayName = DetermineDayName(Date._DayOrder);
        
        return Date;
    }

    static clsDate GetDateFromDayOrderInYear(const int &DateOrderInYear, const int &Year)	{
        clsDate Date;
        Date._Year = Year;
        Date._Month = 1;

		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		while (true) {
			MonthDays = NumberOfDaysInMonth(Year, Date._Month);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else {
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

    static std::string DateToString(const clsDate &Date) {
        return std::to_string(Date._Day) + "/" + std::to_string(Date._Month) + "/" + std::to_string(Date._Year);
    }

    std::string DateToString() {
        return DateToString(*this);
    }

	// دالة تحويل الوقت إلى String بشكل منسق (HH:MM:SS)
    static std::string TimeToString(const clsDate& Date) {
        // استخدمت stringstream هنا لضمان ظهور الأصفار على اليسار مثل 05:09:02
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << Date._Hour << ":"
           << std::setw(2) << std::setfill('0') << Date._Minute << ":"
           << std::setw(2) << std::setfill('0') << Date._Second;
        return ss.str();
    }

    std::string TimeToString() {
        return TimeToString(*this);
    }

    static bool IsValidDate(clsDate Date) {
		if (Date._Day < 1 || Date._Day>31)
			return false;

		if (Date._Month < 1 || Date._Month>12)
			return false;

		if (Date._Month == 2) {
			if (CheckItLeapYear(Date._Year)) {
				if (Date._Day > 29)
					return false;
			}
			else {
				if (Date._Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > DaysInMonth)
			return false;

		return true;
	}

    bool IsValidDate() {
        return IsValidDate(*this);
    }

    clsDate() {
        // Set The Current Date  
        time_t t = time(0);
        tm* loctime = localtime(&t);
        _Year = loctime->tm_year + 1900;
        _Month = loctime->tm_mon + 1;
        _Day = loctime->tm_mday;

		// جلب الوقت الحالي
        _Hour   = loctime->tm_hour;
        _Minute = loctime->tm_min;
        _Second = loctime->tm_sec;

        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    clsDate(const std::string &sDate) {
        std::vector<std::string> vDate;
        vDate = clsString::SplitEachWordInVector(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);

        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    clsDate(int Day, int Month, int Year) {
        _Day = Day;
        _Month = Month;
        _Year = Year;

        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    clsDate(int DayOrderInYear, int Year) {
        // This Will Construct a Date By Date Order In Year.
        clsDate Date1 = GetDateFromDayOrderInYear(DayOrderInYear, Year);
        _Day = Date1._Day;
        _Month = Date1._Month;
        _Year = Date1._Year;

        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    void SetDay(int Day) {
        _Day = Day;
        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    int GetDay() {
        return _Day;
    }

    void SetMonth(int Month) {
        _Month = Month;
        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    int GetMonth() {
        return _Month;
    }

    void SetYear(int Year) {
        _Year = Year;
        _DayOrder = DetermineDayOrder(_Year, _Month, _Day);
        _DayName = DetermineDayName(_DayOrder);
    }

    int GetYear() {
        return _Year;
    }

	void SetHour(int Hour) {
		_Hour = Hour;
	}
    int GetHour() {
		return _Hour;
	}

    void SetMinute(int Minute) {
		_Minute = Minute;
	}
    int GetMinute() {
		return _Minute; 
	}

    void SetSecond(int Second) {
		_Second = Second; 
	}
    int GetSecond() {
		return _Second; 
	}

    void Print() {
        std::cout << DateToString() << '\n';
    }

    static void PrintHeaderOfMonthCalendar(int Month) {
        // Print the current month name
        std::cout << "_______________" << DeterMineMonthName(Month) << "___________________\n\n";
        // Print the columns
        std::cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";
    }

    static void printMonthCalendar(int Year, int Month, int Day) {

        short DayOrder = DetermineDayOrder(Year, Month, Day);
        std::string DayName = DetermineDayName(DayOrder);
        
        PrintHeaderOfMonthCalendar(Month);
        
        int NumOfDays = NumberOfDaysInMonth(Year, Month);
        int j = 0;
        
        for(int i = 1; i <= NumOfDays + j; ++i) {
            if(i >= DayOrder + 1) {
                std::cout << std::setw(3) << i - j << "  ";
            }
            else {
                j++; // Print appropriate spaces
                std::cout << "     ";
            }
            
            if(i % 7 == 0) std::cout << '\n';
        }
        
        std::cout << "\n_____________________________________\n\n";
    }

    void printMonthCalendar() {
        printMonthCalendar(_Year, _Month, _Day);
    }

    static void printYearCalendar(int Year) {
        std::cout << "\n_____________________________________\n\n";
        std::cout << "\t   Calendar * " << Year;
        std::cout << "\n_____________________________________\n\n";
        
        for(int Month = 1; Month < 13; ++Month) {
            int NumOfDays = NumberOfDaysInMonth(Year, Month);
            printMonthCalendar(Year, Month, NumOfDays);
        }
    }

    void printYearCalendar() {
        std::cout << "\n_____________________________________\n\n";
        std::cout << "\t   Calendar * " << _Year;
        std::cout << "\n_____________________________________\n\n";
        
        for(int Month = 1; Month < 13; ++Month) {
            int NumOfDays = NumberOfDaysInMonth(_Year, Month);
            printMonthCalendar(_Year, Month, NumOfDays);
        }
    }

    static int DaysFromTheBeginingOfTheYear(const short &Day, const short &Month, const short &Year) {
		int TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++) {
			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;
		return TotalDays;
	}

    short DaysFromTheBeginingOfTheYear() {
		short TotalDays = 0;

		for (int i = 1; i <= _Month - 1; i++) {
			TotalDays += NumberOfDaysInMonth(i, _Year);
		}

		TotalDays += _Day;
		return TotalDays;
	}

    static clsDate GetDateFromDayOrderInYear(const short &DateOrderInYear, const short &Year) {
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date._Year = Year;
		Date._Month = 1;

		while (true) {
			MonthDays = NumberOfDaysInMonth(Date._Month, Year);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else {
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

    void AddDays(const short &Days) {
		short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
		short MonthDays = 0;

		_Month = 1;

		while (true) {
			MonthDays = NumberOfDaysInMonth(_Month, _Year);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				_Month++;

				if (_Month > 12) {
					_Month = 1;
					_Year++;
				}
			}
			else {
				_Day = RemainingDays;
				break;
			}
		}
    }

    static bool IsDate1BeforeDate2(const clsDate &Date1, const clsDate &Date2){
		return  (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}

	bool IsDateBeforeDate2(const clsDate &Date2) {
		//note: *this sends the current object :-) 
		return  IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(const clsDate &Date1, const clsDate &Date2) {
		return  (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(const clsDate &Date2) {
		return  IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(const clsDate &Date) {
		return (Date._Day == NumberOfDaysInMonth(Date._Month, Date._Year));
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(const short &Month) {
		return (Month == 12);
	}

    static clsDate AddOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date._Month)) {
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}
			else {
				Date._Day = 1;
				Date._Month++;
			}
		}
		else {
			Date._Day++;
		}

		return Date;
	}

	void AddOneDay() {
		*this = AddOneDay(*this);
	}

    static void SwapDates(clsDate & Date1, clsDate & Date2) {
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {
		//this will take care of negative diff
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {
			//Swap Dates 
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2)) {
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

    static short CalculateMyAgeInDays(clsDate DateOfBirth) {
		return GetDifferenceInDays(DateOfBirth, clsDate::GetCurrentDate(), true);
	}
	//above no need to have nonstatic function for the object because it does not depend on any data from it.

    static clsDate IncreaseDateByOneWeek(clsDate & Date) {
		for (int i = 1; i <= 7; i++) {
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}

	clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date){
		for (short i = 1; i <= Weeks; i++) {
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks) {
		IncreaseDateByXWeeks(Weeks, *this);
	}

	clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (Date._Month == 12) {
			Date._Month = 1;
			Date._Year++;
		}
		else {
			Date._Month++;
		}

		//last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
		// be 28/2/2022

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth) {
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	clsDate IncreaseDateByXDays(short Days, clsDate& Date) {
		for (short i = 1; i <= Days; i++) {
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short Days) {
		IncreaseDateByXDays(Days, *this);
	}

	clsDate IncreaseDateByXMonths(short Months, clsDate& Date) {
		for (short i = 1; i <= Months; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short Months) {
		IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {
		Date._Year++;
		return Date;
	}

	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	clsDate IncreaseDateByXYears(short Years, clsDate& Date) {
		Date._Year += Years;
		return Date;
	}

	void IncreaseDateByXYears(short Years) {
		IncreaseDateByXYears(Years, *this);
	}

	clsDate IncreaseDateByOneDecade(clsDate& Date) {
		//Period of 10 years
		Date._Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}

	clsDate IncreaseDateByXDecades(short Decade, clsDate& Date) {
		Date._Year += Decade * 10;
		return Date;
	}

	void IncreaseDateByXDecades(short Decade) {
		IncreaseDateByXDecades(Decade, *this);
	}

	clsDate IncreaseDateByOneCentury(clsDate& Date) {
		//Period of 100 years
		Date._Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		//Period of 1000 years
		Date._Year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}

    static clsDate DecreaseDateByOneDay(clsDate Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}
			else {
				Date._Month--;
				Date._Day = NumberOfDaysInMonth(Date._Month, Date._Year);
			}
		}
		else {
			Date._Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay() {
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate &Date) {
		for (int i = 1; i <= 7; i++) {
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate &Date) {
		for (short i = 1; i <= Weeks; i++) {
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks) {
		DecreaseDateByXWeeks(Weeks ,*this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate &Date) {
		if (Date._Month == 1) {
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;

		//last check day in date should not exceed max days in the current month
	    // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
	    // be 28/2/2022

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth) {
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate &Date) {
		for (short i = 1; i <= Days; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days) {
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate &Date) {
		for (short i = 1; i <= Months; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short Months) {
		DecreaseDateByXMonths( Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate &Date) {
		Date._Year--;
		return Date;
	}

	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate &Date) {
		Date._Year -= Years;
		return Date;
	}

	void DecreaseDateByXYears(short Years) {
		DecreaseDateByXYears(Years ,*this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate &Date) {
		//Period of 10 years
		Date._Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate &Date) {
		Date._Year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecades(short Decades) {
		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate &Date) {
		//Period of 100 years
		Date._Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate &Date) {
		//Period of 1000 years
		Date._Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

    static short IsEndOfWeek(const clsDate &Date) {
		return  DetermineDayOrder(Date._Day, Date._Month, Date._Year) == 6;
	}

	short IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

    static bool IsWeekEnd(const clsDate &Date) {
		//Weekends are Fri and Sat
		short DayIndex = DetermineDayOrder(Date._Day, Date._Month, Date._Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd() {
		return  IsWeekEnd(*this);
	}

    static bool IsBusinessDay(const clsDate &Date) {
		//Weekends are Sun,Mon,Tue,Wed and Thur

	   /*
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex >= 5 && DayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay() {
		return  IsBusinessDay(*this);
	}

    static short DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - DetermineDayOrder(Date._Day, Date._Month, Date._Year);
	}

	short DaysUntilTheEndOfWeek() {
		return  DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date1) {
		clsDate EndOfMontDate;
		EndOfMontDate._Day = NumberOfDaysInMonth(Date1._Month, Date1._Year);
		EndOfMontDate._Month = Date1._Month;
		EndOfMontDate._Year = Date1._Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date1) {
		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date1._Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);
	}

	short DaysUntilTheEndOfYear() {
		return  DaysUntilTheEndOfYear(*this);
	}

    //i added this method to calculate business days between 2 days
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo) {
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo)) {
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;
	}

	// static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {
	// 	/*short Days = 0;
	// 	while (IsDate1BeforeDate2(DateFrom, DateTo)) {
	// 		if (IsBusinessDay(DateFrom))
	// 			Days++;

	// 		DateFrom = AddOneDay(DateFrom);
	// 	}*/

	// 	return CalculateBusinessDays(DateFrom, DateTo);
	// }

	//above method is eough , no need to have method for the object
	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays) {
		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++) {
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

    static bool IsDate1AfterDate2(const clsDate &Date1, const clsDate &Date2) {
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2( clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(const clsDate &Date1, const clsDate &Date2) {
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/
			 //this is faster

		return enDateCompare::After;
	}

	enDateCompare CompareDates(const clsDate &Date2) {
		return CompareDates(*this, Date2);
	}

    clsDate& operator=(const clsDate& other) {
        if(this != &other) {
            this->_Day = other._Day;
            this->_Month = other._Month;
            this->_Year = other._Year;
        }
        return *this;
    }
};