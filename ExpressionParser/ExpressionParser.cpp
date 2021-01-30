#include "ExpressionParser.h"

#include "../Parser/StringToInteger/StringToInteger/StringToInteger.h"
#include "../Errors/Errors.h"
#include "../LabelManager/LabelManager.h"
#include "../Translator/Translator.h"

int ExpressionParser::parse(const string& expression) {
	if (!expression.empty()) {
		m_expression = expression;
		m_it = m_expression.begin();
		m_sign = +1;
		int result = 0;

		m_type = getToken();
		atom(result);
		return result;
	}
	else {
		throw EmptyExpression;
	}
}

void ExpressionParser::atom(int &result) {
	if (m_type == OPER) {
		if (m_token == "-")
			m_sign = -1;
		else if (m_token == "+")
			m_sign = +1;
		m_type = getToken();
	}
	expr(result);
}
void ExpressionParser::expr(int &result) {
	char op;
	int tmp;
	term(result);
	while ((m_token == "+") || (m_token == "-")) {
		op = m_token[0];
		m_type = getToken();
		term(tmp);
		switch (op) {
			case '+': {
				result += tmp;
			} break;
			case '-': {
				result -= tmp;
			} break;
		}
	}
}
void ExpressionParser::term(int &result) {
	char op;
	int tmp;
	factor(result);
	while ((m_token == "*") || (m_token == "/") || (m_token == "%")) {
		op = m_token[0];
		m_type = getToken();
		factor(tmp);
		switch (op) {
			case '*': {
				result *= tmp;
			} break;
			case '/': {
				if (tmp) result /= tmp;
				else throw DivideByZero;
			} break;
			case '%': {
				if (tmp) result %= tmp;
				else throw DivideByZero;
			} break;
		}
	}
}
void ExpressionParser::factor(int &result) {
	if (m_token == "(") {
		m_type = getToken();
		atom(result);
		if (m_token != ")")
			throw MissingCloseBracket;
	}
	else
		value(result);
	m_type = getToken();
}
void ExpressionParser::value(int &result) {
	switch (m_type) {
		case CONST: {
			result = StringToInteger::parse(m_token);
		} break;
		case NAME: {
			result = cLabel();
		} break;
		case LCOUNT: {
			result = cLCount();
		} break;
		case FUN: {
			result = cFunction();
		} break;
		default: {	break;	}
	}
	result *= m_sign;
	m_sign = +1;
}

int ExpressionParser::cLabel() {
	return LabelManager::getLabelValue(m_token);
}
int ExpressionParser::cFunction() {
	size_t pos = m_token.find('(');
	string name = m_token.substr(0, pos);
	string param = m_token.substr(pos);
	return Translator::countFunction(name, param.substr(1, param.size() - 2));
}
int ExpressionParser::cLCount() {
	return Translator::getLCount();
}

TokenType ExpressionParser::getToken() {
	m_token = "";
	m_type = UNDEF;
	if (m_it == m_expression.end()) {
		m_type = END;
		return m_type;
	}
	if (isOperator(*m_it)) {
		m_token = *m_it;
		m_type = OPER;
		++m_it;
	}
	else if (isBracket(*m_it)) {
		m_token = *m_it;
		m_type = DELIM;
		++m_it;
	}
	else if (isdigit(*m_it)) {
		m_token = *m_it;
		++m_it;
		if (m_it != m_expression.end()) {
			if (isX(*m_it) || isB(*m_it)) {
				m_token += *m_it;
				++m_it;
			}
			while ((m_it != m_expression.end()) && !isDeilm(*m_it)) {
				m_token += *m_it;
				++m_it;
			}
		}
		m_type = CONST;
	}
	else if (*m_it == '@') {
		m_token = *m_it;
		m_type = LCOUNT;
		++m_it;
	}
	else if (isFirstId(*m_it)) {
		m_token = *m_it;
		++m_it;
		while ((m_it != m_expression.end()) && isNextId(*m_it)) {
			m_token += *m_it;
			++m_it;
		}
		if (m_it != m_expression.end()) {
			if (*m_it == '(') {
				m_token += *m_it;
				++m_it;
				while ((m_it != m_expression.end()) && (*m_it != ')')) {
					m_token += *m_it;
					++m_it;
				}
				m_token += *m_it;
				m_type = FUN;
			}
			else {
				m_type = NAME;
			}
		}
		else {
			m_type = NAME;
		}
	}
	else {
		throw UndefinedToken;
	}
	return m_type;
}

bool ExpressionParser::isBracket(char symbol) {
	return (symbol == '(' || symbol == ')');
}
bool ExpressionParser::isOperator(char symbol) {
	return (strchr("+-*/%", symbol) != nullptr);
}
bool ExpressionParser::isFirstId(char symbol) {
	return (isalpha(symbol) || symbol == '_');
}
bool ExpressionParser::isNextId(char symbol) {
	return (isalnum(symbol) || symbol == '_');
}
bool ExpressionParser::isX(char symbol) {
	return (symbol == 'x' || symbol == 'X');
}
bool ExpressionParser::isB(char symbol) {
	return (symbol == 'b' || symbol == 'B');
}
bool ExpressionParser::isDeilm(char symbol) {
	return (isBracket(symbol) || isOperator(symbol));
}
