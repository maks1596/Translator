#include "MovCommandTranslator.h"

#include <sstream>

#include "../../Translator/Translator.h"
#include "../../ExpressionParser/ExpressionParser.h"
#include "../../Dependencies.h"

vector<Byte> MovCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	Arguments arguments = commandData.getArguments();
	if (arguments.size() == 2) {
		int src = Translator::s_getRegisterAddress(arguments[0]);
		int dst = Translator::s_getRegisterAddress(arguments[1]);

		// -----------------------------------------------------------------

		try {
			CommandCode code = getOperationCode(src, dst);
			if (src == -1 || dst == -1) {
				MemCmd32 cmd;	cmd.code = code;
				static ExpressionParser parser = ExpressionParser();
				if (src == -1) {
					src = parser.parse(arguments[0]);
					cmd.r2 = (HalfWord) dst; cmd.a = (Address) src;
				} else {
					dst = parser.parse(arguments[1]);
					cmd.r2 = (HalfWord) src; cmd.a = (Address) dst;
				}
				appendData(result, cmd);
			} else {
				MemCmd16 cmd;	cmd.code = code;
				cmd.r1 = (HalfWord) src; cmd.r2 = (HalfWord) dst;
				appendData(result, cmd);
			}
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
	}
	else {
		if (arguments.size() < 2) {
			commandData.addError(NotEnoughArguments);
		} else {
			commandData.addError(TooMuchArguments);
		}
	}
	return result;
}
int MovCommandTranslator::getCommandSize(const CommandData &commandData) const {
	Arguments arguments = commandData.getArguments();
	if (arguments.size() < 2) return EMPTY;	
	
	int tempSource = Translator::s_getRegisterAddress(arguments[0]);
	int tempDest = Translator::s_getRegisterAddress(arguments[1]);
	if(tempSource > 0 && tempDest > 0)	return SHORT;
	else								return LONG;
}


CommandCode MovCommandTranslator::getOperationCode(const int &src, const int &dst) const {
	if (src == -1 && dst != -1) {
		return MovMR;
	} else if (src != -1 && dst == -1) {
		return MovRM;
	} else if (src != -1 /*&& dst != -1*/) {
		return MovRR;
	} else {
		throw MovMMNotAlowed;
	}
}

