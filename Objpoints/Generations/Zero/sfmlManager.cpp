#include <stdlib.h>
#include "sfmlManager.h"
Tools::sfmlMananger::sfmlMananger(){
	this->points = 0;
	this->width = 939;
	this->height = 937;
	this->imageIndex = 0;
	this->hasPoints = false;
	this->circles = nullptr;
	this->results = new char[15];
	this->event = new sf::Event();
	this->images = settings::grps;
	this->pointsList = new float*[3];
	this->pointsList[One] = nullptr;
	this->pointsList[Two] = nullptr;
	this->pointsList[Three] = nullptr;
	this->canvas = new sf::RenderWindow();
	this->bottom_corner = "bottom_corner";
	this->x = new float[this->images + 1]();
	this->y = new float[this->images + 1]();
	this->filenames = new char*[this->images];
	this->texs = new sf::Texture[this->images + 1];
	this->cartoons = new sf::Sprite[this->images + 1];
	this->mode = new sf::VideoMode(this->width, this->height);
	this->halfOfWidth = static_cast<int>(std::round(this->width / 2));
	this->halfOfHeight = static_cast<int>(std::round(this->height / 2));
}
Tools::sfmlMananger::~sfmlMananger(){
	for (this->indexer = 0; this->indexer < this->images; this->indexer++)
		delete[] this->filenames[this->indexer];
	for (this->indexer = 0; this->indexer < 3; this->indexer++)
		delete[] this->pointsList[this->indexer];
	delete[] this->halfOfHeight2;
	delete[] this->halfOfWidth2;
	delete[] this->pointsList;
	delete[] this->filenames;
	delete[] this->cartoons;
	delete[] this->results;
	delete[] this->texs;
	delete this->canvas;
	delete this->event;
	delete this->mode;
	delete[] this->y;
	delete[] this->x;
}
void Tools::sfmlMananger::GetImages(){
	for (this->imageIndex = 0; this->imageIndex < this->images; this->imageIndex++){
		if (settings::setPath(settings::defaultPathIndex) > 0 &&
			!this->texs[this->imageIndex].loadFromFile(settings::defaultPath))
			this->texs[this->imageIndex].loadFromFile("missing.png");
		this->cartoons[this->imageIndex].setTexture(this->texs[this->imageIndex]); 
		this->Indexer = this->halfOfHeight - this->halfOfHeight2[this->imageIndex];
		this->indexer = this->halfOfWidth - this->halfOfWidth2[this->imageIndex];
		this->x[this->imageIndex] += static_cast<float>(this->indexer);
		this->y[this->imageIndex] += static_cast<float>(this->Indexer);
		this->extractName(settings::defaultPath);}
	this->texs[this->images].loadFromFile("Grid.jpg");
	this->cartoons[this->images].setTexture(this->texs[this->images]);
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
				this->pointsList[One][this->indexer] = strtof(this->results, nullptr);
				this->table->select(this->results, pointy, this->indexer);
				this->pointsList[Two][this->indexer] = strtof(this->results, nullptr);
				this->table->select(this->results, radius, this->indexer);
				this->pointsList[Three][this->indexer] = strtof(this->results, nullptr);}
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->table->select(this->results, pointz, this->indexer);
				for (this->Indexer = 0; this->results[this->Indexer] != '\0'; this->Indexer++)
					if (this->results[this->Indexer] != this->bottom_corner[this->Indexer]) break; 
				if (this->bottom_chars != this->Indexer) continue;
				this->halfOfWidth2[this->indexer] = static_cast<int>(std::round(this->pointsList[One][this->indexer] / 2));
				this->halfOfHeight2[this->indexer] = static_cast<int>(std::round(this->pointsList[Two][this->indexer] / 2)); break;}
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->pointsList[One][this->indexer] += static_cast<float>(this->halfOfWidth - this->halfOfWidth2[this->indexer]);
				this->pointsList[Two][this->indexer] += static_cast<float>(this->halfOfHeight - this->halfOfHeight2[this->indexer]);}
			for (this->indexer = 0; this->indexer < this->points; this->indexer++){
				this->circles[this->indexer]->setPosition(this->pointsList[One][this->indexer], this->pointsList[Two][this->indexer]);
				this->circles[this->indexer]->setRadius(this->pointsList[Three][this->indexer] > 0 ? this->pointsList[Three][this->indexer] : 1);
				this->circles[this->indexer]->setFillColor(sf::Color::Green);}
			 this->table->select(this->results, objectz, 0);
			for (this->Indexer = 0; this->Indexer < settings::grps; this->Indexer++){
				for (this->indexer = 0; this->results[this->indexer] != '\0'; this->indexer++)
					if (settings::groups[this->Indexer][this->indexer] != this->results[this->indexer]) break;
				if (this->results[this->indexer] == '\0') this->imageIndex = this->Indexer; else this->imageIndex = -1;}
			if (this->imageIndex >= 0) this->canvas->setTitle(this->filenames[this->imageIndex]);
		}
	}
}
void Tools::sfmlMananger::ModifyPoint(){

}
void Tools::sfmlMananger::DrawImages(){
	this->cartoons[this->images].setPosition(
		this->x[this->images], this->y[this->images]);	
	this->canvas->draw(this->cartoons[this->images]);
	if (this->images != 0 && this->imageIndex >= 0){
		this->cartoons[this->imageIndex].setPosition(
			this->x[this->imageIndex], this->y[this->imageIndex]);
		this->canvas->draw(this->cartoons[this->imageIndex]);}
	for (this->indexer = 0; this->indexer < this->points; this->indexer++)
		this->canvas->draw(*this->circles[this->indexer]);
};
void Tools::sfmlMananger::drawing(bool editable){
	this->canvas->create(*this->mode, "blankwindow");
	this->canvas->setFramerateLimit(60); this->GetImages();
	while (this->canvas->isOpen()){ this->canvas->clear();
		 while (this->canvas->pollEvent(*this->event))
			 if (this->event->type == sf::Event::Closed)
				 this->canvas->close();		
		this->GetPoints();
		this->DrawImages();
		this->ModifyPoint();
		this->canvas->display();
	}
}
int  Tools::sfmlMananger::reconstruct(int points){
	// saving changes logic to db goes here.
	for (this->indexer = 0; this->indexer < Four && this->points > 0; this->indexer++)
	{delete[] this->pointsList[this->indexer]; this->pointsList[this->indexer] = nullptr;}
	for (this->indexer = 0; this->indexer < this->points; this->indexer++) delete this->circles[this->indexer];
	if (this->points > 0) { delete[] this->circles; this->circles = nullptr; } if (points == 0) return points;
	for (this->indexer = 0; this->indexer < Four; this->indexer++)
		this->pointsList[this->indexer] = new float[points]();
	this->circles = new sf::CircleShape*[points]; 
	return points;
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


