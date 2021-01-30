#pragma once

#include <string>
using namespace std;

enum TokenType {
	UNDEF, NAME, LCOUNT, CONST,
	FUN, OPER, DELIM, END
};

class ExpressionParser {
public:
	int parse(const string& expression);

private:
	typedef string::const_iterator StringIterator;
	StringIterator m_it;
	string m_expression;
	TokenType m_type;
	string m_token;
	int m_sign;

	TokenType getToken();
	bool isBracket(char symbol);
	bool isOperator(char symbol);
	bool isFirstId(char symbol);
	bool isNextId(char symbol);
	bool isX(char symbol);
	bool isB(char symbol);
	bool isDeilm(char symbol);

	void atom(int &result);
	void expr(int &result);
	void term(int &result);
	void factor(int &result);
	void value(int &result);

	int cLabel();
	int cFunction();
	int cLCount();
};

