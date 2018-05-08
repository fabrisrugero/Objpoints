#include "points.h"
#include "settings.h"
void Tools::points::outputIntroductions(){
	option::clearConsoleScreen();
	std::cout << "Only the following comands/queries are accepted:\n";
	std::cout << "------------------------------------------------\n";
	std::cout << "1.Up and down arrow keys or w and s to tranverse db\n";
	std::cout << "2.Left and right arrow keys or a and d to launch points editor\n";
	std::cout << "3.To create a new point press enter whilst point editor in focus\n";
	std::cout << "4.once done editing a point press ecaspe whilst editor in focus \n";
	std::cout << "then press enter whilst console in focus to tabulate your work. \n";
	std::cout << "5.Arrow keys are used to move and WDAS are used to increase radius in the editor\n\n";
};
void Tools::points::output(bool results){
	if (!results)
		std::cout << this->index << ") Create/modify points" << std::endl;
	else{
		 if (this->table == nullptr) this->table = new dbTable(nullptr);
		 option::clearConsoleScreen(); if (this->table->hasErrors(this->errmsg))return abort();
		for (this->Indexer = 0; this->Indexer < maxcolumns; this->Indexer++)
			if (this->Indexer == id || this->Indexer == objectz) this->table->ignoredcolumns[this->Indexer] = true;
		this->columns = this->table->initcolumns(this->colsoutput, this->setwidth);
		this->rows = this->table->select(this->content);
		this->hasErrmsg = this->table->hasErrors(this->errmsg);
		if (!this->hasErrmsg) std::cout << this->colsoutput; else return abort();
		for (this->Indexer = 0; this->Indexer < this->rows; this->Indexer++){
			for (this->interation = 0; this->interation < this->columns; this->interation++){
				if (this->table->ignoredcolumns[this->interation]) continue;
				this->table->select(this->results, this->interation, this->Indexer);
				std::cout << "|" << std::setw(this->setwidth) << this->results;} std::cout << "|\n";}
		if (!this->issueWarning) std::cout << "\ntranverse or edit tables or simply press enter to exit database: ";
		else if (!(this->issueWarning = false)) std::cout << "\nclose the Editor window first before exiting";
		option::removeKeysPressed(); option::processKeysPressed(); 
		if (results = option::keyPressed('S', 's')) this->content = content::next;
		else if (results = option::keyPressed('W', 'w')) this->content = content::previous;
		else if (results = (option::keyPressed('D', 'd') || option::keyPressed('A', 'a'))){
			this->content = content::current; if (!this->editorIsOpen) {
				settings::setPath(this->pathIndex + 1, false);
				this->editor = new std::thread{ [=](){
					this->window = new sfmlMananger(
						800, 600, settings::defaultPath);
					this->window->drawing();
					delete this->window;
					this->window = nullptr;
					this->editorIsOpen = false;
				} }; this->editorIsOpen = true;}}
		if (results) return this->output(true);
		else if (this->editorIsOpen) return this->output(this->issueWarning = true);
		else std::cout << "\npress " << this->index << " to open a new database or press enter again to exit to main menu" << std::endl;
	}
}
bool Tools::points::IsValidInput(){
	if (option::IsValidInput() && option::decimalIndex < 0)
		return settings::setPath(this->pathIndex = atoi(option::validUserInputs), false) > 0;
	else 
		return settings::setPath(this->pathIndex = settings::defaultPathIndex, false) > 0;
	return false;
};
Tools::points::points(Menu Index) : option(settings::MAX_CHARS){
	this->errmsg = new char[option::max_size];
	this->index = static_cast<int>(Index)+1;
	this->Indexer = this->interation = 0;
	this->content = content::next;
	this->editorIsOpen = false;
	this->table = nullptr;
}
void Tools::points::deconstruct(){
	if (!this->editorIsOpen && 
		this->editor != nullptr) {
		this->editor->join();
		delete this->editor;
		this->editor = nullptr;
	}
}
void Tools::points::reconstruct(){
	this->issueWarning = false;
}
bool Tools::points::update(){
	std::cout << "Enter the database index or simply pres enter to open default index: ";
	option::removeKeysPressed(); option::processKeysPressed();
	if (this->IsValidInput()) return true;
	else std::cout << "you have entered an invalid databse index and the default index isn't "
		<<"\nvalid either check your settings and make sure there are configured correctly";
	return false;
}
void Tools::points::abort(){
	std::cout << this->errmsg << "\npress " << this->index
		<< " to try again or press enter to exit" << std::endl;
}
Tools::points::~points(){

}
