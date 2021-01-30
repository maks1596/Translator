#pragma once

#include <string>
using namespace std;

class IFunction {
public:
	virtual int operator()(const string &arguments) const = 0;
};
