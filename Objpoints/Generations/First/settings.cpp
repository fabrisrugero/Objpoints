#include "settings.h"
char* Tools::settings::defaultPath = nullptr;
char** Tools::settings::groups = nullptr;
int Tools::settings::maxGroupIndex = 0;
int Tools::settings::defaultdb = 0;
int Tools::settings::Paths = 0;
int Tools::settings::grps = 0;
bool Tools::settings::setPath(int index, char* output){
	return false;
}
void Tools::settings::outputIntroductions(){
	option::clearConsoleScreen();
	std::cout << "Only the following paths are accepted are accepted: " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "1. F:/.db" << std::endl;
	std::cout << "2. C:/blahblah/blahblah.db " << std::endl;
	std::cout << "3. E:/blahblah\blahblah.(jpg/png/jpeg)" << std::endl;
	std::cout << "4. Any whole number between 0 <> +99999 " << std::endl;
	std::cout << "NB: this function doesn't check if paths exists use the open function" << std::endl;
};
void Tools::settings::output(bool results){
	if (!results)
		std::cout << this->index << ") view settings" << std::endl;
	else{
		option::clearConsoleScreen();
	}
}
int Tools::settings::setPath(int index){
	return 0;
}
Tools::settings::settings(Menu Index) : option(settings::MAX_CHARS){
	this->file = new std::ifstream("settings.txt", std::ios_base::in);
	this->fullPaths = new char*[settings::MAX_CHARS];
	this->index = static_cast<int>(Index)+1;
	this->lines = new char[1000];
	this->Indexer = 0;

}
bool Tools::settings::IsValidInput(){
	return option::IsValidInput();
};
void Tools::settings::deconstruct(){
}
void Tools::settings::reconstruct(){
	int size;  this->file->read(this->lines + (this->indexer = 0), 1000);
	int endOfline = 0;  size = static_cast<int>(this->file->gcount());
	settings::Paths = 0; if (size == 0) return;
	while (this->Indexer++ < settings::MAX_PATHS && endOfline < size){
		while (this->lines[endOfline] != '\n') endOfline++;
		this->fullPaths[settings::Paths] = new char[endOfline + 1];
		for (this->interation = 0; this->lines[this->indexer] != '\n'; this->interation++)
			this->fullPaths[settings::Paths][this->interation] = this->lines[this->indexer++];
		this->fullPaths[settings::Paths++][this->interation] = '\0'; this->indexer++; endOfline++;}
	for (this->Indexer = 0; this->Indexer < this->file->gcount(); this->Indexer++) this->lines[this->Indexer] = '\0';
	this->file->clear(); this->file->seekg(0); this->Indexer = 0;
}
bool Tools::settings::update(){
	std::cout << "Enter fullpath here: ";
	option::removeKeysPressed(); option::processKeysPressed();


	return false;
}
Tools::settings::~settings(){

}