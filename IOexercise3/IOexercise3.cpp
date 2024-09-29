#include <iostream>
#include <vector>
#include <fstream>
#include "NoPunctuationString.h"

std::string LowerCaseString(std::string s); //transforms a string lowercase
int AlphabetToNum(const char& ch);  //converts an alphabetical char to it's number in the alphabet

bool IsAlphabeticallyBigger(std::string word, std::string compare); //checks if word is alphabetically bigger than compare

std::string GetLongestString(const std::vector<std::string>& stringvec);    //gets the longest string in a vector

void RemoveDuplicates(std::vector<std::string>& stringvec);     //removes duplicate words
void SortAlphabetical(std::vector<std::string>& stringvec); //sorts words by alphabetical order

std::vector<std::string> GetDictionary(std::vector<std::string> stringvec); //gets an alphabetical dictionary of the words from the word list


std::vector<std::string> GetInput(std::istream& in);            //gets input from an istream
void Output(std::ostream& out, std::vector<std::string> stringlist);    //gets out output

const char Alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
const int AlphabetSize = 26;

int main()
{
    try {
        std::string Iname;      //handles file opening
        std::string Oname;

        std::cout << "Input file:";
        std::cin >> Iname;
        std::ifstream input(Iname);
        if (!input) throw std::runtime_error("unvalid filename");

        std::cout << "Output file:";
        std::cin >> Oname;
        std::ofstream output(Oname);
        if (!output) throw std::runtime_error("unvalid filename");

        
        std::vector<std::string> StringVect = GetInput(input);      //gets input in the vector

        Output(output, GetDictionary(StringVect));     //outputs the dictionary of the vector
    }
    catch (const std::runtime_error& e) { std::cout << e.what() << "\n"; }
}

std::string GetLongestString(const std::vector<std::string>& stringvec) {       //replaces longest with the longest by comparing it time by time and returns
    std::string Longest;
    for (int i = 0; i < stringvec.size(); i++) {
        Longest = stringvec[i];
        for (int y = 0; y < stringvec.size(); y++) {
            if (Longest.size() < stringvec[y].size()) Longest = stringvec[y];
        }
    }
    return Longest;
}

std::string LowerCaseString(std::string s) {        //turns a string all lowercase
    std::string LowerCaseString;
    for (int i = 0; i < s.size(); i++) {
        LowerCaseString.push_back(tolower(s[i]));
    }
    return LowerCaseString;
}

int AlphabetToNum(const char& ch) {
    if (!isalpha((unsigned char)ch)) { 
        throw std::runtime_error("can't numerate a non alphabetical char"); }
    for (int i = 0; i < AlphabetSize; i++) {         //checks witch alphabetical character it is and returns position in the array
        if (tolower(ch) == Alphabet[i]) return i;
    }
}

bool IsAlphabeticallyBigger(std::string word, std::string compare) {
    if (word.size() < compare.size()) {                                 //basically goes character by character checking, if one is bigger or smaller returns, if they are equal go to the next char
        for (int i = 0; i < word.size(); i++) {
            if (!isalpha((unsigned char)word[i]) || !isalpha((unsigned char)compare[i])) continue;
            if (AlphabetToNum(word[i]) > AlphabetToNum(compare[i])) return true;
            if (AlphabetToNum(word[i]) < AlphabetToNum(compare[i])) return false;
        }
    }
    else {
        for (int i = 0; i < compare.size(); i++) {
            if (!isalpha((unsigned char)word[i]) || !isalpha((unsigned char)compare[i])) continue;
            if (AlphabetToNum(word[i]) > AlphabetToNum(compare[i])) return true;
            if (AlphabetToNum(word[i]) < AlphabetToNum(compare[i])) return false;
        }
    }
    return false;   //if the words are equal word isn't bigger than compare
}

void RemoveDuplicates(std::vector<std::string>& stringvec) {    //for every string it checks the vector from i+1 position for duplicates if found deletes them, then passes onto next word
    std::string TempString;
    for (int i = 0; i < stringvec.size(); i++) {
        TempString = LowerCaseString(stringvec[i]);
        for (int y = i + 1; y < stringvec.size(); y++) {
            if (TempString == LowerCaseString(stringvec[y])) { 
                stringvec.erase(stringvec.begin() + y); 
            }
        }
    }
}

void SortAlphabetical(std::vector<std::string>& stringvec) {
    std::vector<std::string> TempVec;
    std::string TempWord;
    bool Smallest;
    for (int i = 0; i < stringvec.size(); i++) {
        TempWord = stringvec[i];
        Smallest = true;                                //takes for granted that the word is the smallest and then checks if it isn't
        for (int y = 0; y < stringvec.size(); y++) {
            if (IsAlphabeticallyBigger(TempWord, stringvec[y])) Smallest = false; 
        }
        if (Smallest) {
            TempVec.push_back(TempWord);
            stringvec.erase(stringvec.begin() + i);
            i = -1;
        }
    }
    stringvec = TempVec;
}

std::vector<std::string> GetInput(std::istream& in) {
    std::vector<std::string> OperatedInput;     //instantiates the class and gets input trough NoPunctuationString
    std::string s;
    NoPunctuationString NoPunct(in, ",;.:@°#[]{}+*§|!\"£$%&/()=?'^1234567890^<>-_'\\", true);
    while (NoPunct >> s) OperatedInput.push_back(s);
    return OperatedInput;
}
void Output(std::ostream& out, std::vector<std::string> stringlist) {
    for (int i = 0; i < stringlist.size(); i++) out << stringlist[i] << "\n";    //prints output
}

std::vector<std::string> GetDictionary(std::vector<std::string> stringvec) {
    RemoveDuplicates(stringvec);
    SortAlphabetical(stringvec);
    return stringvec;
}