#include "BeginReadCommandStateHandler.h"

StringToCommandDataState BeginReadCommandStateHandler::handle(CommandData &, unsigned &curPos, string &inString) const {
	StringToCommandDataState newState = BEGIN_READ_COMMAND;
	switch (inString[curPos])
	{
		case END_OF_LINE: {
			newState = STOP_STRING_TO_COMMAND_DATA_PARSE;
		} break;
		case TABULATION:
		case SPACE: {
			inString.erase(inString.begin());
		} break;
		case SEMICOLON: {
			newState = READ_COMMENT;
		} break;
		default: {
			newState = READ_COMMAND;
		} break;
	}
	return newState;
}
