#pragma once
#include "../../Enums/enums.h"
#include "dbTable.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
namespace Tools{
	class option{
	public:
		~option();
		virtual bool update();
		option(int buffersize);
		static const int max_size = 200;
		static void removeKeysPressed();
		static void clearConsoleScreen();
		static const int alphanumeric = 67;
		static bool keyPressed(int Menuindex);
		virtual void outputIntroductions() = 0;
		virtual void output(bool results = true) = 0;
		static bool keyPressed(char upper, char lower);	
		static void processKeysPressed(int digits = 11);
	protected:
		static bool outputErrorToSecreen(int option);
		static char* validUserInputs;
		virtual bool IsValidInput();
		static int decimalIndex;
		int buffersize;
		int interation;
		char *results;
		int Indexer;
		int index;

	private:	
		static int inputs;
		static int indexer;
		static int charIndex;
		static bool hasDecimal;
		static char _keyPressed;
		static char* userInputs;
		static char* validInputs;
		static int validCharIndex;
		static const char* escapes;
		static const char* alphabet;
		static const char* lowercase;
		static const char* uppercase;
		static const int maxchars = 12;
	};
}
