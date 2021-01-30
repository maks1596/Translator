#pragma once
#include "..\IStringToArgumentsParserStateHandler.h"
class ArgumentReadedStateHandler : public IStringToArgumentsParserStateHandler {
public:
	StringToArgumentsParserState handle(Arguments &arguments, unsigned &curPos, string &inString) const;

private:
	string trim(const string& inString) const;
};

