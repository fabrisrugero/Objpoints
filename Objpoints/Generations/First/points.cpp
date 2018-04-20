#include "points.h"
#include "settings.h"
void Tools::points::outputIntroductions(){
	option::clearConsoleScreen();
	std::cout << "Only the following comands/queries are accepted:\n";
	std::cout << "------------------------------------------------\n";
	std::cout << "1.seperate multiple comands with a vertical bar\n";
	std::cout << "2.Blank input followed by enter display all points\n";
	std::cout << "3.Only alphanumeric characters allowed eg a-z, A-Z and 0-9\n";
	std::cout << "4.-T <name> this command returns all points belonging to specified Type\n";
	std::cout << "5.-p <name> this command returns all points belonging to specified part\n\n";
};
void Tools::points::output(bool results){
	if (!results)
		std::cout << this->index << ") Create/modify points" << std::endl;
	else{
		option::clearConsoleScreen();
	}
}
Tools::points::points(Menu Index) : option(settings::MAX_CHARS){
	this->index = static_cast<int>(Index)+1;
}
bool Tools::points::update(){
	std::cout << "Enter command/query: ";
	option::removeKeysPressed(); option::processKeysPressed();
	return false;
}
bool Tools::points::IsValidInput(){
	this->Indexer = 0;
	if (option::IsValidInput()){
		if (option::decimalIndex >= 0){
			while (option::validUserInputs[option::decimalIndex + this->Indexer] != '\0') this->Indexer++;

		}
	}
	return false;
};
Tools::points::~points(){

}