#pragma once
#include "../../Enums/enums.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
namespace Tools{
	class option{
	public:
		~option();
		virtual bool update();
		option(int interations = 1);
		virtual bool IsValidInput();
		static void removeKeysPressed();
		static void processKeysPressed();
		static void clearConsoleScreen();
		static bool keyPressed(int Menuindex);
		virtual void outputIntroductions() = 0;
		virtual void output(bool results = true) = 0;
		static bool keyPressed(char upper, char lower);	
	protected:
		static bool outputErrorToSecreen(int option);
		static const int maxinterations = 144;
		static char* validUserInputs;
		static int decimalIndex;
		int interations;
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
		static const int maxchars = 12;
	};
}
