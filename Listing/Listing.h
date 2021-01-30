#pragma once

#include "../CommandData/CommandData.h"

class Listing
{
public:
	Listing(const vector<CommandData> &commandData);

	string toString() const;
	friend ostream& operator<<(ostream& os, const Listing &listing);

private:
	// Считает отступы для табулированного вывода
	void countMaxLengths();
	// Считает отступ для адресов
	unsigned countAddressOffset();
	// Считает отступ для счётчика строк
	unsigned countCounterOffset();

	vector<CommandData> m_CommandData;
	bool m_hasErrors = false;

	unsigned m_addressOffset = 0;
	unsigned m_counterOffset = 0;

	size_t m_maxMachineCodeLength = 0;
	size_t m_maxLabelLength = 0;
	size_t m_maxCommandLength = 0;
	size_t m_maxArgumentsLength = 0;
};

