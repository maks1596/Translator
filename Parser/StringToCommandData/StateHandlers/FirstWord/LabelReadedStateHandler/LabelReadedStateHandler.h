#pragma once
#include "../../IStringToCommandDataParserStateHandler.h"
class LabelReadedStateHandler :	public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

