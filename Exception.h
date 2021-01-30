#pragma once

#include <exception>
#include <string>

using namespace std;

class NotEnoughCommandLineParameters : public exception {
public:
	virtual const char * what() const noexcept {
		return "Недостаточно параметров командной строки";
	}
};

class TranslatorNotEnoughArguments : public exception {
public:
	virtual const char * what() const noexcept {
		return "Недостаточно аргументов";
	}
};

class TranslatorFileNotFound : public exception {
public:
	virtual const char * what() const noexcept {
		return "Файл не найден";
	}
};

class TranslationError : public exception {
public:
	virtual const char * what() const noexcept {
		return "Ошибка трансляции";
	}
};

