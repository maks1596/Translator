#include "ArgumentsReadedStateHandler.h"

StringToCommandDataState ArgumentsReadedStateHandler::handle(CommandData &command, unsigned &curPos, string &inString) const {
	command.setArguments(inString.substr(0, curPos));
	inString.erase(inString.begin(), inString.begin() + curPos);
	curPos = 0;
	if (inString.empty())
		return STOP_STRING_TO_COMMAND_DATA_PARSE;
	else
		return READ_COMMENT;
}
