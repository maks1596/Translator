#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class CommandReadedStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};
