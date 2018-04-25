#include "sfmlManager.h"
#include <stdlib.h>

Tools::sfmlMananger::sfmlMananger(int width, int height, char* image){
	this->width = width;
	this->x = this->y = 0;
	this->height = height;
	this->extractName(image);
	this->canvasIsCreated = false;
	this->tex.loadFromFile(image);
	this->cartoon.setTexture(tex);
	this->mode = new sf::VideoMode(width, height);
}
void Tools::sfmlMananger::draw(){
	if (!this->canvasIsCreated) settings::canvas->create(*this->mode, this->filename);
	if (!settings::IscanvasVisible()) settings::canvasVisible(true);
	this->cartoon.setPosition(static_cast<float>(this->x),
		static_cast<float>(this->y));
	settings::canvas->draw(this->cartoon);
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
Tools::sfmlMananger::~sfmlMananger(){
	delete[] this->filename;
}