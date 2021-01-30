#include "StringToCommandData.h"

#include "../StateHandlers/FirstWord/BeginReadFirstWordStateHandler/BeginReadFirstWordStateHandler.h"
#include "../StateHandlers/FirstWord/ReadFirstWordStateHandler/ReadFirstWordStateHandler.h"
#include "../StateHandlers/FirstWord/LabelReadedStateHandler/LabelReadedStateHandler.h"

#include "../StateHandlers/Command/BeginReadCommandStateHandler/BeginReadCommandStateHandler.h"
#include "../StateHandlers/Command/ReadCommandStateHandler/ReadCommandStateHandler.h"
#include "../StateHandlers/Command/CommandReadedStateHandler/CommandReadedStateHandler.h"

#include "../StateHandlers/Arguments/ReadArgumentsStateHandler/ReadArgumentsStateHandler.h"
#include "../StateHandlers/Arguments/ArgumentsReadedStateHandler/ArgumentsReadedStateHandler.h"

#include "../StateHandlers/ReadCommentStateHandler/ReadCommentStateHandler.h"

StringToCommandData::StringToCommandData() {
	m_stateHandlers = new IStringToCommandDataParserStateHandler*[STOP_STRING_TO_COMMAND_DATA_PARSE];

	m_stateHandlers[BEGIN_READ_FIRST_WORD] = new BeginReadFirstWordStateHandler();
	m_stateHandlers[READ_FIRST_WORD] = new ReadFirstWordStateHandler();
	m_stateHandlers[LABEL_READED] = new LabelReadedStateHandler();

	m_stateHandlers[BEGIN_READ_COMMAND] = new BeginReadCommandStateHandler();
	m_stateHandlers[READ_COMMAND] = new ReadCommandStateHandler();
	m_stateHandlers[COMMAND_READED] = new CommandReadedStateHandler();

	m_stateHandlers[READ_ARGUMENTS] = new ReadArgumentsStateHandler();
	m_stateHandlers[ARGUMENTS_READED] = new ArgumentsReadedStateHandler();

	m_stateHandlers[READ_COMMENT] = new ReadCommentStateHandler();
}

StringToCommandData::~StringToCommandData() {
	delete[] m_stateHandlers;
}

CommandData StringToCommandData::parse(const string &inString) const {
	string copy = inString;
	StringToCommandDataState currentState = BEGIN_READ_FIRST_WORD;
	CommandData result = CommandData();
	unsigned currentPosition = 0;
	while (currentState != STOP_STRING_TO_COMMAND_DATA_PARSE) {
		currentState = m_stateHandlers[currentState]->handle(result, currentPosition, copy);
	}
	return result;
}
