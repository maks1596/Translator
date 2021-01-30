#include "ArgumentReadedStateHandler.h"

#include <sstream>

StringToArgumentsParserState ArgumentReadedStateHandler::handle(Arguments & arguments, unsigned & curPos, string & inString) const {
	arguments.push_back(trim(inString.substr(0, curPos)));
	inString.erase(inString.begin(), inString.begin() + curPos);
	if (!inString.empty()) {				// Если не последний аргумент
		curPos = 0;
		inString.erase(inString.begin());	// Удалили запятую после аргумента
		return BEGIN_READ_ARGUMENT;
	}
	return STOP_STRING_TO_ARGUMENTS_PARSE;
}

string ArgumentReadedStateHandler::trim(const string & inString) const {
	if (inString.empty()) return inString;

	stringstream ss(inString);
	string result, mediator;
	while (ss >> mediator) 
		result += mediator;
	return result;
}
