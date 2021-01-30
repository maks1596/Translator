#include "BeginReadFirstWordStateHandler.h"

StringToCommandDataState BeginReadFirstWordStateHandler::handle(CommandData &, unsigned &curPos, string &inString) const {
	StringToCommandDataState newState = BEGIN_READ_FIRST_WORD;
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
		case COLON: {
			inString.erase(inString.begin());
			return BEGIN_READ_COMMAND;
		} break;
		default: {
			newState = READ_FIRST_WORD;
		} break;
	}
	return newState;
}
