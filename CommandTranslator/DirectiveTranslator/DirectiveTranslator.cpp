#include "DirectiveTranslator.h"

#include <sstream>

#include "../../FloatNumberRecognizer/FloatNumberRecognizer.h"
#include "../../Parser/StringToInteger/StringToInteger/StringToInteger.h"
#include "../../ExpressionParser/ExpressionParser.h"
#include "../../LabelManager/LabelManager.h"
#include "../../Translator/Translator.h"

vector<Byte> FloatTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	Arguments arguments = commandData.getArguments();
	int size = arguments.size();

	if (size > 0) {
		appendData(result, size);
		float floatArgument = 0.0;

		for (int i = 0; i < size; i++) {
			if (FloatNumberRecognizer::isFloat(arguments[i])) {
				stringstream temp(arguments[i]);
				temp >> floatArgument;
				appendData(result, floatArgument);
			}
			else {
				commandData.addError(NotFloatArgument);
				break;
			}			
		}
	}
	else {
		commandData.addError(NotEnoughArguments);
	}
	return result;
}
int FloatTranslator::getCommandSize(const CommandData &commandData) const {
	return commandData.getArguments().size();
}

vector<Byte> IntTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	Arguments arguments = commandData.getArguments();
	int size = arguments.size();

	if (size > 0) {
		appendData(result, size);
		try {
			for (int i = 0; i < size; i++) {
				int parsed = StringToInteger::parse(arguments[i]);
				appendData(result, parsed);
			}
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
	}
	else {
		commandData.addError(NotEnoughArguments);
	}
	return result;
}
int IntTranslator::getCommandSize(const CommandData &commandData) const {
	return commandData.getArguments().size();
}


vector<Byte> EquTranslator::translateCommandData(CommandData &commandData) const {
	Arguments arguments = commandData.getArguments();
	if (arguments.size() == 1) {
		try {
			static ExpressionParser parser = ExpressionParser();
			int value = parser.parse(arguments[0]);
			LabelManager::setAbsoluteLabelValue(commandData.getLabel(), value);
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
	}
	else {
		if (arguments.size() < 1)
			commandData.addError(NotEnoughArguments);
		else
			commandData.addError(TooMuchArguments);
	}
	return vector<Byte>();
}
int EquTranslator::getCommandSize(const CommandData &) const {
	return EMPTY;
}

