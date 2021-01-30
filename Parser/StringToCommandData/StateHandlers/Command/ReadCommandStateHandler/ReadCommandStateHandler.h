#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class ReadCommandStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

