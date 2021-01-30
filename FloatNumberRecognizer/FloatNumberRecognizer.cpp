#include "FloatNumberRecognizer.h"

SymbolType FloatNumberRecognizer::type(char ch) {
	switch (ch) {
	case '.': return Point;
	case 'e':
	case 'E': return Exp;
	case '-':
	case '+': return Sign;
	default:
		if (isdigit(ch)) return Digit;
		else return Other;
	}
}

bool FloatNumberRecognizer::isFloat(const string &inString) {
	static State matrix[ClassCount][statesCount] = 
	{
		{s2, s2, s2, s4, s4, s7, s7, s7},
		{err, err, s3, err, err, err, err, err},
		{err, err, s5, err, s5, err, err, err},
		{s1, err, err, err, err, s6, err, err},
		{err, err, fin, err, fin, err, err, fin}
	};
	unsigned n = 0, size = inString.size();
	State s = start;
	while (n < size && s != fin) {
		SymbolType t = type(inString[n++]);
		s = matrix[t][s];
		if (s == err) return false;
	}
	return true;
}
