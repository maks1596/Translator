#include "AfterZeroStringToIntegerStateHandler.h"

StringToIntegerParserState AfterZeroStringToIntegerStateHandler::handle(char symbol, IntData &data) const {
	switch (symbol) {
		case 'x':
		case 'X': {
			data.base = 16;
		} break;
		case 'b':
		case 'B': {
			data.base = 2;
		} break;
		default: {
			throw InvalidIntegerFormat;
		} break;
	}
	data.sign = +1;
	return READ_NUMBER;
}
