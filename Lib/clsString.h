#pragma once
#include <iostream>
#include <vector>

class clsString {
private:
    std::string _Value;

public:
    // Must include all types of letters
    enum enKindOfLetter { Small = 1, Capital = 2, AllLetters = 3};
    // For Case
    enum enMatchCase {MatchCase = 1, NotMatchCase = 2};

    clsString() {
        _Value = "";
    }

    clsString(const std::string &Value) {
        this->_Value = Value;
    }

    void setValue(const std::string &Value) {
        _Value = Value;
    }

    std::string getValue() {
        return _Value;
    }

    static int Length(const std::string &S1) {
        return S1.length();
    }

    int Length() {
        return _Value.length();
    }

    static int CountWords(const std::string &S1) {
        std::string delim = " "; // delimiter
        int Counter = 0;

        std::string vWord = ""; // define a string variable
        // use find() function to get the position of the delimiters
        
        int pos = -1;
        int start = 0;
        
        while( (pos = S1.find(delim, start)) != std::string::npos ) {
            vWord = S1.substr(start, pos - start);
            
            if (vWord != "") {
                Counter++;
            }
            start = pos + delim.length();
        }
        
        if (S1 != "") {
            Counter++; // it counts the last word of the string.
        }
        return Counter;
    }

    int CountWords() {
        return CountWords(_Value);
    }

    static std::string UpperCaseEachFirstLetterInWord(std::string &Line) {
        bool isFirstLetter = true;
        
        for(int i = 0; i < Line.size(); ++i) {
            if(Line[i] != ' ' && isFirstLetter) {
                isFirstLetter = false;
                Line[i] = toupper(Line[i]);
            }
            
            isFirstLetter = (Line[i] == ' ');
        }
        return Line;
    }

    void UpperCaseEachFirstLetterInWord() {
        // no need to return value , this function will directly update the object value
        _Value = UpperCaseEachFirstLetterInWord(_Value);
    }

    static std::string LowerCaseEachFirstLetterInWord(std::string &Line) {
        bool isFirstLetter = true;
        
        for(int i = 0; i < Line.size(); ++i) {
            if(Line[i] != ' ' && isFirstLetter) {
                isFirstLetter = false;
                Line[i] = tolower(Line[i]);
            }
            
            isFirstLetter = (Line[i] == ' ');
        }
        return Line;
    }

    void LowerCaseEachFirstLetterInWord() {
        // no need to return value , this function will directly update the object value
        _Value = LowerCaseEachFirstLetterInWord(_Value);
    }

    static std::string UpperAllString(std::string &S1) {
        for(char &c : S1) {
            c = toupper(c);
        }
        return S1;
    }

    void UpperAllString() {
        _Value = UpperAllString(_Value);
    }

    static std::string LowerAllString(std::string &S1) {
        for(char &c : S1) {
            c = tolower(c);
        }
        return S1;
    }

    void LowerAllString() {
        _Value = LowerAllString(_Value);
    }

    static char InvertChar(char &c) {
        return (islower(c) ? toupper(c) : tolower(c));
    }

    static std::string InvertAllChars(std::string &Line) {        
        for(char &c : Line) {
            c = InvertChar(c);
        }
        return Line;
    }

    void InvertAllChars() {
        _Value = InvertAllChars(_Value);
    }

    static int CountTypeOfLetter(const std::string &Line, enKindOfLetter LetterType = enKindOfLetter::AllLetters) {
    
        int Counter = 0;
        
        for(char c : Line) {
            if(islower(c) && LetterType == enKindOfLetter::Small) {
                Counter++;
            }
            else if(isupper(c) && LetterType == enKindOfLetter::Capital) {
                Counter++;
            }
            else if((isalpha(c) && LetterType == enKindOfLetter::AllLetters)) {
                Counter++;
            }
        }
        return Counter;
    }

    int CountTypeOfLetter(enKindOfLetter LetterType = enKindOfLetter::AllLetters) {
        return CountTypeOfLetter(_Value, LetterType);
    }

    static int CountSpecificLetter(const std::string &Line, const char &Target, enMatchCase Case) {
    
        int Counter = 0;
        
        for(char c : Line) {
            if(enMatchCase::MatchCase == Case) {
                if(c == Target) Counter++;
            }
            else {
                if(tolower(c) == tolower(Target)) Counter++;
            }
        }
        return Counter;
    }

    int CountSpecificLetter(const char &Target, enMatchCase Case) {
        return CountSpecificLetter(_Value, Target, Case);
    }

