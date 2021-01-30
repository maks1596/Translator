#pragma once

#include <vector>
using namespace std;

#include "../Dependencies.h"
#include "../CommandData/CommandData.h"

enum CommandSize {
	EMPTY = 0,
	SHORT = -1,
	LONG = 1,
};

class CommandTranslator {
public:

	virtual vector<Byte> translateCommandData(CommandData &commandData) const = 0;
	
	virtual int getCommandSize(const CommandData &commandData) const = 0;

protected:
    inline
    void appendData(vector<Byte> &dst, const MemCmd32 &cmd) const {
        appendData(dst, Word(cmd));
    }

	inline
	void appendData(vector<Byte> &dst, const MemCmd16 &cmd) const {
		appendData(dst, Word(cmd), sizeof(cmd));
	}

	void appendData(vector<Byte> &dst, const Word &w,
					const size_t size = sizeof(Word)) const {
		for (size_t i = 0; i < size; i++) {
			dst.push_back(w.bytes[i]);
		}
	}
};
