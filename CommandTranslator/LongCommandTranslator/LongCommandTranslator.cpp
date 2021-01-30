#include "LongCommandTranslator.h"

#include "../../Translator/Translator.h"
#include "../../ExpressionParser/ExpressionParser.h"

int LongCommandTranslator::getCommandSize(const CommandData &) const {
	return LONG;
}

vector<Byte> JumpCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	MemCmd32 cmd;
	cmd.code = commandData.getCommandCode();

	Arguments arguments = commandData.getArguments();
	try {
		switch (arguments.size()) {
			case 1: {	// Однозначно адрес
				static ExpressionParser parser = ExpressionParser();
				Address address = parser.parse(arguments[0]);
				cmd.r1 = 1;		cmd.a = address;
			} break;
			case 2: {	// Регистр-память, память-регистр(что одно и то же) или регистр-регистр
				int firstRegister, secondArgumentIndex;
				// Пробуем получить регистр. Он обязан быть в одном из аргументов
				firstRegister = Translator::s_getRegisterAddress(arguments[0]);
				if (firstRegister > 0) {
					secondArgumentIndex = 1;
				}
				else {		// Первый аргумент оказался не регистром. Пробуем второй
					firstRegister = Translator::s_getRegisterAddress(arguments[1]);
					if (firstRegister > 0) {
						secondArgumentIndex = 0;
					}
					else {	// Регистра ни в одном из аргументов нет, а должен
						commandData.addError(InvalidArguments);
						break;	// Выходим из switch-а - с "инвалидными" аргументами больше делать нечего
					}
				}

				// К этому моменту регистр мы всё-таки получили
				// Пытаемся получить регистр из второго аргумента 
				int secondRegister = Translator::s_getRegisterAddress(arguments[secondArgumentIndex]);
				if (secondRegister >= 0) {
					cmd.r1 = 2;		cmd.r2 = firstRegister;		cmd.a = secondRegister;
				}
				else {	// Второй аргумент - адрес
					static ExpressionParser parser = ExpressionParser();
					int address = parser.parse(arguments[secondArgumentIndex]);
					cmd.r1 = 3;		cmd.r2 = firstRegister;		cmd.a = address;
				}
			} break;
			default: {
				if (arguments.size())	commandData.addError(TooMuchArguments);
				else					commandData.addError(NotEnoughArguments);
			} break;
		}
		appendData(result, cmd);
	}
	catch (ErrorCode err) {		// Отлавливает ошибки аргументов
		commandData.addError(err);
	}
	return result;
}

vector<Byte> RetCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	if (commandData.getArguments().size() == 0) {
		MemCmd32 cmd;	cmd.code = Ret;
		appendData(result, cmd);
	} else {
		commandData.addError(TooMuchArguments);
	}
	return result;
}

vector<Byte> CallCommandTranslator::translateCommandData(CommandData &commandData) const {
	vector<Byte> result = vector<Byte>();
	MemCmd32 cmd;
	Arguments arguments = commandData.getArguments();
	if (arguments.size() == 3) {
		cmd.code = commandData.getCommandCode();
		try {
			cmd.r1 = Translator::getRegisterAddress(arguments[0]);
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
		try {
			cmd.r2 = Translator::getRegisterAddress(arguments[0]);
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
		try {
			static ExpressionParser parser = ExpressionParser();
			cmd.a = parser.parse(arguments[2]);
		}
		catch (ErrorCode err) {
			commandData.addError(err);
		}
		appendData(result, cmd);
	}
	else {
		if (arguments.size() < 3)
			commandData.addError(NotEnoughArguments);
		else
			commandData.addError(TooMuchArguments);
	}
	return result;
}
