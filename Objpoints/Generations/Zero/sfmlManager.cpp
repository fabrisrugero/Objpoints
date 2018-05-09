#include "sfmlManager.h"
#include <stdlib.h>
Tools::sfmlMananger::sfmlMananger(){
	this->points = 0;
	this->width = 800;
	this->height = 600;
	this->x = this->y = 0;
	this->IsVisible = false;
	this->hasPoints = false;
	this->results = new char[10];
	this->event = new sf::Event();
	this->filename = "testWindow";
	this->pointsList = new double*[3];
	this->pointsList[0] = new double[1]();
	this->pointsList[1] = new double[1]();
	this->pointsList[1] = new double[1]();
	this->canvas = new sf::RenderWindow();
	this->mode = new sf::VideoMode(800, 600);
	this->success = this->tex.loadFromFile("...jpg");
	if (this->success) this->cartoon.setTexture(tex);
}
void Tools::sfmlMananger::drawing(){
	if (!this->IsVisible){
		this->canvas->create(*this->mode, this->filename);
		this->canvas->setFramerateLimit(60);}
	while (this->canvas->isOpen()){
		while (this->canvas->pollEvent(*this->event))
			if (this->event->type == sf::Event::Closed){
			this->canvas->setActive(false);
			this->canvas->close();}	
		this->canvas->clear();
		this->GetPoints();
		this->DrawPoints();
		this->DrawTexture();
		this->canvas->display();
	}
}
Tools::sfmlMananger::~sfmlMananger(){
	for (this->indexer = 0; this->indexer < 3; this->indexer++)
		delete[] this->pointsList[this->indexer];
	delete[] this->pointsList;
	delete[] this->filename;
	delete[] this->results;
	delete this->canvas;
	delete this->mode;
}
void Tools::sfmlMananger::GetPoints(){
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->hasPoints) this->hasPoints = false;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !this->hasPoints){ this->hasPoints = true;
		if (this->table == nullptr) this->table = new dbTable(nullptr);
		if (!(this->hasErrmsg = this->table->hasErrors()))
			this->points = this->table->select(content::current);
		if (!(this->hasErrmsg = this->table->hasErrors()) && this->points > 0){
			for (this->indexer = 0; this->indexer < 3; this->indexer++)
				delete[] this->pointsList[this->indexer];
			for (this->indexer = 0; this->indexer < 3; this->indexer++)
				this->pointsList[this->indexer] = new double[this->points]();
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->table->select(this->results, pointx, this->indexer);
				this->pointsList[One][this->indexer] = atof(this->results);
				this->table->select(this->results, pointy, this->indexer);
				this->pointsList[Two][this->indexer] = atof(this->results);
				this->table->select(this->results, radius, this->indexer);
				this->pointsList[Three][this->indexer] = atof(this->results);}}
	}
}
void Tools::sfmlMananger::DrawPoints(){


}
void Tools::sfmlMananger::DrawTexture(){
	this->cartoon.setPosition(static_cast<float>(this->x),
		static_cast<float>(this->y));
	this->canvas->draw(this->cartoon);
};
void Tools::sfmlMananger::extractName(char* path){
	this->fileLenght = settings::MAX_CHARS + 100;
	size_t dOfElemts = settings::MAX_CHARS + 100;
	size_t	dirOfElemts = settings::MAX_CHARS + 100;
	size_t	extOfElemts = settings::MAX_CHARS + 100;
	char *dir = new char[settings::MAX_CHARS + 100];
	char *ext = new char[settings::MAX_CHARS + 100];
	char * drive = new char[settings::MAX_CHARS + 100];
	this->filename = new char[settings::MAX_CHARS + 100];
	_splitpath_s(path, drive, dOfElemts, dir, dirOfElemts,
		this->filename, this->fileLenght, ext, extOfElemts);
	delete[] dir; delete[] ext; delete[] drive;
}
Tools::sfmlMananger::sfmlMananger(int width, int height, char* image){
	this->points = 0;
	this->width = width;
	this->x = this->y = 0;
	this->height = height;
	this->IsVisible = false;
	this->hasPoints = false;
	this->extractName(image);
	this->event = new sf::Event();
	this->pointsList = new double*[3];
	this->pointsList[0] = new double[1]();
	this->pointsList[1] = new double[1]();
	this->pointsList[1] = new double[1]();
	this->canvas = new sf::RenderWindow();
	this->mode = new sf::VideoMode(width, height);
	this->success = this->tex.loadFromFile(image);
	if (this->success) this->cartoon.setTexture(tex);
}
bool Tools::sfmlMananger::reconstruct(int width, int height, char* image){
	delete this->mode;
	delete this->event;
	this->width = width;
	this->height = height;
	this->hasPoints = false;
	this->extractName(image);
	this->event = new sf::Event();
	this->mode = new sf::VideoMode(width, height);
	this->success = this->tex.loadFromFile(image);
	if (this->success) this->cartoon.setTexture(tex);
	return success;
}

