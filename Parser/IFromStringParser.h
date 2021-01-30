#pragma once

#include <string>
using namespace std;

template <class T>
class IFromStringParser {
public:
	virtual T parse(const string &) const = 0;
};

