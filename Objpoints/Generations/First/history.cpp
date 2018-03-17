#include "history.h"
void Tools::history::outputIntroductions(){
	option::clearConsoleScreen();
	std::cout << "Only the following formats and numbers are accepted: " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "1.Any integer number between -99999 <> +99999 " << std::endl;
	std::cout << "2.Any real number between -9999.0 <> +99999.0 " << std::endl;
	std::cout << "3.Decimal places are limited to 6 places eg. 0.123456" << std::endl << std::endl;
};
void Tools::history::output(bool results){
	if (!results)
		std::cout << this->index << ") Celsius to Kelvin" << std::endl;
	else{
		option::clearConsoleScreen();
	}
}
Tools::history::history(Menu Index) : option(){
	this->index = static_cast<int>(Index)+1;
}
bool Tools::history::update(){
	std::cout << "Enter Degrees Celsuis: ";
	option::removeKeysPressed(); option::processKeysPressed();
	return false;
}
bool Tools::history::IsValidInput(){
	this->Indexer = 0;
	if (option::IsValidInput()){
		if (option::decimalIndex >= 0){
			while (option::validUserInputs[option::decimalIndex + this->Indexer] != '\0') this->Indexer++;

		}
	}
	return false;
};
Tools::history::~history(){

}