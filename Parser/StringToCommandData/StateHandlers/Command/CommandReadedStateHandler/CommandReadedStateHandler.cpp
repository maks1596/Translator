#include "CommandReadedStateHandler.h"

StringToCommandDataState CommandReadedStateHandler::handle(CommandData &command, unsigned &curPos, string &inString) const {
	command.setCommand(inString.substr(0, curPos));
	inString.erase(inString.begin(), inString.begin() + curPos);
	curPos = 0;
	return READ_ARGUMENTS;
}
