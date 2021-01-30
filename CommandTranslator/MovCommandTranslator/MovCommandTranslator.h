#pragma once
#include "../CommandTranslator.h"
#include "../../Dependencies.h"

class MovCommandTranslator : public CommandTranslator {
public:
	vector<Byte> translateCommandData(CommandData &commandData) const;
	int getCommandSize(const CommandData &commandData) const;

private:
	CommandCode getOperationCode(const int &src, const int &dst) const;
};
