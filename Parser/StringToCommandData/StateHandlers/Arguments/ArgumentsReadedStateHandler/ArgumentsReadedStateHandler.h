#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class ArgumentsReadedStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

