#include "Translator.h"

#include <string>
#include <fstream>
#include <map>
#include <sstream>

#include "../Exception.h"
#include "../Parser/StringToCommandData/StringToCommandData/StringToCommandData.h"
#include "../Listing/Listing.h"

#include "../CommandTranslator/ShortCommandTranslator/ShortCommandTranslator.h"
#include "../CommandTranslator/LongCommandTranslator/LongCommandTranslator.h"
#include "../CommandTranslator/DirectiveTranslator/DirectiveTranslator.h"
#include "../CommandTranslator/MovCommandTranslator/MovCommandTranslator.h"

#include "../Functions/SizeOf/SizeOf.h"

using namespace std;

int Translator::m_LCount = 0;
Address Translator::m_startAddress = 0;
string Translator::m_programName = "";
string Translator::m_translationFileName = "";
string Translator::m_executableFileName = "";

const string Translator::EXECUTABLE_FILE_EXTENSION = ".vmexec";
const string Translator::LISTING_FILE_SUFFIX = " listing.lst";

const unordered_map<string, IFunction *> Translator::m_functions {
	make_pair("sizeof", new SizeOf())
};

const unordered_map<string, TranslatorCommand> Translator::m_translatorMap {
	// Директивы
	make_pair( "equ", TranslatorCommand(Nop, new EquTranslator()) ),
	make_pair( "int", TranslatorCommand(Nop, new IntTranslator()) ),
	make_pair( "float", TranslatorCommand(Nop, new FloatTranslator()) ),

	make_pair( "end", TranslatorCommand(Stop, new EndCommandTranslator()) ),

	// Целочисленная арифметика
	make_pair( "add", TranslatorCommand(AddI, new ShortCommandTranslator()) ), 		// Сложение
	make_pair( "sub", TranslatorCommand(SubI, new ShortCommandTranslator()) ), 		// Вычитание
	make_pair( "mul", TranslatorCommand(MulI, new ShortCommandTranslator()) ),	 	// Умножение
	make_pair( "div", TranslatorCommand(DivI, new ShortCommandTranslator()) ), 		// Деление
	make_pair( "mod", TranslatorCommand(ModI, new ShortCommandTranslator()) ), 		// Остаток от деления

	// Целая беззнаковая арифметика	
	make_pair( "umul", TranslatorCommand(MulUI, new ShortCommandTranslator()) ), 	// Умножение беззнаковых
	make_pair( "udiv", TranslatorCommand(DivUI, new ShortCommandTranslator()) ), 	// Деление беззнаковых
	make_pair( "umod", TranslatorCommand(ModUI, new ShortCommandTranslator()) ),	// Остаток от деления беззнаковых

	// Дробная арифметика
	make_pair( "fadd", TranslatorCommand(AddF, new ShortCommandTranslator()) ), 	// Сложение
	make_pair( "fsub", TranslatorCommand(SubF, new ShortCommandTranslator()) ), 	// Вычитание
	make_pair( "fmul", TranslatorCommand(MulF, new ShortCommandTranslator()) ), 	// Умножение
	make_pair( "fdiv", TranslatorCommand(DivF, new ShortCommandTranslator()) ), 	// Деление

	// Перессылки
	make_pair( "mov", TranslatorCommand(Nop, new MovCommandTranslator()) ), 		// Пересылка целых

	// Сравнения
	make_pair( "cmp", TranslatorCommand(CmpI, new ShortCommandTranslator()) ), 		// Сравнение целых
	make_pair( "ucmp", TranslatorCommand(CmpUI, new ShortCommandTranslator()) ), 	// Сравнение беззнаковых целых
	make_pair( "fcmp", TranslatorCommand(CmpF, new ShortCommandTranslator()) ), 	// Сравнение дробных

	// Ввод вывод
	make_pair( "in", TranslatorCommand(InI, new IOCommandTranslator()) ), 			// Ввод целых
	make_pair( "out", TranslatorCommand(OutI, new IOCommandTranslator()) ), 		// Вывод целых
	make_pair( "fin", TranslatorCommand(InF, new IOCommandTranslator()) ), 			// Ввод дробных
	make_pair( "fout", TranslatorCommand(OutF, new IOCommandTranslator()) ), 		// Вывод дробных

	// Переходы
	make_pair( "jmp", TranslatorCommand(Jmp, new JumpCommandTranslator()) ), 		// Переход к адресу
	make_pair( "je", TranslatorCommand(Je, new JumpCommandTranslator()) ), 			// Переход, если равно
	make_pair( "jl", TranslatorCommand(Jl, new JumpCommandTranslator()) ), 			// Переход, если меньше
	make_pair( "jg", TranslatorCommand(Jg, new JumpCommandTranslator()) ), 			// Переход, если больше
	make_pair( "call", TranslatorCommand(Call, new CallCommandTranslator()) ), 		// Вызов подпрограммы
	make_pair( "ret", TranslatorCommand(Ret, new RetCommandTranslator()) ) 			// Возвращение из подпрограммы
};

