#include "history.h"
#include "settings.h"
void Tools::history::outputIntroductions(){
	option::clearConsoleScreen();
	std::cout << "Only the following time formats are accepted: " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "1.seconds are between 0 <> +99999 " << std::endl;
	std::cout << "2.minutes are betwwwn 0.0 <> +99999.0 " << std::endl;
	std::cout << "3.Decimal places are limited to 2 places eg. 0.30" << std::endl << std::endl;
};
void Tools::history::output(bool results){
	if (!results)
		std::cout << this->index << ") view all changes since application strart" << std::endl;
	else{
		option::clearConsoleScreen();
	}
}
Tools::history::history(Menu Index) : option(settings::MAX_CHARS){
	this->index = static_cast<int>(Index)+1;
}
bool Tools::history::update(){
	std::cout << "Enter time to backtrack to: ";
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