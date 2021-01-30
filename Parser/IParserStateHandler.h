#pragma once

#include <ctype.h>
#include <string>

#include "../Errors/Errors.h"
#include "SpecialSymbols.h"

using namespace std;

template <typename State, class T>
class IParserStateHandler {
public:
	virtual State handle(T &, unsigned &curPos, string &inString) const = 0;
};

