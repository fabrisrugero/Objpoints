#include "open.h"
#include "settings.h"
const char* Tools::open::dbs = "dbDB";
const char* Tools::open::pngs = "pngPNG";
const char* Tools::open::jpgs = "jpgJPG";
const char* Tools::open::jpegs = "jpegJPEG";
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
	this->table = nullptr;
	this->index = static_cast<int>(Index) + 1;
}
bool Tools::open::opendb(){
	if (!this->IsDbImage){
		if (this->table != nullptr){
			if (!this->table->connectedTo(option::validUserInputs)){
				delete this->table;
				this->table = new Tools::dbTable(option::validUserInputs);
				if (!this->table->errors()) this->table->select(Tools::content::distinct);
			}
			else 
				this->table->select(Tools::content::distinct);

		}
		return true;
	}
	else{
		return false;
	}
}
bool Tools::open::update(){
	std::cout << "Enter FileName: "; option::removeKeysPressed(); 
	option::processKeysPressed(option::alphanumeric);
	if (this->IsValidInput())
		return this->opendb();
	else {
		if (Tools::settings::setPath(Tools::settings::defaultdb) && this->IsValidInput())
			return this->opendb();
		else
			for (this->Indexer = 0; this->Indexer < Tools::settings::dbs; this->Indexer++)
				if (Tools::settings::setPath(this->Indexer) && this->IsValidInput())
					return this->opendb();
	}
	std::cout <<" Error: unable to open a file including any defualts set in settings \n" 
		<< "press "<< this->index <<" to try again or press enter to exit" << std::endl;
	return false;
}
bool Tools::open::IsValidInput(){
	if (option::IsValidInput() && option::decimalIndex > 0){
		while (option::validUserInputs[option::decimalIndex + this->decimalplaces] != '\0') this->decimalplaces++;
		if (this->decimalplaces < 2 || this->decimalplaces > 4) return false;
		this->Indexer = this->decimalplaces;
		for (this->InDexer = 0; this->InDexer < this->decimalplaces * 2; this->InDexer = +this->decimalplaces){
			if (!this->extMatcher(this->InDexer, this->decimalplaces)) continue;
			this->Indexer = strlen(option::validUserInputs);    
			wchar_t* wtext = new wchar_t[this->Indexer];
			this->IsDbImage = this->decimalplaces > 2; size_t outSize;
			mbstowcs_s(&outSize, wtext, this->Indexer + 1, option::validUserInputs, this->Indexer + 1);
			DWORD dwAttrib = GetFileAttributes(wtext);
			bool result = (dwAttrib != INVALID_FILE_ATTRIBUTES 
				&&!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
			delete[] wtext; return result;
		}	
	}
	return false;
};
bool Tools::open::extMatcher(int start, int ext){
	switch (ext){
	default: return false;
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