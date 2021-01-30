#pragma once

#include "../StringToIntegerStateHandler/StringToIntegerStateHandler.h"

class StartStringToIntegerStateHandler : public StringToIntegerStateHandler {
public:
	StringToIntegerParserState handle(char symbol, IntData &data) const;
};

