#pragma once
#include "../CommandTranslator.h"

class DirectiveTranslator :	public CommandTranslator {
public:
	virtual vector<Byte> translateCommandData(CommandData &commandData) const = 0;
	virtual int getCommandSize(const CommandData &commandData) const = 0;
};

class FloatTranslator : public DirectiveTranslator {
	vector<Byte> translateCommandData(CommandData &commandData) const;
	int getCommandSize(const CommandData &commandData) const;
};

class IntTranslator : public DirectiveTranslator {
	vector<Byte> translateCommandData(CommandData &commandData) const;
	int getCommandSize(const CommandData &commandData) const;
};

class EquTranslator : public DirectiveTranslator {
	vector<Byte> translateCommandData(CommandData &commandData) const;
	int getCommandSize(const CommandData &commandData) const;
};
