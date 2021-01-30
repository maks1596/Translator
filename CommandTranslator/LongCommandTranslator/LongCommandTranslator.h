#pragma once
#include "../CommandTranslator.h"

class LongCommandTranslator : public CommandTranslator {
public:
	virtual vector<Byte> translateCommandData(CommandData &commandData) const = 0;
	int getCommandSize(const CommandData &commandData) const;
};

class JumpCommandTranslator : public LongCommandTranslator {
	vector<Byte> translateCommandData(CommandData &commandData) const;
};

class RetCommandTranslator : public LongCommandTranslator {
public:
	vector<Byte> translateCommandData(CommandData &commandData) const;
};

class CallCommandTranslator : public LongCommandTranslator {
public:
	vector<Byte> translateCommandData(CommandData &commandData) const;
};

