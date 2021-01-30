#pragma once

#include <string>
using namespace std;

enum State { start, s1, s2, s3, s4, s5, s6, s7, fin, err, statesCount = fin };
enum SymbolType { Digit, Point, Exp, Sign, Other, ClassCount };

class FloatNumberRecognizer
{
public:
	static bool isFloat(const string &inString);

private:
	static SymbolType type(char ch);
};

