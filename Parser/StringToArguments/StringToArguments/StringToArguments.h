#pragma once

#include <vector>

#include "../../IFromStringParser.h"
#include "../../../Parser/StringToArguments/StateHandlers/IStringToArgumentsParserStateHandler.h"


class StringToArguments : public IFromStringParser<Arguments> {
public:
	StringToArguments();
	~StringToArguments();

	Arguments parse(const string &inString) const;

private:
	IStringToArgumentsParserStateHandler ** m_stateHandlers;
};

