#pragma once
#include "../IStringToCommandDataParserStateHandler.h"
class ReadCommentStateHandler : public IStringToCommandDataParserStateHandler {
public:
	StringToCommandDataState handle(CommandData &command, unsigned &curPos, string &inString) const;
};

