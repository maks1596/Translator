#include "StartStringToIntegerStateHandler.h"

StringToIntegerParserState StartStringToIntegerStateHandler::handle(char symbol, IntData &data) const {
	switch (symbol)
	{
		case ZERO: {
			return AFTER_ZERO;
		} break;
		case MINUS: {
			data.sign = -1;
		} break;
		case PLUS: {
			data.sign = +1;
		} break;
		default: {	// Цифра
			data.sign = +1;
			int d = digit(symbol);
			data.number = d;
		} break;
	}
	data.base = 10;
	return READ_NUMBER;
}
