#include <iostream>

#include "Translator/Translator.h"
#include "Exception.h"

void configureTranslator(int argc, char* argv[]) {
	// В первом аргументе ожидается получить имя транслируемого файла
	if (argc < 2) {
		throw NotEnoughCommandLineParameters();	
	}
	Translator::setTranslationFileName(argv[1]);
	if(argc > 2) {
		Translator::setExecutableFileName(argv[2]);
	}
	
}

int main(int argc, char* argv[])
{
	setlocale(0, "rus");
	try {
		configureTranslator(argc, argv);
		string executableFileName = Translator::translate();
	}
	catch (const exception & ex) {
		cerr << ex.what() << endl;
		system("pause");
	}
}
