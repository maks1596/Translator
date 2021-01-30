#pragma once
#include "../IStringToArgumentsParserStateHandler.h"
class BeginReadArgumentStateHandler : public IStringToArgumentsParserStateHandler {
public:
	StringToArgumentsParserState handle(Arguments &arguments, unsigned &curPos, string &inString) const;
};

