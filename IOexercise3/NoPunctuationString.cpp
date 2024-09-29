#include "NoPunctuationString.h"


bool NoPunctuationString::IsWhiteSpace(char ch) {		//checks if character is to be considered whitespace
	for (int i = 0; i < WhitespaceChars.size(); i++) {
		if (ch == WhitespaceChars[i]) return true;
	}
	return false;
}

std::string NoPunctuationString::GetLongForm(std::string abbr) {	//gets long form of abbreviated forms
	if (abbr == Abbreviations[0]) return "not";
	if (abbr == Abbreviations[1]) return "am";
	if (abbr == Abbreviations[2]) return "are";
	if (abbr == Abbreviations[3]) return "have";
	if (abbr == Abbreviations[4]) return "is";
	return "";
}

NoPunctuationString& NoPunctuationString::operator>>(std::string& s) {
	while (!(Buffer >> s)) {		//if the buffer is empty/has laready gave output get input and reset emptied
		Emptied = false;
		
		if (Buffer.bad() || !InputSource.good()) return *this;
		Buffer.clear();

		std::string punctuatedstring;
		InputSource >> punctuatedstring;
		for (int i = 0; i < punctuatedstring.size(); i++) {

			if (!CapitalSensitive) punctuatedstring[i] = tolower(punctuatedstring[i]);	//handles capital letters and whitespace considered chars
			if (IsWhiteSpace(punctuatedstring[i])) { 
				if (punctuatedstring[i] == '\'') {		//checks if the char is the start of an abbreviation
					std::string abbreviation = "";
					for (int y = i + 1; y < punctuatedstring.size(); y++) abbreviation.push_back(punctuatedstring[y]);	//gets the abbreviation

					//erases the abbreviation from the word
					if (abbreviation == "t") { punctuatedstring.erase(punctuatedstring.begin() + (i - 1), punctuatedstring.end()); }	//in case of not abbreviation theres is a n earlier ex. I haven't -> I have not
					else { punctuatedstring.erase(punctuatedstring.begin() + i, punctuatedstring.end()); }

					punctuatedstring += " " + GetLongForm(abbreviation);	//replaces it with its long form
					i = -1;	//resets
				}
				else { punctuatedstring[i] = ' '; }	//for other characters they become white spaces
			}
		}
		Buffer.str(punctuatedstring);
	}
	Emptied = true;		//in the case the buffer succesfully transferred to s it has been emptied
	return *this;
}
NoPunctuationString::operator bool() {
	return Emptied || InputSource.good();	//return true if the buffer has been emptied and so an operation succeded or if the source of input is good
}