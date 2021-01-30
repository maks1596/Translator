#include "ShortCommandTranslator.h"

#include <sstream>

#include "../../LabelManager/LabelManager.h"
#include "../../Translator/Translator.h"

vector<Byte> ShortCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	Arguments arguments = commandData.getArguments();
	try {
		int first = -1, second = -1;
		try {
			first = Translator::getRegisterAddress(arguments[0]);
		} catch (ErrorCode err) {	commandData.addError(err);	}
		try {
			second = Translator::getRegisterAddress(arguments[1]);
		} catch (ErrorCode err) { commandData.addError(err); }
		if (first != -1 && second != -1) {	
			MemCmd16 cmd;
			cmd.code = commandData.getCommandCode();
			cmd.r1 = (HalfWord)second;
			cmd.r2 = (HalfWord)first;
			appendData(result, cmd);
		}
	}
	catch (ErrorCode err) {
		commandData.addError(err);
	}
	return result;
}

int ShortCommandTranslator::getCommandSize(const CommandData &) const {
	return SHORT;
}

vector<Byte> IOCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	Arguments arguments = commandData.getArguments();
	try {
		if (arguments.size() == 1) {
			int r = Translator::getRegisterAddress(arguments[0]);
			MemCmd16 cmd;
			cmd.code = commandData.getCommandCode();
			cmd.r1 = (HalfWord) r;
			appendData(result, cmd);
		}
		else {
			if (arguments.size() < 1)	throw NotEnoughArguments;
			else						throw TooMuchArguments;
		}
	}
	catch (ErrorCode err) {
		commandData.addError(err);
	}
	return result;
}

vector<Byte> EndCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	Arguments arguments = commandData.getArguments();
	if (arguments.size() == 1) {
		try {
			Translator::setStartAddress((Address)LabelManager::getLabelValue(arguments[0]));
			MemCmd16 cmd;
			cmd.code = commandData.getCommandCode();
			appendData(result, cmd);
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
	}
	else if (arguments.size() < 1) {
		commandData.addError(NotEnoughArguments);
	} else {
		commandData.addError(TooMuchArguments);
	}
	return result;
}
