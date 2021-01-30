#pragma once

#include "../../IParserStateHandler.h"

#include <vector>

typedef vector<string> Arguments;

enum StringToArgumentsParserState {
	BEGIN_READ_ARGUMENT,
	READ_ARGUMENT,
	ARGUMENT_READED,
	STOP_STRING_TO_ARGUMENTS_PARSE
};

class IStringToArgumentsParserStateHandler : public IParserStateHandler<StringToArgumentsParserState, Arguments> {
public:
	virtual StringToArgumentsParserState handle(Arguments &arguments, unsigned &curPos, string &inString) const = 0;
};

