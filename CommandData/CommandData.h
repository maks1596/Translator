#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <regex>

#include "../Errors/Errors.h"
#include "../Parser/SpecialSymbols.h"
#include "../Parser/StringToArguments/StringToArguments/StringToArguments.h"
#include "../Dependencies.h"

using namespace std;

class CommandData {
public:
	void setLabel(const string &label);
	string getLabel() const;

	void setCommand(const string &command);
	string getCommand() const;

	void setArguments(const string &arguments);
	vector<string> getArguments() const;

	void setComment(const string &comment);
	string getComment() const;

	void setCommandCode(const CommandCode &commandCode);
	CommandCode getCommandCode() const;

	void setMachineCode(const vector<Byte> &machineCode);
	vector<Byte> getMachineCode() const;

	void setAddress(const unsigned &address);
	unsigned getAddress() const;

	void addError(const ErrorCode &errorCode);
	bool hasErrors() const;

	string argumentsToString() const;
	string errorsToString() const;
	string machineCodeToString() const;
	string toString() const;

	friend ostream& operator<<(ostream & os, const CommandData &commandData);

private:
	string m_label;
	string m_command;
	vector<string> m_arguments;
	string m_comment;

	CommandCode m_commandCode;
	vector<Byte> m_machineCode;
	unsigned m_address;
	vector<ErrorCode> m_errorCodes;

	static const string IDENTIFIER_REGEX;
	static const StringToArguments m_argumentsParser;
};
