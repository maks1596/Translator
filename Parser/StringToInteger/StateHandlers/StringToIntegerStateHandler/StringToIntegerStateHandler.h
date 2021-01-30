#pragma once

#include "../../../SpecialSymbols.h"
#include "../../../../Errors/Errors.h"

struct IntData {
	int number;
	int sign;
	int base;
};

enum StringToIntegerParserState {
	START,
	AFTER_ZERO,
	READ_NUMBER
};

class StringToIntegerStateHandler {
public:
	virtual StringToIntegerParserState handle(char symbol, IntData &data) const = 0;

protected:
	int digit(char symbol, int base = 10) const;
};
