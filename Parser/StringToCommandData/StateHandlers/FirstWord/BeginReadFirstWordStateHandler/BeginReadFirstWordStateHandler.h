#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class BeginReadFirstWordStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

