#include "ReadFirstWordStateHandler.h"

StringToCommandDataState ReadFirstWordStateHandler::handle(CommandData &, unsigned &curPos, string &inString) const {
	StringToCommandDataState newState = READ_FIRST_WORD;
	switch (inString[curPos])
	{
		case END_OF_LINE: {
			newState = COMMAND_READED;
		} break;
		case TABULATION:
		case SPACE: {
			newState = COMMAND_READED;
		} break;
		case SEMICOLON: {
			newState = COMMAND_READED;
		} break;
		case COLON: {
			return LABEL_READED;
		} break;
		default: {
			curPos++;
		} break;
	}
	return newState;
}
