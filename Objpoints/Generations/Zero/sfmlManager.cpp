#include "sfmlManager.h"
#include <stdlib.h>
Tools::sfmlMananger::sfmlMananger(){
	this->width = 800;
	this->height = 600;
	this->x = this->y = 0;
	this->IsVisible = false;
	this->event = new sf::Event();
	this->filename = "testWindow";
	this->canvas = new sf::RenderWindow();
	this->mode = new sf::VideoMode(800, 600);
	this->success = this->tex.loadFromFile("...jpg");
	if (this->success) this->cartoon.setTexture(tex);
}
Tools::sfmlMananger::sfmlMananger(int width, int height, char* image){
	this->width = width;
	this->x = this->y = 0;
	this->height = height;
	this->IsVisible = false;
	this->extractName(image);
	this->event = new sf::Event();
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
	this->extractName(image);
	this->event = new sf::Event();
	this->mode = new sf::VideoMode(width, height);
	this->success = this->tex.loadFromFile(image);
	if (this->success) this->cartoon.setTexture(tex);
	return success;
}
bool Tools::sfmlMananger::update(){

	return true;
}
bool Tools::sfmlMananger::draw(){
	if (!this->success) return this->success;
	this->cartoon.setPosition(static_cast<float>(this->x),
		static_cast<float>(this->y));
	this->canvas->draw(this->cartoon);
	return this->success;
};
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
		this->update();
		this->draw();
		this->canvas->display();
	}
}
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
Tools::sfmlMananger::~sfmlMananger(){
	delete[] this->filename;
	delete this->canvas;
	delete this->mode;
}