    static bool IsVowel(char Ch1) {
        Ch1 = toupper(Ch1);
        return (Ch1 == 'A' || Ch1 == 'E' || Ch1 == 'I' || Ch1 == 'O' || Ch1 == 'U');
    }

    static int CountVowels(const std::string &S1) {
        int Counter = 0;

        for(char c : S1) {
            if(IsVowel(c))
                Counter++;
        }
        return Counter;
    }

    int CountVowels() {
        return CountVowels(_Value);
    }

    static std::vector<std::string> SplitEachWordInVector(const std::string &S1, const std::string &delim) {
    
        std::vector<std::string> vData;
        std::string vWord = "";
        
        int pos = -1;
        int start = 0;
        
        // use find() function to get the position of the delimiters
        while( (pos = S1.find(delim, start)) != std::string::npos ) {
            vWord = S1.substr(start, pos - start); // store the word
            
            vData.emplace_back(vWord);
            start = pos + delim.length();
        }
        
        if(S1 != "")
            vData.emplace_back(S1.substr(start));
        
        return vData;
    }

    std::vector<std::string> SplitEachWordInVector(const std::string &Delim) {
        return SplitEachWordInVector(_Value, Delim);
    }

    static std::string TrimLeft(const std::string &S1) {
        // Remove all extra spaces from the left
        for(int i = 0; i < S1.size(); ++i) {
            if(S1[i] != ' ') {
                return S1.substr(i, S1.size() - 1);
            }
        }
        return "";
    }

    void TrimLeft() {
        _Value = TrimLeft(_Value);
    }

    static std::string TrimRight(const std::string &S1) {
        // Remove all extra spaces from the Right
        for(int i = S1.size() - 1; i > -1; --i) {
            if(S1[i] != ' ') {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    void TrimRight() {
        _Value = TrimRight(_Value);
    }

    static std::string Trim(const std::string &S1) {
        // Remove all extra spaces from two sides
        return TrimLeft(TrimRight(S1));
    }

    void Trim() {
        _Value = TrimLeft(TrimRight(_Value));
    }

    static std::string JoinString(const std::vector<std::string> &V1, const std::string &delim) {
    
        std::string FinalString = "";
        
        for(int i = 0; i < V1.size(); ++i) {
            FinalString += V1[i];   
            if(V1.size() - 1 != i) FinalString += delim;
        }
        return FinalString;
    }

    static std::string JoinString(const std::string Array[], const int &Size, const std::string &delim) {
        
        std::string FinalString = "";
        
        for(int i = 0; i < Size; ++i) {
            FinalString += Array[i];
            if(Size - 1 != i) FinalString += delim;
        }
        return FinalString;
    }

    static std::string ReverseWords(const std::string &S1) {
    
        std::vector<std::string> vWord;
        vWord = SplitEachWordInVector(S1, " ");
        
        std::string AnsString = "";
        
        for(int i = vWord.size() - 1; i > -1; --i) {
            AnsString += vWord[i];
            if(i != 0) AnsString += " ";
        }
        return AnsString;
    }

    void ReverseWords() {
        _Value = ReverseWords(_Value);
    }

    static std::string ReplaceWordInStringCustom(std::string &Orginal, std::string ToReplace, const std::string &Replace, enMatchCase MatchCase = enMatchCase::MatchCase) {
    
        std::vector<std::string> vWords = SplitEachWordInVector(Orginal, " ");
        
        std::string ToReplaceLower = MatchCase == enMatchCase::MatchCase ? "" : LowerAllString(ToReplace);
        
        for(std::string& s : vWords) {

            if(MatchCase == enMatchCase::MatchCase) {
                if(s == ToReplace) s = Replace;
            }
            else {
                if(LowerAllString(s) == ToReplaceLower) s = Replace;
            }
        }
        return JoinString(vWords, " ");
    }

    void ReplaceWordInStringCustom(std::string ToReplace, const std::string &Replace, enMatchCase MatchCase = enMatchCase::MatchCase) {
        _Value = ReplaceWordInStringCustom(_Value, ToReplace, Replace, MatchCase);
    }

    static std::string RemovePunctuations(std::string &s) {
    
        std::string FinalString = "";
        
        for(char& c : s) {
            if(!ispunct(c))
                FinalString += c;
        }
        return FinalString;
    }

    void RemovePunctuations() {
        _Value = RemovePunctuations(_Value);
    }
};