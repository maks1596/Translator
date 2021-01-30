#pragma once

#include <string>
#include <unordered_map>

#include "../LabelData.h"

using namespace std;

class LabelManager {
public:
	// Проверяет существование метки
	static bool isLabelExist(const string &name);

	// Добавляет новую метку
	static void addLabel(const string &name, const LabelData &data);

	// Добавляет значение абсолютной метки
	static void setAbsoluteLabelValue(const string &name, const int &value);

	// Возвращает данные метки по её имени
	static LabelData getLabelData(const string &name);

	// Возвращает значение метки
	static int getLabelValue(const string &name);

private:
	// "Собранные" метки
	static unordered_map<string, LabelData> m_labels;
};

