#include "ReadArgumentStateHandler.h"

StringToArgumentsParserState ReadArgumentStateHandler::handle(Arguments &, unsigned &curPos, string &inString) const {
	StringToArgumentsParserState newState = READ_ARGUMENT;
	switch (inString[curPos]) {
		case COMMA: 
		case END_OF_LINE: {
			newState = ARGUMENT_READED;
		} break;
		default: {
			curPos++;
		} break;
	}
	return newState;
}
