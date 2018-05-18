#include <stdlib.h>
#include "sfmlManager.h"

void Tools::sfmlMananger::imgdex(){
	for (this->Indexer = 0; this->Indexer < settings::grps; this->Indexer++){
		for (this->inDexer = 0; this->results[this->inDexer] != '\0'; this->inDexer++)
		{if (settings::groups[this->Indexer][this->inDexer] != this->results[this->inDexer]) break;}
		if (this->results[this->inDexer] == '\0') { this->imageIndex = this->Indexer; break; } else this->imageIndex = -1;
	}	if (this->imageIndex >= 0) this->canvas->setTitle(this->filenames[this->imageIndex]);
}
Tools::sfmlMananger::sfmlMananger(){
	this->points = 0;
	this->imageIndex = 0;
	this->endChar = '\0';
	this->ctrlKeyHits = 0;
	this->databaseHits = 0;
	this->circles = nullptr;
	this->ctrlKeyPressed = false;
	this->event = new sf::Event();
	this->images = settings::grps;
	this->pointsList = new float*[3];
	this->pointsList[Three] = nullptr;
	this->pointsList[One] = nullptr;
	this->pointsList[Two] = nullptr;
	this->canvas = new sf::RenderWindow();
	this->bottom_corner = "bottom_corner";
	this->x = new float[this->images + 1]();
	this->y = new float[this->images + 1]();
	this->ImageMissing = new bool[images]();
	this->filenames = new char*[this->images];
	this->keysPressed = new bool[relevateKeys]();
	this->results = new char[settings::MAX_CHARS];
	this->texs = new sf::Texture*[this->images + 1];
	this->halfOfWidth2 = new int[this->images + 1]();
	this->halfOfHeight2 = new int[this->images + 1]();
	this->sfImages = new sf::Image*[this->images + 1];
	this->cartoons = new sf::Sprite*[this->images + 1];
	this->mode = new sf::VideoMode(this->width, this->height);
	this->halfOfWidth = static_cast<int>(std::round(this->width / 2));
	this->halfOfHeight = static_cast<int>(std::round(this->height / 2));
	for (this->inDexer = 0; this->inDexer < this->images; this->inDexer++)
	{this->texs[this->inDexer] = new sf::Texture();this->sfImages[this->inDexer] = new sf::Image();this->cartoons[this->inDexer] = new sf::Sprite();}
	this->texs[this->images] = new sf::Texture(); this->cartoons[this->images] = new sf::Sprite(); this->sfImages[this->images] = new sf::Image();
}
Tools::sfmlMananger::~sfmlMananger(){
	for (this->indexer = 0; this->indexer < this->images; this->indexer++) delete this->sfImages[this->indexer]; delete this->sfImages[this->indexer];
	for (this->indexer = 0; this->indexer < this->images; this->indexer++) delete this->cartoons[this->indexer]; delete this->cartoons[this->indexer];
	for (this->indexer = 0; this->indexer < this->images; this->indexer++) delete this->texs[this->indexer]; delete this->texs[this->indexer];
	for (this->indexer = 0; this->indexer < this->images; this->indexer++) delete[] this->filenames[this->indexer];
	for (this->indexer = 0; this->indexer < this->points; this->indexer++) delete this->circles[this->indexer];
	for (this->indexer = 0; this->indexer < 3; this->indexer++) delete[] this->pointsList[this->indexer];
	if (this->images > 0) delete[] this->ImageMissing;
	if (this->points > 0) delete[] this->circles; 
	delete[] this->halfOfHeight2;
	delete[] this->halfOfWidth2;
	delete[] this->pointsList;
	delete[] this->filenames;
	delete[] this->sfImages;
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
		if (settings::setPath(settings::defaultPathIndex + this->imageIndex + 1) > 0
			&& !this->sfImages[this->imageIndex]->loadFromFile(settings::defaultPath))
			this->ImageMissing[this->imageIndex] = this->sfImages[this->imageIndex]->loadFromFile("missing.png");
		this->texs[this->imageIndex]->loadFromImage(*this->sfImages[this->imageIndex]);
		this->cartoons[this->imageIndex]->setTexture(*this->texs[this->imageIndex]);
		this->extractName(settings::defaultPath);} 
	this->imageIndex = -1; this->sfImages[this->images]->loadFromFile("Grid.jpg");
	this->texs[this->images]->loadFromImage(*this->sfImages[this->images]);
	this->cartoons[this->images]->setTexture(*this->texs[this->images]);
}
void Tools::sfmlMananger::GetPoints(){
	if (this->databaseHits < this->fetchFromDatabase(false)){
		if (this->table == nullptr && settings::setPath(settings::defaultPathIndex, false) > 0 ) 
			this->table = new dbTable(nullptr); 
		if (this->table != nullptr && !(this->hasErrmsg = this->table->hasErrors()))
			this->points = this->reconstruct(this->fetchFromDatabase(true)); this->databaseHits++;
	if (this->table != nullptr && !(this->hasErrmsg = this->table->hasErrors()) && this->points > 0){
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
			this->table->select(this->results, objectz, One);
			this->imgdex(); this->centerImage(); break;}
		for (this->indexer = 0; this->indexer < this->points; this->indexer++){
			this->pointsList[One][this->indexer] += static_cast<float>(this->x[this->imageIndex]);
			this->pointsList[Two][this->indexer] += static_cast<float>(this->y[this->imageIndex]);}
		for (this->indexer = 0; this->indexer < this->points; this->indexer++){
			this->circles[this->indexer] = new sf::CircleShape();
			this->floater = this->pointsList[Three][this->indexer];
			this->circles[this->indexer]->setRadius(this->floater);
			this->circles[this->indexer]->setFillColor(sf::Color::Green);
			this->circles[this->indexer]->setOrigin(this->floater, this->floater);
			this->circles[this->indexer]->setPosition(this->pointsList[One][this->indexer], this->pointsList[Two][this->indexer]);}}
	else if (this->imageIndex == -1 && this->images > 0) this->imageIndex = 0;}
}
void Tools::sfmlMananger::DrawImages(){
	this->cartoons[this->images]->setPosition(
		this->x[this->images], this->y[this->images]);	
	this->canvas->draw(*this->cartoons[this->images]);
	if (this->images != 0 && this->imageIndex >= 0){
		this->cartoons[this->imageIndex]->setPosition(
			this->x[this->imageIndex], this->y[this->imageIndex]);
		this->canvas->draw(*this->cartoons[this->imageIndex]);}
	for (this->indexer = 0; this->indexer < this->points; this->indexer++)
		this->canvas->draw(*this->circles[this->indexer]);
};
void Tools::sfmlMananger::centerImage(){
	if (this->ImageMissing[this->imageIndex]) this->halfOfWidth2[this->imageIndex] = this->widthOfMissing;
	else this->halfOfWidth2[this->imageIndex] = static_cast<int>(std::round(this->pointsList[One][this->indexer] / 2));
	if (this->ImageMissing[this->imageIndex]) this->halfOfHeight2[this->imageIndex] = this->heightOfMissing;
	else this->halfOfHeight2[this->imageIndex] = static_cast<int>(std::round(this->pointsList[Two][this->indexer] / 2));
	this->y[this->imageIndex] = static_cast<float>(this->halfOfHeight - this->halfOfHeight2[this->imageIndex]);
	this->x[this->imageIndex] = static_cast<float>(this->halfOfWidth - this->halfOfWidth2[this->imageIndex]);
}
void Tools::sfmlMananger::ModifyPoint(){
	if (this->keyPressed(controlKey) ){
		this->ctrlKeyPressed = !this->ctrlKeyPressed; if (this->imageIndex < 0) return;
		if (this->ctrlKeyPressed) this->endChar = '\0'; else this->endChar = '*';
		for (this->indexer = 0; this->indexer < this->images; this->indexer++){
			for (this->inDexer = 0; this->filenames[this->indexer][this->inDexer] != this->endChar; this->inDexer++) continue;
			if (this->ctrlKeyPressed) this->filenames[this->indexer][this->inDexer] = '*';
			else this->filenames[this->indexer][this->inDexer] = '\0';}
		this->canvas->setTitle(this->filenames[this->imageIndex]);
	}




}
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
	char* filename = new char[settings::MAX_CHARS + 101];
	this->filenames[this->imageIndex] = new char[settings::MAX_CHARS + 101]; _splitpath_s(path,
		drive, dOfElemts, dir, dirOfElemts, filename, this->maxFileLenght, ext, extOfElemts);
	for (this->indexer = 0; filename[this->indexer] != '\0'; this->indexer++)
		this->filenames[this->imageIndex][this->indexer] = filename[this->indexer];
	this->filenames[this->imageIndex][this->indexer] = filename[this->indexer];
	delete[] dir; delete[] ext; delete[] drive; delete[] filename;
	this->filenames[this->imageIndex][this->indexer + 1] = '\0';
}
bool Tools::sfmlMananger::keyPressed(keyboard Key){
	switch (Key){
	case Tools::noKey:
		break;
	case Tools::altKey:
		break;
	case Tools::enterKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
			&& this->keysPressed[enterKey]) 
			return this->keysPressed[enterKey] = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) 
			&& !this->keysPressed[enterKey])
			return this->keysPressed[enterKey] = true; break;
	case Tools::controlKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)
			&& this->keysPressed[controlKey]) return this->keysPressed[controlKey] = false;
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
			&& !this->keysPressed[controlKey]) return this->keysPressed[controlKey] = true; break;
	case Tools::upArrowKey:
		break;
	case Tools::leftArrowKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			&& this->keysPressed[leftArrowKey]) return this->keysPressed[leftArrowKey] = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			&& !this->keysPressed[leftArrowKey])return this->keysPressed[leftArrowKey] = true;break;
	case Tools::downArrowKey:
		break;
	case Tools::rightArrowKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			&& this->keysPressed[rightArrowKey]) return this->keysPressed[rightArrowKey] = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			&& !this->keysPressed[rightArrowKey])return this->keysPressed[rightArrowKey] = true; break;
	default:
		break;
	}
	return false;
}
int Tools::sfmlMananger::fetchFromDatabase(bool query) {
	if (!query){
		if (this->databaseHits == this->ctrlKeyHits && (
			(this->ctrlKeyPressed && this->keyPressed(enterKey)) ||
			(this->ctrlKeyPressed && this->keyPressed(rightArrowKey)) ||
			(this->ctrlKeyPressed && this->keyPressed(leftArrowKey))))
			return ++this->ctrlKeyHits;
	}
	else{
		if (this->ctrlKeyPressed && this->keysPressed[enterKey])
			return this->table->select(content::current);
		else if (this->ctrlKeyPressed && this->keysPressed[rightArrowKey])
			return this->table->select(content::next);
		else if (this->ctrlKeyPressed && this->keysPressed[leftArrowKey])
			return this->table->select(content::previous);
	} return 0;
}


