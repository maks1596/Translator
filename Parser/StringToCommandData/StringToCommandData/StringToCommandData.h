#pragma once

#include "../../IFromStringParser.h"
#include "../../../CommandData/CommandData.h"
#include "../StateHandlers/IStringToCommandDataParserStateHandler.h"

class StringToCommandData : public IFromStringParser<CommandData>
{
public:
	StringToCommandData();
	~StringToCommandData();

	CommandData parse(const string &inString) const;

private:
	IStringToCommandDataParserStateHandler** m_stateHandlers;
};

