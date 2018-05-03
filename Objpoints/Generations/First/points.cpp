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
	std::cout << "then press enter whilst console in focus to tabulate your work. \n\n";
	std::cout << "5.Arrow keys are used to move and WDAS are used to increase radius in the editor\n";
};
void Tools::points::output(bool results){
	if (!results)
		std::cout << this->index << ") Create/modify points" << std::endl;
	else{
		option::clearConsoleScreen(); if (this->table != nullptr) delete this->table;	
		this->table = new dbTable(nullptr); if (this->table->hasErrors(this->errmsg))return abort();
		for (this->Indexer = 0; this->Indexer < maxcolumns; this->Indexer++)
			if (this->Indexer == id || this->Indexer == objectz) this->table->ignoredcolumns[this->Indexer] = true;
		this->columns = this->table->initcolumns(this->colsoutput, this->setwidth);
		this->rows = this->table->select(this->content);
		this->hasErrmsg = this->table->hasErrors(this->errmsg);
		if (!this->hasErrmsg) std::cout << this->colsoutput; else return abort();
		for (this->Indexer = 0; this->Indexer < this->rows; this->Indexer++){
			for (this->interation = 0; this->interation < this->columns; this->interation++){
				if (this->table->ignoredcolumns[this->interation]) continue;
				this->table->select(this->results, this->interation, 0);
				std::cout << "|" << std::setw(this->setwidth) << this->results;} std::cout << "|\n";}
		std::cout << "\nEnter a command or press <<" << this->index << " simply press enter to exit to main menu: ";
		option::removeKeysPressed(); option::processKeysPressed(); if(!this->IsValidInput()) return;
		if (results = option::keyPressed('S', 's')) this->content = content::next;
		else if (results = option::keyPressed('W', 'w')) this->content = content::previous;
		else if (results = (option::keyPressed('D', 'd') || option::keyPressed('A', 'a'))){
			//start points editor in new thread here
		}
		if (results) return this->output(true);
	}
}
Tools::points::points(Menu Index) : option(settings::MAX_CHARS){
	this->errmsg = new char[option::max_size];
	this->index = static_cast<int>(Index)+1;
	this->Indexer = this->interation = 0;
	this->content = content::next;
	this->IsUpdating = true;
	this->table = nullptr;
}
void Tools::points::deconstruct(){
}
void Tools::points::reconstruct(){
}
bool Tools::points::update(){
	std::cout << "Enter the database index or simply pres enter to open default index: ";
	option::removeKeysPressed(); option::processKeysPressed();
	if (this->IsValidInput()) this->IsUpdating = false;
	else std::cout << "you have entered an invalid databse index and the default index isn't "
		<<"\nvalid either check your settings and make sure there are configured correctly";
	return !this->IsUpdating;
}
bool Tools::points::IsValidInput(){
	if (option::IsValidInput() && option::decimalIndex < 0){
		if (this->IsUpdating)
			return settings::setPath(atoi(option::validUserInputs)) > 0;
		else if (option::validUserInputs[0] == 'a' ||
			option::validUserInputs[0] == 'w' ||
			option::validUserInputs[0] == 's' ||
			option::validUserInputs[0] == 'd')
			return true;}
	else if (this->IsUpdating)
		return settings::setPath(settings::defaultPathIndex) > 0;
	return false;
};
Tools::points::~points(){

}
void Tools::points::abort(){
	std::cout << this->errmsg << "\npress " << this->index
		<< " to try again or press enter to exit" << std::endl;
}