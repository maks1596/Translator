#include "BeginReadArgumentStateHandler.h"

StringToArgumentsParserState BeginReadArgumentStateHandler::handle(Arguments &, unsigned & curPos, string & inString) const
{
	StringToArgumentsParserState newState = BEGIN_READ_ARGUMENT;
	switch (inString[curPos])
	{
		case SPACE: {
			inString.erase(inString.begin());
		} break;
		case END_OF_LINE: {
			newState = STOP_STRING_TO_ARGUMENTS_PARSE;
		} break;
		default: {
			newState = READ_ARGUMENT;
		} break;
	}
	return newState;
}
