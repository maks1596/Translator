#pragma once

#include "../../IParserStateHandler.h"
#include "../../../CommandData/CommandData.h"

enum StringToCommandDataState {
	BEGIN_READ_FIRST_WORD,
	READ_FIRST_WORD,
	LABEL_READED,

	BEGIN_READ_COMMAND,
	READ_COMMAND,
	COMMAND_READED,

	READ_ARGUMENTS,
	ARGUMENTS_READED,

	READ_COMMENT,
	STOP_STRING_TO_COMMAND_DATA_PARSE
};

class IStringToCommandDataParserStateHandler : public IParserStateHandler<StringToCommandDataState, CommandData> {
public:
	virtual StringToCommandDataState handle(CommandData &commandData, unsigned &curPos, string &inString) const = 0;
};
