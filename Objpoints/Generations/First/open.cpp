#include "open.h"
void Tools::open::outputIntroductions(){
	option::clearConsoleScreen();
	std::cout << "Only the following file formats will be accepted:\n";
	std::cout << "------------------------------------------------\n";
	std::cout << "1.Joint Photographic Experts Group ( JPEG/JPG )\n";
	std::cout << "2.Portable Network Graphics ( PNG )\n";
	std::cout << "3.SQLite Database file ( db )\n\n";
};
void Tools::open::output(bool results){
	if (!results)
		std::cout << this->index << ") open local image/database" << std::endl;
	else{
		option::clearConsoleScreen();
	}
}
Tools::open::open(Menu Index) : option(){
	this->index = static_cast<int>(Index) + 1;
}
bool Tools::open::update(){
	std::cout << "Enter FileName: ";
	option::removeKeysPressed(); 
	option::processKeysPressed(option::alphanumeric);
	return false;
}
bool Tools::open::IsValidInput(){
	this->Indexer = 0;
	if (option::IsValidInput()){
		if (option::decimalIndex >= 0){
			while (option::validUserInputs[option::decimalIndex + this->Indexer] != '\0') this->Indexer++;

		}
	}
	return false;
};
Tools::open::~open(){

}