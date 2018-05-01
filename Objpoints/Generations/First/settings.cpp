#include "settings.h"
char* Tools::settings::defaultPath = nullptr;
char** Tools::settings::groups = nullptr;
int Tools::settings::maxGroupIndex = 0;
int Tools::settings::defaultPaths = 0;
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
		if (settings::Paths > 0){
			option::clearConsoleScreen();
			for (this->Indexer = 0; this->Indexer < 40; this->Indexer++) std::cout << "--";
			for (this->Indexer = 0; this->Indexer < settings::Paths; this->Indexer++){
				std::cout << "\n|" << std::setfill('0')
					<< std::setw(3) << std::right << this->Indexer << "|";
				this->indexer = this->pathLenghts[this->Indexer] - 63;
				if (this->indexer < 0) this->indexer = 0; this->interation = 0;
				while (this->indexer < this->pathLenghts[this->Indexer])
					this->lines[this->interation++] = this->fullPaths[this->Indexer][this->indexer++];
				this->lines[this->interation] = '\0'; std::cout << std::setfill(' ') << std::setw(63) << std::left << this->lines;
				if (settings::defaultPaths != this->Indexer) std::cout << "|          |"; else std::cout << "|< default |";
				if ((this->Indexer + 1) % 2 == 0 || this->Indexer + 1 == settings::Paths)
					for (this->indexer = 0; this->indexer < 41; this->indexer++){
					if (this->indexer == 0) std::cout << std::endl; else std::cout << "--";}
			}
		}
		if (!this->success) 
			std::cout << " Error: unable to configure any settings press\n " <<
			this->index << " to try again or press enter to exit" << std::endl;
		else if (this->success && settings::Paths == 0)
			std::cout << " Oops: you have not files to configure press\n " <<
			this->index << " to add files to settings or press enter to exit" << std::endl;
	}
}
int Tools::settings::setPath(int index){
	return 0;
}
Tools::settings::settings(Menu Index) : option(settings::MAX_CHARS){
	this->settingsFile = new std::fstream("settings.txt", std::ios_base::in);
	this->fullPaths = new char*[settings::MAX_CHARS];
	this->pathLenghts = new int[settings::MAX_CHARS];
	this->index = static_cast<int>(Index)+1;
	this->Indexer = this->indexer = 0;
	this->lines = new char[1000];
}
bool Tools::settings::IsValidInput(){
	this->interation = atoi(option::validUserInputs);
	return option::IsValidInput();
};
void Tools::settings::deconstruct(){
	if (!this->settingsFile->is_open())
		this->settingsFile->open("settings.txt", std::ios_base::out);
	for (this->Indexer = 0; this->Indexer < settings::Paths; this->Indexer++){
		this->fullPaths[this->Indexer][this->pathLenghts[this->Indexer] + 1] = '\0';
		this->fullPaths[this->Indexer][this->pathLenghts[this->Indexer]] = '\n';
		*this->settingsFile << this->fullPaths[this->Indexer];
		this->settingsFile->flush();}
  this->settingsFile->close();
 for (this->Indexer = 0; this->Indexer < settings::Paths; this->Indexer++)
		delete[] this->fullPaths[this->Indexer];
 this->Indexer = this->indexer = settings::Paths = 0;
}
void Tools::settings::reconstruct(){
	if (!this->settingsFile->is_open())
		this->settingsFile->open("settings.txt", std::ios_base::in);
	this->settingsFile->read(this->lines, 1000);
	int size = static_cast<int>(this->settingsFile->gcount());
	if (size == 0) return this->settingsFile->close(); int endOfline = settings::Paths;
	while (this->Indexer++ < settings::MAX_PATHS && endOfline < size){
		while (this->lines[endOfline] != '\n') endOfline++;
		this->fullPaths[settings::Paths] = new char[endOfline + 2];
		for (this->interation = 0; this->lines[this->indexer] != '\n'; this->interation++)
			this->fullPaths[settings::Paths][this->interation] = this->lines[this->indexer++];
		this->fullPaths[settings::Paths][this->interation] = '\0'; this->indexer++; endOfline++;
		this->pathLenghts[settings::Paths++] = this->interation; }
	for (this->Indexer = 0; this->Indexer < this->settingsFile->gcount(); this->Indexer++) this->lines[this->Indexer] = '\0';
	this->settingsFile->clear(); this->settingsFile->seekg(0); this->Indexer = this->indexer = 0;
	this->settingsFile->close();
}
bool Tools::settings::update(){
	std::cout << "Enter fullpath here: "; option::removeKeysPressed(); 
	this->indexer = option::processKeysPressed(option::max_size);
	if (this->IsValidInput()){
		if (success = option::decimalIndex > 0){
			this->pathLenghts[settings::Paths] = this->indexer;
			this->fullPaths[settings::Paths] = new char[this->indexer + 2];
			for (this->Indexer = 0; option::validUserInputs[this->Indexer] != '\0'; this->Indexer++)
				this->fullPaths[settings::Paths][this->Indexer] = option::validUserInputs[this->Indexer];
			this->fullPaths[settings::Paths++][this->Indexer] = '\0';
		}
		else if (success = (this->indexer > 2 && this->interation >= 0 && this->interation <= settings::Paths))
			settings::defaultPaths = this->interation;
	}
	return true;
}
Tools::settings::~settings(){

}