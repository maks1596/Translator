#pragma once

#include "CommandTranslator/CommandTranslator.h"
#include "Dependencies.h"

struct TranslatorCommand {
	CommandCode commandCode;
	CommandTranslator * commandTranslator;

	TranslatorCommand(const CommandCode &initCommandCode,
		CommandTranslator * initCommandTranslator) {
		commandCode = initCommandCode;
		commandTranslator = initCommandTranslator;
	}
};
