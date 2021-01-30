#include "StringToArguments.h"

#include "../StateHandlers/BeginReadArgumentStateHandler/BeginReadArgumentStateHandler.h"
#include "../StateHandlers/ReadArgumentStateHandler/ReadArgumentStateHandler.h"
#include "../StateHandlers/ArgumentReadedStateHandler/ArgumentReadedStateHandler.h"

StringToArguments::StringToArguments() {
	m_stateHandlers = new IStringToArgumentsParserStateHandler* [STOP_STRING_TO_ARGUMENTS_PARSE];
	m_stateHandlers[BEGIN_READ_ARGUMENT] = new BeginReadArgumentStateHandler();
	m_stateHandlers[READ_ARGUMENT] = new ReadArgumentStateHandler();
	m_stateHandlers[ARGUMENT_READED] = new ArgumentReadedStateHandler();
}


StringToArguments::~StringToArguments() {
	delete[] m_stateHandlers;
}

Arguments StringToArguments::parse(const string & inString) const {
	StringToArgumentsParserState currentState = BEGIN_READ_ARGUMENT;
	string copy = inString;
	unsigned currentPosition = 0;
	Arguments result = Arguments();
	while (currentState != STOP_STRING_TO_ARGUMENTS_PARSE) {
		currentState = m_stateHandlers[currentState]->handle(result, currentPosition, copy);
	}
	return result;
}
