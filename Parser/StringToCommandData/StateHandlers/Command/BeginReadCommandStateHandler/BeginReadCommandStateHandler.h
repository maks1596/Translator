#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class BeginReadCommandStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

