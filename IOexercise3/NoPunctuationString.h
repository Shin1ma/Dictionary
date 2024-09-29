#pragma once
#include <iostream>
#include <sstream>

class NoPunctuationString
{
private:
	std::istream& InputSource;	//source of input, Buffer to get input to the string, list of characters considered whitespaces(in case of ' abbreviations)
	std::stringstream Buffer;
	std::string WhitespaceChars;
	const std::string Abbreviations[5] = {"t", "m", "re", "ve", "s"};
	bool CapitalSensitive;		//do we worry about capital letters, has the buffer been emptied into the string
	bool Emptied;

public:
	NoPunctuationString(std::istream& source, std::string whitespacechar, bool capitalsensitive):
		InputSource(source), Buffer(""), WhitespaceChars(whitespacechar), CapitalSensitive(capitalsensitive), Emptied(false)
	{}

	bool IsWhiteSpace(char ch);	//checks if the character is punctuation and to be considerede whitespace

	std::string GetLongForm(std::string abbr);		//gets long form of abbreviations after ' like: t, ve, etc..

	NoPunctuationString& operator>>(std::string& s);	//operators
	operator bool();

	std::string GetWhitespaceChars() { return WhitespaceChars; }	//getters and setters
	bool IsCapitalSensitive() { return CapitalSensitive; }
	void SetCapitalSensitive(bool value) { CapitalSensitive = value; }
	void SetWhitespaceChars(std::string newchars) { WhitespaceChars = newchars; }
	void NewWhitespaceChar(char ch) { WhitespaceChars += ch; }


};

