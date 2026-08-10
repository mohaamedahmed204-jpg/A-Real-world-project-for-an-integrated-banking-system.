#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib> 
#include <limits>
#include "clsInputValidate.h"

class  clsUtil {
public:
    template<typename T>
    static T RandomNumber(const T &From, const T &To) {
        T randnum = rand() % (To - From + 1) + From;
        return randnum;
    }

    static void Srand() {
        srand((unsigned)time(NULL));
    }

    enum enCharType {
        SmallLetter = 1, CapitalLetter = 2,
        SpecialChar = 3, Digit = 4, MixChars = 5
    };

    static char GetRandChar(const enCharType &CharType) {
        switch(CharType) {
            case enCharType::CapitalLetter: {
                return RandomNumber(65, 90);
                break;
            }
            case enCharType::SmallLetter: {
                return RandomNumber(97, 122);
                break;
            }
            case enCharType::SpecialChar: {
                return RandomNumber(33, 47);
                break;
            }
            case enCharType::Digit: {
                return RandomNumber(48, 57);
                break;
            }
              case enCharType::MixChars: {
                return RandomNumber(48, 122);
                break;
            }
        }

        return '\0';
    }

    static std::string GenerateWord(const enCharType &CharType, const short &Length) {
        std::string word = "";

        for(int i = 1; i <= Length; i++) {
            word = word + GetRandChar(CharType);
        }
        return word;
    }

    static std::string GenerateKey(const enCharType &CharType) {
        std::string key = "";

        key = GenerateWord(CharType, 4) + "-";
        key = key + GenerateWord(CharType, 4) + "-";
        key = key + GenerateWord(CharType, 4) + "-";
        key = key + GenerateWord(CharType, 4);

        return key;
    }

    static void GenerateKeys(const enCharType &CharType, const short &NumOfKeys) {
        
        for(int i = 1; i <= NumOfKeys; i++) {
            std::cout << "Key [ " << i << " ] :";
            std::cout << GenerateKey(CharType) << '\n';
        }
    }

    template<typename T>
    static void Swap(T &A, T &B) {
        T temp;

        temp = A;
        A = B;
        B = temp;
    }

    template<typename T>
    static void ShuffleArray(T arr[], int arrLength) {
        for(int i = arrLength - 1; i > 0; --i) {
            // التبديل مع عنصر عشوائي من العناصر التي تسبقه فقط
            Swap(arr[i], arr[RandomNumber(0, i)]);
        }
    }

    static void FillArrayWithRandNum(int arr[], const int& arrLength, const int &From, const int &To) {
        for(int i = 0; i < arrLength; i++) {
            arr[i] = RandomNumber(From, To);
        }
    }

    static void FillArrWithRandWords(std::string arr[], const int& arrLength, const enCharType &CharType, const int &WordLength) {
        for(int i = 0; i < arrLength; ++i) {
            arr[i] = GenerateWord(CharType, WordLength);
        }
    }

    static void FillArrayWithRandKeys(std::string arr[], const int &arrLength, const enCharType &CharType) {
        for(int i = 0; i < arrLength; i++) {
            arr[i] = GenerateKey(CharType);
        }
    }

    static std::string Seperator(const int &Size, const char &seper) {
        return std::string(Size, seper);
    }

    static void ClearBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static std::string Encryption(std::string Text, int EncryptionKey) {
        int k = (126 - 32 + 1);
        EncryptionKey = ((EncryptionKey % k) + k) % k;
        
        for(int i = 0 ; i < Text.size(); i++) {
            int currentVal = Text[i] + EncryptionKey;
            
            if(currentVal > 126) currentVal = (currentVal - 127) + 32;
            if(currentVal < 32) currentVal = (currentVal - 32) + 127;
            
            Text[i] = currentVal;
        }
        return Text;
    }

    static std::string Decryption(std::string Text, int EncryptionKey) {
        return Encryption(Text, EncryptionKey * -1);
    }

    static std::string NumberToText(int Number) {

        if (Number == 0) {
           return "";
        }

        if (Number >= 1 && Number <= 19) {
           std::string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
            "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
            "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

           return  arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99) {
           std::string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
           return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199) {
           return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999) {
           return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999) {
           return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999) {
           return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999) {
           return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999) {
           return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999) {
           return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else {
           return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }

    static void PressEnterToContinue() {
        //std::cout << "\nPress Double Enter To Back To Main Menu........\n";
        clsInputValidate::ClearBuffer();
        std::cin.get();
    }
};