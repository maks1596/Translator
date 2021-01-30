#include "CommandData.h"

#include <sstream>

const string CommandData::IDENTIFIER_REGEX = "[_[:alpha:]][_[:alnum:]]*";
const StringToArguments CommandData::m_argumentsParser = StringToArguments();

void CommandData::setLabel(const string &label) {
	m_label = label;
	if (!regex_match(m_label, regex(IDENTIFIER_REGEX)))
		m_errorCodes.push_back(IllegalLabelName);
}
string CommandData::getLabel() const {
	return m_label;
}

void CommandData::setCommand(const string &command) {
	m_command = command;
	if (!regex_match(command, regex(IDENTIFIER_REGEX)))
		m_errorCodes.push_back(IllegalCommandName);
}
string CommandData::getCommand() const {
	return m_command;
}

void CommandData::setArguments(const string &arguments) {
	m_arguments = m_argumentsParser.parse(arguments);
}
vector<string> CommandData::getArguments() const {
	return m_arguments;
}

void CommandData::setComment(const string &comment) {
	m_comment = comment;
}
string CommandData::getComment() const {
	return m_comment;
}

void CommandData::setCommandCode(const CommandCode &commandCode) {
	m_commandCode = commandCode;
}
CommandCode CommandData::getCommandCode() const {
	return m_commandCode;
}

void CommandData::setMachineCode(const vector<Byte> &machineCode) {
	m_machineCode = machineCode;
}
vector<Byte> CommandData::getMachineCode() const {
	return m_machineCode;
}

void CommandData::setAddress(const unsigned &address) {
	m_address = address;
}
unsigned CommandData::getAddress() const {
	return m_address;
}

void CommandData::addError(const ErrorCode &errorCode) {
	m_errorCodes.push_back(errorCode);
}

bool CommandData::hasErrors() const {
	return m_errorCodes.size() > 0;
}

string CommandData::argumentsToString() const {
	stringstream ss;
	if (!m_arguments.empty()) {
		ss << m_arguments[0];
		unsigned size = m_arguments.size();
		for (unsigned i = 1; i < size; i++)
			ss << (char)COMMA << (char)SPACE << m_arguments[i];
	}
	return ss.str();
}

string CommandData::errorsToString() const {
	stringstream ss;
	if (!m_errorCodes.empty()) {
		ss << endl << "!! ----- Ошибка ----- !!" << endl;
		for (auto errorCode : m_errorCodes)
			ss << Errors.at(errorCode) << endl;
		ss << "!! ------------------ !!";
	}
	return ss.str();
}

string CommandData::toString() const {
	stringstream ss;
	ss << "address: " << m_address << endl;
	ss << "machine code: " << machineCodeToString() << endl;
	ss << "label: " << m_label << endl;
	ss << "command: " << m_command << " | code: " << m_commandCode << endl;
	ss << "arguments: " << argumentsToString() << endl;
	ss << "comment: " << m_comment << endl;
	ss << "errors: " << errorsToString() << endl;
	return ss.str();
}

string CommandData::machineCodeToString() const {
	if (m_machineCode.empty()) {
		return string();
	}

	Word data;
	stringstream ss;
	if (m_command == "float" || m_command == "int") {
		if (m_command == "float") {
			ss << 'f';
			size_t i = 0;
			while (i < sizeof(int)) {
				data.bytes[i] = m_machineCode[i];
				i++;
			}
			int size = data.i;
			ss << " " << size;

			while (i < m_machineCode.size()) {
				for (size_t j = 0; j < sizeof(float); j++) {
					data.bytes[i + j] = m_machineCode[i + j];
				}
				ss << " " << data.f;
				i += sizeof(float);
			}
		} else {
			ss << 'i';
			size_t i = 0;
			while (i < sizeof(int)) {
				data.bytes[i] = m_machineCode[i];
				i++;
			}
			int size = data.i;
			ss << " " << size;

			while (i < m_machineCode.size()) {
				for (size_t j = 0; j < sizeof(int); j++) {
					data.bytes[j] = m_machineCode[i + j];
				}
				ss << " " << data.i;
				i += sizeof(int);
			}
		}
	} else {
		ss << 'k';
		size_t size = m_machineCode.size();
		for (size_t i = 0; i < size; i++) {
			data.bytes[i] = m_machineCode[i];
		}
		ss << " " << data.mc.code << " " << data.mc.fcmd16.r1 << " " << data.mc.fcmd16.r2;
		if (size > sizeof(MemCmd16)) {
			ss << " " << data.mc.cmd32.a;
		}
	}
	return ss.str();
}

ostream& operator<<(ostream & os, const CommandData &commandData) {
	return os << commandData.toString();
}
