#include "StringToIntegerStateHandler.h"

int StringToIntegerStateHandler::digit(char symbol, int base/* = 10*/) const {
	static string digits = "0123456789abcdef";
	for (int d = 0; d < base; d++)
		if (symbol == digits[d]) return d;
	static string xdigits = "ABCDEF";
	for (int d = 0; d < 6; d++)
		if (symbol == xdigits[d]) return (10 + d);
	throw InvalidIntegerFormat;
}
