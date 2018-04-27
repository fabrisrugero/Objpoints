#include "open.h"
#include "settings.h"
//#include "Shlwapi.h"
const char* Tools::open::dbs = "dbDB";
const char* Tools::open::pngs = "pngPNG";
const char* Tools::open::jpgs = "jpgJPG";
const char* Tools::open::jpegs = "jpegJPEG";
bool Tools::open::extMatcher(int start, int ext){
	switch (ext){
	default: return false;
	case 2:
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (option::validUserInputs[option::decimalIndex + this->Indexer + 1] != dbs[start + this->Indexer]) return false;
		return true;
	case 3:
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (option::validUserInputs[option::decimalIndex + this->Indexer + 1] != pngs[start + this->Indexer]) break;
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (option::validUserInputs[option::decimalIndex + this->Indexer + 1] != jpgs[start + this->Indexer]) return false;
		return true;
	case 4:
		for (this->Indexer = 0; this->Indexer < this->decimalplaces; this->Indexer++)
			if (option::validUserInputs[option::decimalIndex + this->Indexer + 1] != jpegs[start + this->Indexer]) return false;
		return true;
	}
}
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
		std::cout << this->index << ") open image/database" << std::endl;
	else{
		option::clearConsoleScreen();
		if (this->hasErrmsg) return abort();
		else if (!this->IsDbImage){
			int columns = this->table->initcolumns(this->colsoutput, this->setwidth);
			int rows = this->table->select(Tools::content::group);
			this->hasErrmsg = this->table->hasErrors(this->errmsg);
			if (!this->hasErrmsg) std::cout << this->colsoutput; else return abort();
			for (this->InDexer = 0; this->InDexer < settings::grps; this->InDexer++){
				for (this->Indexer = 0; this->Indexer < rows; this->Indexer++){
					for (this->interation = 0; this->interation < columns; this->interation++){
						this->table->select(this->results, this->interation, 0);
						std::cout << "|" << std::setw(this->setwidth) << this->results;}
					std::cout << "|\n"; break;}
				rows = this->table->select(Tools::content::next);
				if (this->hasErrmsg = this->table->hasErrors(this->errmsg)) break;}
			if (this->hasErrmsg)return abort();
		}
		else if (this->threadIsBusy)
			std::cout << "close the Image window first, Once Image window closed '"
			<< "\npress " << this->index << " to try again or enter to exit to main menu" << std::endl;
		else{
			this->threadIsBusy = true;
			std::cout << "opened '" << option::validUserInputs << "'"
				<< "\npress " << this->index << " to open a new image or database or press enter to exit" << std::endl;
		}
	}
}
bool Tools::open::IsValidInput(){
	if (option::IsValidInput() && option::decimalIndex > 0){
		while (option::validUserInputs[option::decimalIndex + this->decimalplaces + 1] != '\0') this->decimalplaces++;
		if (this->decimalplaces < 2 || this->decimalplaces > 4) return false;
		this->Indexer = this->decimalplaces;
		for (this->InDexer = 0; this->InDexer < this->decimalplaces * 2; this->InDexer += this->decimalplaces){
			if (!this->extMatcher(this->InDexer, this->decimalplaces)) continue;
			wchar_t* _wtext = new wchar_t[option::max_size + 1];
			int bytes = GetModuleFileName(NULL, _wtext, option::max_size + 1);
			for (this->Indexer = bytes - 1; _wtext[this->Indexer] != '\\' && _wtext[this->Indexer] != '//'; this->Indexer--) bytes--;
			this->indeXer = strlen(option::validUserInputs); bytes += this->indeXer; wchar_t* wtext = new wchar_t[bytes + 1];
			for (this->Indexer = 0; this->Indexer < this->indeXer; this->Indexer++)
				_wtext[bytes - this->indeXer + this->Indexer] = option::validUserInputs[this->Indexer];
			_wtext[bytes - this->indeXer + this->Indexer] = '\0';
			for (this->Indexer = 0; _wtext[this->Indexer] != '\0'; this->Indexer++)
				wtext[this->Indexer] = _wtext[this->Indexer];
			wtext[this->Indexer] = '\0'; delete[] _wtext;
			this->IsDbImage = this->decimalplaces > 2; 
			DWORD dwAttrib = GetFileAttributes(wtext);
			if ((dwAttrib != INVALID_FILE_ATTRIBUTES
				&&!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))){
				delete[] option::validUserInputs; 
				option::validUserInputs = new char[bytes + 1]; size_t outSize;
				wcstombs_s(&outSize, option::validUserInputs, bytes + 1, wtext, bytes + 1);
				delete[] wtext;
				return true;
			}
			else{
				delete[] wtext;
				return false;
			}

		}	
	}
	return false;
};
void Tools::open::deconstruct(){
	if (!this->threadIsBusy){
		if (this->thread != nullptr) {
			this->thread->join();
			delete this->thread;
			this->thread = nullptr;
		}
		if (this->validUserInputs != nullptr){
			delete[] this->validUserInputs;
			this->validUserInputs = nullptr;
		}
	}
}
void Tools::open::reconstruct(){
	this->Indexer = 0;
	this->InDexer = 0;
	this->indeXer = 0;
	this->deconstruct();
	this->decimalplaces = 0;
}
Tools::open::open(Menu Index) : option(settings::MAX_CHARS){
	this->window = nullptr;
	this->threadIsBusy = false;
	this->colsoutput[500] = {};
	this->validUserInputs = nullptr;
	this->index = static_cast<int>(Index)+1;
	this->errmsg = new char[settings::QUERY_SIZE];
}
bool Tools::open::opendb(){
	if (!this->IsDbImage){
		if (this->table != nullptr  && (this->conected = this->table->connectedTo(option::validUserInputs))
			&& !(this->hasErrmsg = this->table->hasErrors(this->errmsg))) return true;
		else if (this->table != nullptr  && (!this->conected || this->hasErrmsg)){
			delete this->table; this->table = new Tools::dbTable(option::validUserInputs);
			if (this->hasErrmsg = this->table->hasErrors(this->errmsg)) return false; }
		else if (this->table != nullptr) delete this->table;
		this->table = new Tools::dbTable(option::validUserInputs, this->Indexer);
		if (this->hasErrmsg = this->table->hasErrors(this->errmsg)) return false;
		settings::grps = this->table->select(Tools::content::distinct);
		if (this->hasErrmsg = this->table->hasErrors(this->errmsg)) return false;
		if (settings::groups != nullptr) delete[] settings::groups;
		if (settings::grps == 0) settings::groups = nullptr;
		else settings::groups = new char*[settings::grps];
		settings::maxGroupIndex = settings::grps - 1;
		for (this->Indexer = 0; this->Indexer < settings::grps; this->Indexer++)
			this->table->select(settings::groups[this->Indexer] 
			= new char[settings::MAX_CHARS], query::COL_ONE, this->Indexer);
		return true;
	}
	else{
		if (this->threadIsBusy) return true;
		this->validUserInputs = new char[this->Indexer + 1];
		for (this->Indexer = 0; option::validUserInputs[this->Indexer] != '\0'; this->Indexer++)
			this->validUserInputs[this->Indexer] = option::validUserInputs[this->Indexer];
		this->validUserInputs[this->Indexer] = '\0'; 
		this->thread = new std::thread{ [=](){
			this->window = new sfmlMananger(800, 600, this->validUserInputs);
			this->window->drawing();
			delete this->window;
			this->window = nullptr;
			this->threadIsBusy = false;
		} };
		return true;
	}
}
bool Tools::open::update(){
	std::cout << "Enter image/database: "; option::removeKeysPressed(); 
	option::processKeysPressed(option::alphanumeric);
	if (this->IsValidInput() && this->opendb())
		return true;
	if (settings::setPath(settings::defaultdb) > 0 && this->IsValidInput() && this->opendb())
		return true;
	else
		for (this->InDexer = 0; this->InDexer < settings::dbs; this->InDexer++)
			if (settings::setPath(this->InDexer) > 0 && this->IsValidInput() && this->opendb())
				return true;
	if (this->hasErrmsg) std::cout << this->errmsg;
	else std::cout << " Error: unable to open a file including any defualts set in settings";
	std::cout << "\npress " << this->index << " to try again or press enter to exit" << std::endl;
	return false;
}
void Tools::open::abort(){
	std::cout << this->errmsg << "\npress " << this->index
		<< " to try again or press enter to exit" << std::endl;
}
Tools::open::~open(){
	if (this->validUserInputs != nullptr) 
		delete[] this->validUserInputs;
}