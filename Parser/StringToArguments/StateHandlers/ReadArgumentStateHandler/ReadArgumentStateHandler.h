#pragma once
#include "..\IStringToArgumentsParserStateHandler.h"
class ReadArgumentStateHandler : public IStringToArgumentsParserStateHandler {
public:
	StringToArgumentsParserState handle(Arguments &arguments, unsigned &curPos, string &inString) const;
};

