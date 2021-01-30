#include "StringToInteger.h"

#include "../StateHandlers/StartStringToIntegerStateHandler/StartStringToIntegerStateHandler.h"
#include "../StateHandlers/AfterZeroStringToIntegerStateHandler/AfterZeroStringToIntegerStateHandler.h"
#include "../StateHandlers/ReadNumberStringToIntegerStateHandler/ReadNumberStringToIntegerStateHandler.h"

const map<StringToIntegerParserState, StringToIntegerStateHandler *> StringToInteger::m_stateHandlers = {
	make_pair(START, new StartStringToIntegerStateHandler()),
	make_pair(AFTER_ZERO, new AfterZeroStringToIntegerStateHandler()),
	make_pair(READ_NUMBER, new ReadNumberStringToIntegerStateHandler())
};

IntData StringToInteger::m_data;

int StringToInteger::parse(const string &inString) {
	m_data.number = 0;
	StringToIntegerParserState currentState = START;
	for (char symbol : inString)
		currentState = m_stateHandlers.at(currentState)->handle(symbol, m_data);
	return m_data.number * m_data.sign;
}
