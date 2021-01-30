#pragma once

#include "../CommandTranslator.h"

class ShortCommandTranslator : public CommandTranslator {
public:
	vector<Byte> translateCommandData(CommandData &commandData) const;
	int getCommandSize(const CommandData &commandData) const;
};

class IOCommandTranslator : public ShortCommandTranslator {
public:
	vector<Byte> translateCommandData(CommandData &commandData) const;
};

class EndCommandTranslator : public ShortCommandTranslator {
public:
	vector<Byte> translateCommandData(CommandData &commandData) const;
};
