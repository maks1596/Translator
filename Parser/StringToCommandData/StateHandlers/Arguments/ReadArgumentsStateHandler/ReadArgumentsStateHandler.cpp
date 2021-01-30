#include "ReadArgumentsStateHandler.h"

StringToCommandDataState ReadArgumentsStateHandler::handle(CommandData &, unsigned &curPos, string &inString) const {
	StringToCommandDataState newState = READ_ARGUMENTS;
	switch (inString[curPos])
	{
		case END_OF_LINE: {
			newState = ARGUMENTS_READED;
		} break;
		case SEMICOLON: {
			newState = ARGUMENTS_READED;
		} break;
		default: {
			curPos++;
		} break;
	}
	return newState;
}
