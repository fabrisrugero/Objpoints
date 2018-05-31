#include "settings.h"
int Tools::settings::grps = 0;
int Tools::settings::Paths = 0;
int Tools::settings::inDexer = 0;
int Tools::settings::rootIndex = 0;
int Tools::settings::lRootIndex = 0;
int Tools::settings::maxGroupIndex = 0;
char** Tools::settings::groups = nullptr;
int Tools::settings::defaultPathIndex = 0;
char** Tools::settings::fullPaths = nullptr;
int* Tools::settings::rootIndeces = nullptr;
int* Tools::settings::pathLenghts = nullptr;
char* Tools::settings::defaultPath = nullptr;
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
		if (Paths > 0){
			option::clearConsoleScreen();
			for (this->Indexer = 0; this->Indexer < 40; this->Indexer++) std::cout << "--";
			for (this->Indexer = 0; this->Indexer < Paths; this->Indexer++){
				std::cout << "\n|" << std::setfill('0')
					<< std::setw(3) << std::right << this->Indexer << "|";
				this->indexer = pathLenghts[this->Indexer] - 63;
				if (this->indexer < 0) this->indexer = 0; this->interation = 0;
				while (this->indexer < pathLenghts[this->Indexer])
					this->lines[this->interation++] = this->fullPaths[this->Indexer][this->indexer++];
				this->lines[this->interation] = '\0'; std::cout << std::setfill(' ') << std::setw(63) << std::left << this->lines;
				if (defaultPathIndex != this->Indexer && !this->removePaths[this->Indexer] ) std::cout << "|          |";
				else if (this->removePaths[this->Indexer]) std::cout << "|< deleted |"; else std::cout << "|< default |";
				if (this->Indexer + 1 == Paths)for (this->indexer = 0; this->indexer < 41; this->indexer++){
					if (this->indexer == 0) std::cout << std::endl; else std::cout << "--";}
				else for (this->indexer = 0; this->fullPaths[this->Indexer + 1][this->indexer] != '\0'; this->indexer++){
					if (this->fullPaths[this->Indexer + 1][this->indexer] == '.'){
						if ((this->fullPaths[this->Indexer + 1][this->indexer + 1] == 'd'
							&& this->fullPaths[this->Indexer + 1][this->indexer + 2] == 'b'
							&& this->fullPaths[this->Indexer + 1][this->indexer + 3] == '\0') 
							){ for (this->indexer = 0; this->indexer < 41; this->indexer++){
								if (this->indexer == 0) std::cout << std::endl; else std::cout << "--";}break;}
					}
				}
			}
		}
		if (!this->success) 
			std::cout << " Error: unable to configure any settings press\n " <<
			this->index << " to try again or press enter to exit" << std::endl;
		else if (this->success && Paths == 0)
			std::cout << " Oops: you have not files to configure press\n " <<
			this->index << " to add files to settings or press enter to exit" << std::endl;
	}
}
int Tools::settings::setPath(int index, bool newPath){
	if (!newPath && index >= 0 && index < Paths){
		for (inDexer = 0; fullPaths[index][inDexer] != '\0'; inDexer++)
			defaultPath[inDexer] = fullPaths[index][inDexer]; defaultPath[inDexer] = '\0'; 
		if (option::validUserInputs == nullptr) return pathLenghts[index];
		for (inDexer = 0; defaultPath[inDexer] != '\0'; inDexer++)
			if (defaultPath[inDexer] == '\\') lRootIndex = rootIndexer(); 
		for (inDexer = rootIndeces[rootIndex]; defaultPath[inDexer] != '\0'; inDexer++)
			option::validUserInputs[inDexer - rootIndeces[rootIndex]] = defaultPath[inDexer];
		if (defaultPath[inDexer - 1] == '\n') option::validUserInputs[inDexer - lRootIndex - 1] =
			option::validUserInputs[inDexer - lRootIndex] = defaultPath[inDexer - 1] = '\0';
		for (inDexer = 0; option::validUserInputs[inDexer] != '\0'; inDexer++)
		if (option::validUserInputs[inDexer] == '.') option::decimalIndex = inDexer;
		inDexer = 0; return pathLenghts[index];}
	else if(newPath){
		while (option::validUserInputs[inDexer] != '\0') inDexer++;
		fullPaths[Paths] = new char[inDexer + 2];
		for (inDexer = 0; option::validUserInputs[inDexer] != '\0'; inDexer++){
			fullPaths[Paths][inDexer] = option::validUserInputs[inDexer];
			defaultPath[inDexer] = option::validUserInputs[inDexer];}
		defaultPath[inDexer] = fullPaths[Paths][inDexer] = '\0';
		pathLenghts[Paths++] = inDexer; inDexer = 0; 
		return pathLenghts[defaultPathIndex];}
	return 0;
}
int Tools::settings::rootIndexer(){
	rootIndeces[Four] = rootIndeces[Three];
	rootIndeces[Three] = rootIndeces[Two];
	rootIndeces[Two] = rootIndeces[One];
	return rootIndeces[One] = inDexer + 1;
};
Tools::settings::settings(Menu Index) : option(MAX_CHARS){
	this->settingsFile = new std::fstream("settings.txt", std::ios_base::in);
	settings::defaultPath = new char[option::max_size];
	settings::pathLenghts = new int[MAX_CHARS];
	settings::fullPaths = new char*[MAX_CHARS];
	this->removePaths = new bool[MAX_CHARS]();
	this->index = static_cast<int>(Index)+1;
	settings::rootIndeces = new int[four]();
	this->Indexer = this->indexer = 0;
	this->lines = new char[1000];
	this->remove = false;
}
bool Tools::settings::IsValidInput(){
	this->interation = atoi(option::validUserInputs);
	if (this->interation - 100 >= 0){
		this->remove = !this->remove;
		 this->interation -= 100;}
	return option::IsValidInput();
};
void Tools::settings::deconstruct(){
	if (!this->settingsFile->is_open())
		this->settingsFile->open("settings.txt", std::ios_base::out);
	for (this->Indexer = 0; this->Indexer < Paths; this->Indexer++){
		if (this->removePaths[this->Indexer]) continue;
		fullPaths[this->Indexer][pathLenghts[this->Indexer] + 1] = '\0';
		fullPaths[this->Indexer][pathLenghts[this->Indexer]] = '\n';
		*this->settingsFile << fullPaths[this->Indexer];
		this->settingsFile->flush();}
  this->settingsFile->close();
  this->remove = false;
  this->Indexer = 0;
  this->indexer = 0;
}
void Tools::settings::reconstruct(){
	if (Paths > 0) this->deconstruct();
	if (!this->settingsFile->is_open())
		this->settingsFile->open("settings.txt", std::ios_base::in);
	this->settingsFile->read(this->lines, 1000);
	int size = static_cast<int>(this->settingsFile->gcount());
	if (size == 0) return this->settingsFile->close(); int endOfline = 0;
	for (this->interation = 0; this->interation < Paths; this->interation++) {
		delete[] fullPaths[this->interation]; this->removePaths[this->interation] = false;}	
	Paths = 0; while (this->Indexer++ < MAX_PATHS && endOfline < size){
		while (this->lines[endOfline] != '\n') endOfline++;
		fullPaths[Paths] = new char[endOfline + 2];
		for (this->interation = 0; this->lines[this->indexer] != '\n'; this->interation++)
			fullPaths[Paths][this->interation] = this->lines[this->indexer++];
		fullPaths[Paths][this->interation] = '\0'; this->indexer++; endOfline++;
		pathLenghts[Paths++] = this->interation; }
	for (this->Indexer = 0; this->Indexer < this->settingsFile->gcount(); this->Indexer++) this->lines[this->Indexer] = '\0';
	this->settingsFile->clear(); this->settingsFile->seekg(0); this->Indexer = this->indexer = 0;
	this->settingsFile->close();
}
bool Tools::settings::update(){
	std::cout << "Enter fullpath here: "; option::removeKeysPressed(); 
	this->indexer = option::processKeysPressed(option::max_size);
	if (this->IsValidInput()){
		if (success = option::decimalIndex > 0){
			pathLenghts[Paths] = this->indexer;
			fullPaths[Paths] = new char[this->indexer + 2];
			for (this->Indexer = 0; option::validUserInputs[this->Indexer] != '\0'; this->Indexer++)
				fullPaths[Paths][this->Indexer] = option::validUserInputs[this->Indexer];
			fullPaths[Paths++][this->Indexer] = '\0';
		}
		else if (success = (this->indexer > 2 && this->interation >= 0 && this->interation <= Paths)){
			if(!this->remove) defaultPathIndex = this->interation;
			this->removePaths[this->interation] = this->remove;
		}
	}
	return true;
}
Tools::settings::~settings(){
	delete[] this->lines;
	delete this->settingsFile;
	delete[] this->removePaths;
	delete[] settings::fullPaths;
	delete[] settings::pathLenghts;
}