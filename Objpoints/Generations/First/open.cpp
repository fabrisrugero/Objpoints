#include "open.h"
const char* dbs = "dbDB";
const char* pngs = "pngPNG";
const char* jpgs = "jpgJPG";
const char* jpegs = "jpegJPEG";
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
	if (option::IsValidInput() && option::decimalIndex >= 0){
		while (option::validUserInputs[option::decimalIndex + this->decimalplaces] != '\0') this->decimalplaces++;
		if (this->decimalplaces < 2 || this->decimalplaces > 4) return false;
		this->Indexer = this->decimalplaces;
		for (this->InDexer = 0; this->InDexer < this->decimalplaces * 2; this->InDexer = +this->decimalplaces){
			if (!this->extMatcher(this->InDexer, this->decimalplaces)) continue;
			return this->dbOrImage = true;
		}	
	}
	return false;
};
bool Tools::open::extMatcher(int start, int ext){
	switch (ext){
	case 2:
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (validUserInputs[option::decimalIndex + this->Indexer] != dbs[start + this->Indexer]) return false;
		return true;
	case 3:
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (validUserInputs[option::decimalIndex + this->Indexer] != pngs[start + this->Indexer]) break;
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (validUserInputs[option::decimalIndex + this->Indexer] != jpgs[start + this->Indexer]) return false;
		return true;
	case 4:
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (validUserInputs[option::decimalIndex + this->Indexer] != jpegs[start + this->Indexer]) return false;
		return true;
	}
}
Tools::open::~open(){

}