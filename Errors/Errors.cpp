#include "Errors.h"

const map<ErrorCode, string> Errors = {
	make_pair(IllegalLabelName, "Недопустимое имя метки"),
	make_pair(IllegalCommandName, "Недопустимое имя команды"),
	make_pair(InvalidIntegerFormat, "Некорректный форматцелого числа"),
	make_pair(EmptyExpression, "Пустое выражение"),
	make_pair(UndefinedToken, "Неизвестная лексема"),
	make_pair(DivideByZero, "Деление на ноль"),
	make_pair(MissingCloseBracket, "Не хватает закрывающей скобки"),
	make_pair(IllegalFunction, "Неизвестная функция"),
	make_pair(IllegalFunctionArguments, "Недопустимые аргументы для функции"),
	make_pair(LabelRedefinition, "Переопределение метки"),
	make_pair(UndefinedLabel, "Неопределённая метка"),
	make_pair(UndefinedAbsoluteLabel, "Неопределённая абсолютная метка"),
	make_pair(UndefinedRegister, "Неизвестное имя регистра"),
	make_pair(NotEnoughArguments, "Недостаточно аргументов"),
	make_pair(TooMuchArguments, "Слишком много аргументов"),
	make_pair(NotFloatArgument, "Аргумент не является дробным числом"),
	make_pair(MovMMNotAlowed, "Пересылка память-память не разрешена"),
	make_pair(UnknownCommand, "Неизвестная команда"),
	make_pair(InvalidArguments, "Недопустимые аргументы"),
	make_pair(HaveNoEndCommand, "Команда \"end\" не найдена")
};

