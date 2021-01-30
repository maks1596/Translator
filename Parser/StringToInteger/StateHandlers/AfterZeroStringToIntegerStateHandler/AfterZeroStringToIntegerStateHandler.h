#pragma once
#include "../StringToIntegerStateHandler/StringToIntegerStateHandler.h"
class AfterZeroStringToIntegerStateHandler : public StringToIntegerStateHandler {
public:
	StringToIntegerParserState handle(char symbol, IntData &data) const;
};

