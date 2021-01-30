#pragma once

#include <string>
#include <map>

using namespace std;

enum ErrorCode {
	IllegalLabelName = 0,
	IllegalCommandName,
	InvalidIntegerFormat,
	EmptyExpression,
	UndefinedToken,
	DivideByZero,
	MissingCloseBracket,
	IllegalFunction,
	IllegalFunctionArguments,
	UndefinedLabel,
	LabelRedefinition,
	UndefinedAbsoluteLabel,
	UndefinedRegister,
	NotEnoughArguments,
	TooMuchArguments,
	NotFloatArgument,
	MovMMNotAlowed,
	UnknownCommand,
	InvalidArguments,
	HaveNoEndCommand
};

extern const map<ErrorCode, string> Errors;

