#include "Listing.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

Listing::Listing(const vector<CommandData> &commandData) {
	m_CommandData = commandData;
	countMaxLengths();
	m_counterOffset = countCounterOffset();
	m_addressOffset = countAddressOffset();
}

void Listing::countMaxLengths() {
	for (CommandData currentCommand : m_CommandData) {
		m_maxMachineCodeLength = max(m_maxMachineCodeLength, currentCommand.machineCodeToString().size());
		m_maxLabelLength = max(m_maxLabelLength, currentCommand.getLabel().size());
		m_maxCommandLength = max(m_maxCommandLength, currentCommand.getCommand().size());
		m_maxArgumentsLength = max(m_maxArgumentsLength, currentCommand.argumentsToString().size());

		// Не очень красиво, зато повышает быстродейтсвие
		m_hasErrors |= currentCommand.hasErrors();		// Определяется будет ли выводиться машинный код
	}
}

unsigned Listing::countAddressOffset() {
	unsigned address = m_CommandData[m_CommandData.size() - 1].getAddress();
	unsigned offset = 1;
	while (address /= 10) offset++;
	return offset;
}

unsigned Listing::countCounterOffset() {
	unsigned size = m_CommandData.size();
	unsigned offset = 1;
	while (size /= 10) offset++;
	return offset;
}

string Listing::toString() const {
	stringstream ss;
	unsigned counter = 1;

	for (CommandData currentCommand : m_CommandData) {
		if (!m_hasErrors) {		// Адрес и машинный код выводятся только, если не было ошибок
			ss << setw(m_addressOffset) << right << currentCommand.getAddress() << ": ";
			ss << setw(m_maxMachineCodeLength) << left << currentCommand.machineCodeToString() << " | ";
		}

		ss << setw(m_counterOffset) << right << counter++ << " | ";
		ss << setw(m_maxLabelLength) << right << currentCommand.getLabel();
		if(!currentCommand.getLabel().empty())
			ss << (char)COLON;
		else
			ss << (char)SPACE;	// Пробел нужен, иначе будет не красиво!
		ss << (char)SPACE;

		ss << setw(m_maxCommandLength + 1 + m_maxArgumentsLength) << left 
			<< currentCommand.getCommand() + (char)SPACE + currentCommand.argumentsToString() << (char)SPACE;

		if(!currentCommand.getComment().empty())
			ss << (char)SEMICOLON << currentCommand.getComment();
		ss << currentCommand.errorsToString();
		ss << endl;
	}
	return ss.str();
}

ostream& operator<<(ostream& os, const Listing &listing) {
	return os << listing.toString();
}