void Translator::setTranslationFileName(const string &fileName) {
	m_translationFileName = fileName;
	pickProgramName();
}

void Translator::pickProgramName() {
	m_programName = m_translationFileName;
	size_t dotPosition = m_programName.rfind('.');
	if (dotPosition > 0) {
		m_programName.erase(dotPosition);
	}
}

void Translator::setExecutableFileName(const string &fileName) {
	m_executableFileName = fileName;
}

vector<CommandData> Translator::parseFile(ifstream& inFile) {
	string currentLine;
	vector<CommandData> result;
	StringToCommandData parser = StringToCommandData();
	while (!inFile.eof()) {
		getline(inFile, currentLine);
		result.push_back(parser.parse(currentLine));
	}
	return result;
}

void Translator::writeListing(const Listing& listing) {
	ofstream listingFile(m_programName + LISTING_FILE_SUFFIX);
	listingFile << listing;
	listingFile.close();
}

void Translator::firstPass(vector<CommandData> &commandData) {
	bool isPreviousWordFull = true;
	unsigned writeAddress = 0;

	for (unsigned i = 0; i < commandData.size(); ++i) {
		string command = commandData[i].getCommand();
		int currentCommandSize = EMPTY;

		auto it = m_translatorMap.find(command);
		if (it != m_translatorMap.end()) {
			currentCommandSize = it->second.commandTranslator->getCommandSize(commandData[i]);
			commandData[i].setCommandCode(it->second.commandCode);
		}

		unsigned shiftAddress = 0;
		// Если текущая команда короткая и на неё не указывает метка
		if (currentCommandSize == SHORT && commandData[i].getLabel().empty()) {
			if (!isPreviousWordFull) {	// Если предыдущая команда не полная
				shiftAddress = 1;
			}
			isPreviousWordFull = !isPreviousWordFull;
		}
		else {
			if (!isPreviousWordFull) {
				writeAddress++;
				isPreviousWordFull = true;
			}
			if (currentCommandSize == SHORT) {
				if (!isPreviousWordFull) {
					shiftAddress = 1;
				} else {
					shiftAddress = 0;
				}
			} else {
				shiftAddress = currentCommandSize;
			}
		}

		if (!commandData[i].getLabel().empty()) {
			try {
				LabelManager::addLabel(commandData[i].getLabel(),
									   LabelData(writeAddress, command != "equ"));
			}
			catch (const ErrorCode &error) {
				commandData[i].addError(error);
			}
		}
		commandData[i].setAddress(writeAddress);
		writeAddress += shiftAddress;
	}
}

