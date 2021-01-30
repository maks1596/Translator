#include "SizeOf.h"

#include "../../Errors/Errors.h"
#include "../../Dependencies.h"

int SizeOf::operator()(const string &arguments) const {
	if (arguments == "byte") return sizeof(Byte);
	else if (arguments == "word") return sizeof(Word);
	else if (arguments == "float") return sizeof(float);
	else if (arguments == "int") return sizeof(int);
	else throw IllegalFunctionArguments;
}
