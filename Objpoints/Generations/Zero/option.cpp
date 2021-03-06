#include "option.h"
int Tools::option::inputs = 0;
int Tools::option::indexer = 0;
int Tools::option::charIndex = 0;
Tools::option::~option(){
	delete[] results;
}
int Tools::option::decimalIndex = -1;
bool Tools::option::update(){
	return true;
}
int Tools::option::validCharIndex = 0;
char Tools::option::_keyPressed = '\0';
bool Tools::option::hasDecimal = false;
char* Tools::option::validInputs = nullptr;
const char* Tools::option::escapes = "_@-\\//:";
char* Tools::option::userInputs = new char[max_size];
char* Tools::option::validUserInputs = new char[max_size];
const char* Tools::option::alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
Tools::option::option(int buffersize){
	this->buffersize = buffersize;
	this->results = new char[buffersize]();
	if (option::validInputs != nullptr) return;
	option::validInputs = new char[alphanumeric + 1];
	for (this->interation = 0; this->interation < 10; this->interation++)
		option::validInputs[this->interation] = '0' + this->interation;
	for (this->interation = 0; this->interation < 52; this->interation++)
		option::validInputs[this->interation + 10] = option::alphabet[this->interation];
	for (this->interation = 0; this->interation < 6; this->interation++)
		option::validInputs[this->interation + 62] = option::escapes[this->interation];
	option::validInputs[this->interation + 62] = '\0';
}
void Tools::option::removeKeysPressed(){
	if (userInputs == nullptr) return;
	for (indexer = 0; indexer < max_size; indexer++)
		userInputs[indexer] = '\0';
	for (indexer = 0; indexer < max_size; indexer++)
		validUserInputs[indexer] = '\0';
	validCharIndex = 0; hasDecimal = false; decimalIndex = -1;
};
bool Tools::option::IsValidInput(){
	if (!hasDecimal && validCharIndex > 0) return true;
	else if (hasDecimal && validCharIndex >= 2) return true;
	else return false;
}
int Tools::option::processKeysPressed(int maxchars){
	while (std::cin.get(_keyPressed)){
		if (charIndex < maxchars && _keyPressed != '\n')
			userInputs[charIndex++] = _keyPressed;
		else 
			break;
	}
	userInputs[charIndex] = '\0'; inputs = charIndex;
	while (charIndex){
		for (indexer = 0; userInputs[inputs - charIndex] != '\0'; indexer++){
			if (userInputs[inputs - charIndex] == validInputs[indexer]){
				validUserInputs[validCharIndex++] = userInputs[inputs - charIndex];
				 break;
			}
			else if (userInputs[inputs - charIndex] == '.'){
				validUserInputs[validCharIndex++] = userInputs[inputs - charIndex];
				decimalIndex = validCharIndex - 1;
				hasDecimal = true; 
				break;
			}
		}	
		charIndex--;
		if (charIndex == 0) validUserInputs[validCharIndex] = '\0';
	}
	return validCharIndex;
};
void Tools::option::clearConsoleScreen(){
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
};
bool Tools::option::keyPressed(int Menuindex){
	if (validUserInputs == nullptr) return false;
	switch (Menuindex){
	  default:
		 return false;
	case One:
		for (indexer = 0; validUserInputs[indexer] != '\0'; indexer++)
			if (validUserInputs[indexer] == '1') return true;
		break;
	case Two:
		for (indexer = 0; validUserInputs[indexer] != '\0'; indexer++)
			if (validUserInputs[indexer] == '2') return true;
		break;
	case Three:
		for (indexer = 0; validUserInputs[indexer] != '\0'; indexer++)
			if (validUserInputs[indexer] == '3') return true;
		break;
	case Four:
		for (indexer = 0; validUserInputs[indexer] != '\0'; indexer++)
			if (validUserInputs[indexer] == '4') return true;
		break;
	case Five:
		for (indexer = 0; validUserInputs[indexer] != '\0'; indexer++)
			if (validUserInputs[indexer] == '5') return true;
		break;
	}
	return false;
};
bool Tools::option::outputErrorToSecreen(int option){
	std::cout << std::endl << "You have entered an invalid value"
		<<" press "<< option <<" to try again... ";
	return false;
};
bool Tools::option::keyPressed(char upper, char lower){
	if (userInputs == nullptr) return false;
	for (indexer = 0; userInputs[indexer] != '\0'; indexer++)
		if (userInputs[indexer] == upper) return true;
	for (indexer = 0; userInputs[indexer] != '\0'; indexer++)
		if (userInputs[indexer] == lower) return true;
	return false;
};

