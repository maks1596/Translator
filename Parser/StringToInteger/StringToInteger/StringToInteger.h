#pragma once

#include <string>
#include <map>

#include "../StateHandlers/StringToIntegerStateHandler/StringToIntegerStateHandler.h"

using namespace std;

class StringToInteger {
public:
	static int parse(const string &inString);

private:
	static IntData m_data;
	static const map<StringToIntegerParserState, StringToIntegerStateHandler *> m_stateHandlers;
};

