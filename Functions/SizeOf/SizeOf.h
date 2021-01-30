#pragma once
#include "../IFunction.h"
class SizeOf : public IFunction {
public:
	int operator()(const string &arguments) const;
};

