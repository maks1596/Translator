#pragma once
#include "../StringToIntegerStateHandler/StringToIntegerStateHandler.h"
class ReadNumberStringToIntegerStateHandler : public StringToIntegerStateHandler {
public:
	StringToIntegerParserState handle(char symbol, IntData &data) const;
};

