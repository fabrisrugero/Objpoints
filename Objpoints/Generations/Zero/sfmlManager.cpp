#include "sfmlManager.h"
#include <stdlib.h>
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
			this->points = this->reconstruct(this->table->select(content::current));
		if (!(this->hasErrmsg = this->table->hasErrors()) && this->points > 0){
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->table->select(this->results, pointx, this->indexer);
				this->pointsList[One][this->indexer] = atof(this->results);
				this->table->select(this->results, pointy, this->indexer);
				this->pointsList[Two][this->indexer] = atof(this->results);
				this->table->select(this->results, radius, this->indexer);
				this->pointsList[Three][this->indexer] = atof(this->results);}
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->table->select(this->results, pointz, this->indexer);
				for (this->Indexer = 0; this->results[this->Indexer] != '\0'; this->Indexer++)
					if (this->results[this->Indexer] != this->bottom_corner[this->Indexer]) break; 
				if (this->bottom_chars != this->Indexer) continue;
				this->halfOfWidth2[this->indexer] = static_cast<int>(std::round(this->pointsList[One][this->indexer] / 2));
				this->halfOfHeight2[this->indexer] = static_cast<int>(std::round(this->pointsList[Two][this->indexer] / 2)); break;}
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->pointsList[One][this->indexer] += static_cast<double>(this->halfOfWidth - this->halfOfWidth2[this->indexer]);
				this->pointsList[One][this->indexer] += static_cast<double>(this->halfOfWidth - this->halfOfWidth2[this->indexer]);
			}
		}
	}
}
int  Tools::sfmlMananger::reconstruct(int points){
	if (points == 0) return points;
	// saving changes logic to db goes here.
	for (this->indexer = 0; this->indexer < 3; this->indexer++)
		delete[] this->pointsList[this->indexer];
	for (this->indexer = 0; this->indexer < 3; this->indexer++)
		this->pointsList[this->indexer] = new double[points]();
	return points;
}
void Tools::sfmlMananger::DrawPoints(){


}
void Tools::sfmlMananger::DrawTexture(){
	this->cartoon.setPosition(static_cast<float>(this->x),
		static_cast<float>(this->y));
	this->canvas->draw(this->cartoon);
};
Tools::sfmlMananger::sfmlMananger(){
	this->points = 0;
	this->width = 939;
	this->height = 937;
	this->imageIndex = 0;
	this->x = this->y = 0;
	this->hasPoints = false;
	this->results = new char[10];
	this->event = new sf::Event();
	this->images = settings::grps;
	this->pointsList = new double*[3];
	this->filenames = new char*[images];
	this->texs = new sf::Texture[images];
	this->pointsList[0] = new double[1]();
	this->pointsList[1] = new double[1]();
	this->pointsList[1] = new double[1]();
	this->canvas = new sf::RenderWindow();
	this->bottom_corner = "bottom_corner";
	this->cartoons = new sf::Sprite[images];
	this->mode = new sf::VideoMode(this->width, this->height);
	this->tex.loadFromFile("Grid.jpg");	this->cartoon.setTexture(tex);
	this->halfOfWidth = static_cast<int>(std::round(this->width / 2));
	this->halfOfHeight = static_cast<int>(std::round(this->height / 2));
}
void Tools::sfmlMananger::GetImages(){
	this->extractName(settings::defaultPath);
	this->success = this->tex.loadFromFile(settings::defaultPath);
	if (this->success) this->cartoon.setTexture(tex);
}
void Tools::sfmlMananger::drawing(bool editable){
	this->canvas->create(*this->mode, "blankwindow");
	this->canvas->setFramerateLimit(60); this->GetImages();
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
void Tools::sfmlMananger::extractName(char* path){
	size_t dOfElemts = settings::MAX_CHARS + 100;
	size_t	dirOfElemts = settings::MAX_CHARS + 100;
	size_t	extOfElemts = settings::MAX_CHARS + 100;
	char *dir = new char[settings::MAX_CHARS + 100];
	char *ext = new char[settings::MAX_CHARS + 100];
	char * drive = new char[settings::MAX_CHARS + 100];
	this->filenames[this->imageIndex] = new char[settings::MAX_CHARS + 100]; _splitpath_s(path, drive, 
		dOfElemts, dir, dirOfElemts,this->filenames[this->imageIndex], this->maxFileLenght, ext, extOfElemts);
	delete[] dir; delete[] ext; delete[] drive;
}


