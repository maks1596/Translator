#include "ReadCommentStateHandler.h"

StringToCommandDataState ReadCommentStateHandler::handle(CommandData &command, unsigned &, string &inString) const {
													// + 1 , потому что ';' перед комментарием
	inString.erase(inString.begin(), inString.begin() + 1);
	command.setComment(inString);
	return STOP_STRING_TO_COMMAND_DATA_PARSE;
}
