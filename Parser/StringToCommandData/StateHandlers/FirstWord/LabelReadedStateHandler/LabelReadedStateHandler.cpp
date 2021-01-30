#include "LabelReadedStateHandler.h"

StringToCommandDataState LabelReadedStateHandler::handle(CommandData &command, unsigned &curPos, string &inString) const {
	command.setLabel(inString.substr(0, curPos));
													// curPos + 1 , чтобы удалить ":" после метки
	inString.erase(inString.begin(), inString.begin() + curPos + 1);
	curPos = 0;
	return BEGIN_READ_COMMAND;
}
