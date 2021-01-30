#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

#include "../Dependencies.h"
#include "../CommandData/CommandData.h"
#include "../LabelData.h"
#include "../TranslatorCommand.h"
#include "../Functions/IFunction.h"
#include "../Listing/Listing.h"
#include "../LabelManager/LabelManager.h"

using namespace std;

class Translator {
public:
	// Устанавливает имя транслируемого файла
	static void setTranslationFileName(const string &fileName);
	// Устанавливает имя исполняемого файла
	static void setExecutableFileName(const string &fileName);
	
	// Принимает имя файла с ассембелерным кодом
	// Возвращает имя оттранслированного исполняемого файла
	static string translate();

	// Устанавливает адрес старта программы
	static void setStartAddress(const Address &startAddress);

	// Возвращает значение функции с именем name на основе переданных аргументов 
	static int countFunction(const string &name, const string &arguments);

	// Возвращает адрес регистра
	static int getRegisterAddress(const string &name);
	// Возвращает адрес регистра (безопасный метод)
	static int s_getRegisterAddress(const string &name);

	// Возвращает адрес счётчика размещения
	static int getLCount();

private:
	// Вытаскивает из имени исполняемого файла имя программы
	static void pickProgramName();

	// Перевод файла в вектор разобранных командных строк
	static vector<CommandData> parseFile(ifstream& inFile);

	// Сбор меток
	static void firstPass(vector<CommandData> &commandData);

	// Трансляция команд ассемблера в машинные коды
	static void secondPass(vector<CommandData> &commandData);

	// Записывает листинг в файл
	static void writeListing(const Listing& listing);

	// Проверяет команды на ошибки
	// Если ошибки есть, то формирует листинг и возвращает исключение
	static void checkErrors(vector<CommandData> &commandData);

	// Проверяет оттранслированные команды на предмет ошибок
	static bool hasErrors(const vector<CommandData> &commandData);

	// Проверяет имя исполняемого файла на... наличие? 
	// Его могли не передать и необходимо составить имя самим
	static void checkExecutableFileName();
	// Создаёт исполняемый файл
	static void writeExecutableFile(vector<CommandData> &commandData);

	// Список допустимых команд
	static const unordered_map<string, TranslatorCommand> m_translatorMap;
	// Допустимые функции
	static const unordered_map<string, IFunction *> m_functions;

	static Address m_startAddress;		// Адрес начала исполнения
	static int m_LCount;			// Счётчик размещения

	static string m_programName;			// Имя программы(без расширения)
	static string m_translationFileName;	// Имя транслируемого файла
	static string m_executableFileName;		// Имя исполняемого файла

	const static string EXECUTABLE_FILE_EXTENSION;
	const static string LISTING_FILE_SUFFIX;
};
