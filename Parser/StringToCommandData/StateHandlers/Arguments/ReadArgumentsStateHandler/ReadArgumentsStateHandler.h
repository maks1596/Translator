#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class ReadArgumentsStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

