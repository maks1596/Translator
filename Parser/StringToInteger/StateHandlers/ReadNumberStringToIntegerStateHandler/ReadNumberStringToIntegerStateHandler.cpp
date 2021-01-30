#include "ReadNumberStringToIntegerStateHandler.h"

StringToIntegerParserState ReadNumberStringToIntegerStateHandler::handle(char symbol, IntData &data) const {
	data.number = data.number * data.base + digit(symbol, data.base);
	return READ_NUMBER;
}