void Translator::secondPass(vector<CommandData> &commandData) {
	unsigned size = commandData.size();
	bool endCommandReaded = false;
	unsigned i = 0;
	while (i < size && !endCommandReaded) {
		if (!commandData[i].getCommand().empty()) {
			m_LCount = commandData[i].getAddress();
			vector<Byte> machineCode;
			auto iter = m_translatorMap.find(commandData[i].getCommand());
			if (iter != m_translatorMap.end()) {
				machineCode = iter->second.commandTranslator->translateCommandData(commandData[i]);
			} else {
				commandData[i].addError(UnknownCommand);
			}
			commandData[i].setMachineCode(machineCode);

			if (commandData[i].getCommand() == "end") 
				endCommandReaded = true;
		}
		i++;
	}

	if (!endCommandReaded) {
		commandData[size - 1].addError(HaveNoEndCommand);
	}
}

void Translator::checkErrors(vector<CommandData> &commandData) {
	if (hasErrors(commandData)) {
		Listing listing = Listing(commandData);
		writeListing(listing);
		cout << listing << endl;
		throw TranslationError();
	}
}

bool Translator::hasErrors(const vector<CommandData> &commandData) {
	for (const CommandData &command : commandData) {
		if (command.hasErrors()) {
			return true;
		}
	}
	return false;
}

void Translator::checkExecutableFileName() {
	if (m_executableFileName.empty()) {
		m_executableFileName = m_programName + EXECUTABLE_FILE_EXTENSION;
	}
}

void Translator::writeExecutableFile(vector<CommandData> &commandData) {
	checkExecutableFileName();
	ofstream executableFile(m_executableFileName, ios::trunc | ios::binary);
	size_t size = commandData.size();
	Address prevAddress = -1, curAddress = 0;
	for (size_t i = 0; i < size; i++) {
		if (!commandData[i].getMachineCode().empty()) {
			curAddress = commandData[i].getAddress();
			
			// Записываем префиксы команд, если они нужны
			if (commandData[i].getCommand() == "float") {
				executableFile << 'f';
			} else if (commandData[i].getCommand() == "int") {
				executableFile << 'i';
			} else if (prevAddress != curAddress) {
				executableFile << 'k';
			}

			for (Byte byte : commandData[i].getMachineCode()) {
				executableFile.write((char *)&byte, sizeof(byte));
			}
			if (commandData[i].getMachineCode().size() == sizeof(MemCmd16)) {
				if (prevAddress != curAddress) {
					if ((i + 1) == size || commandData[i + 1].getAddress() != curAddress) {
						executableFile << (char)0 << (char)0;
					}
				}
			}
			prevAddress = curAddress;
		}
	}

	// Дописываем адрес начала исполнения
	char prefix = 's';
	executableFile.write((char *)&prefix, sizeof(prefix));
	executableFile.write((char *)&m_startAddress, sizeof(m_startAddress));

	executableFile.close();
}

string Translator::translate() {
	ifstream inFile(m_translationFileName);
	if (!inFile.is_open()) 	{
		throw TranslatorFileNotFound();
	}
	vector<CommandData> parsedData = parseFile(inFile);
	inFile.close();

	firstPass(parsedData);
	checkErrors(parsedData);
	secondPass(parsedData);
	checkErrors(parsedData);

	writeExecutableFile(parsedData);
	writeListing(Listing(parsedData));
	return m_executableFileName;
}

void Translator::setStartAddress(const Address &startAddress) {
	m_startAddress = startAddress;
}

int Translator::countFunction(const string &name, const string &arguments) {
	auto iter = m_functions.find(name);
	if (iter != m_functions.end()) {
		return (*iter->second)(arguments);
	}
	else {
		throw IllegalFunction;
	}	
}

int Translator::getRegisterAddress(const string &name) {
	int result = s_getRegisterAddress(name);
	if (result < 0)	throw UndefinedRegister;		
	else			return result;
}

// Отталкиваться будем от того, что имена регистров r0, ... , r31 
int Translator::s_getRegisterAddress(const string &name) {
	int result = -1;
	if (name[0] == 'r') {
		string number = string(name.begin() + 1, name.end());
		try {
			int temp = stoi(number);
			if (0 <= temp && temp < 32)
				result = temp;
		} catch (const exception &ex) {
			cout << ex.what() << endl;
		}
	} 
	return result;
}

int Translator::getLCount() {
	return m_LCount;
}
 
