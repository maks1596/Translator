#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned short Address;		// Адрес памяти
typedef unsigned char Byte;			// Байт
typedef unsigned short HalfWord;	// Полслова

// Короткая команда. Занимает полслова - 16 бит
struct MemCmd16 {
	HalfWord code : 6;
	HalfWord r1 : 5;
	HalfWord r2 : 5;
};

// Длинная команда. Занимает целое слово - 32 бита
struct MemCmd32 : public MemCmd16 {
	Address a;
};

union MemCmd {
	HalfWord code : 6;
	
	struct {
		MemCmd16 fcmd16;
		MemCmd16 scmd16;
	};
	MemCmd32 cmd32;
};

// Слово - 32 бита
union Word {
	unsigned u;
	int i;
	float f;
	MemCmd mc;
	Byte bytes[4];
	
	Word() : i() {}
	Word(const int &i) : i(i) {}
	Word(const float &f) : f(f) {}
	Word(const MemCmd16 &first,
		 const MemCmd16 &second = MemCmd16()) {
		mc.fcmd16 = first;
		mc.scmd16 = second;
	}
    Word(const MemCmd32 &cmd) {
        mc.cmd32 = cmd;
    }
};

enum CommandCode : Byte	// Коды операций
{
	Nop,		// Нет операции
	Stop,		// Стоп

	// Целая арифметика
	AddI,		// Сложение
	SubI,		// Вычитание
	MulI,		// Умножение
	MulUI,		// Умножение беззнаковых
	DivI,		// Деление
	DivUI,		// Деление беззнаковых
	ModI,		// Остаток от деления
	ModUI,		// Остаток от деления беззнаковых

	// Дробная арифметика
	AddF,		// Сложение
	SubF,		// Вычитание
	MulF,		// Умножение
	DivF,		// Деление

	// Пересылки
	MovRR,		// Пересылка регистр-регистр
	MovRM,		// Пересылка регистр-память
	MovMR,		// Пересылка память-регистр

	// Сравнения
	CmpI,		// Сравнение целых
	CmpUI,		// Сравнение беззнаковых целых
	CmpF,		// Сравнение дробных

	// Ввод вывод
	InI,		// Ввод целых
	OutI,		// Вывод целых
	InF,		// Ввод дробных
	OutF,		// Вывод дробных

	// Переходы
	Jmp,		// Переход к адресу
	Je,			// Переход, если равно
	Jl,			// Переход, если меньше
	Jg,			// Переход, если больше
	Call,		// Вызов подпрограммы
	Ret			// Возвращение из подпрограммы
};
