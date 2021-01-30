#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class ReadFirstWordStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

