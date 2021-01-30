#include "ReadCommandStateHandler.h"

StringToCommandDataState ReadCommandStateHandler::handle(CommandData &, unsigned &curPos, string &inString) const {
	StringToCommandDataState newState = READ_COMMAND;
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
		default: {
			curPos++;
		} break;
	}
	return newState;
}
