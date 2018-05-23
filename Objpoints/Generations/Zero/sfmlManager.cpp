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
	this->DrawOnTop = false;
	this->ctrlKeyPressed = false;
	this->event = new sf::Event();
	this->images = settings::grps;
	this->pointsList = new float*[3];
	this->pointsList[Three] = nullptr;
	this->pointsList[One] = nullptr;
	this->pointsList[Two] = nullptr;
	this->alternateKeyPressed = false;
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
	settings::setPath(settings::defaultPathIndex, false); this->table = new dbTable(nullptr);
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
	this->cartoons[this->images]->setPosition(this->x[this->images], this->y[this->images]);
	this->imageIndex = -1; this->sfImages[this->images]->loadFromFile("Grid.jpg");
	this->texs[this->images]->loadFromImage(*this->sfImages[this->images]);
	this->cartoons[this->images]->setTexture(*this->texs[this->images]);
}
void Tools::sfmlMananger::GetPoints(){
	if (this->databaseHits < this->QueriesToDatabase(false)){
		if (!(this->hasErrmsg = this->table->hasErrors()))
			this->points = this->reconstruct(this->QueriesToDatabase(true)); this->databaseHits++;
		if (!(this->hasErrmsg = this->table->hasErrors()) && this->points > 0) this->ProcPoints();
		else if (this->imageIndex == -1 && this->images > 0) this->imageIndex = 0; this->convertToPoints();
	}
}
void Tools::sfmlMananger::ProcPoints(){
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
		this->floater = this->pointsList[Three][this->indexer];
		this->circles[this->indexer] = new sf::CircleShape();
		this->circles[this->indexer]->setRadius(this->floater);
		this->circles[this->indexer]->setFillColor(sf::Color::Green);
		this->circles[this->indexer]->setOrigin(this->floater, this->floater);
		this->circles[this->indexer]->setPosition(this->pointsList[One][this->indexer], this->pointsList[Two][this->indexer]);}
	this->cartoons[this->imageIndex]->setPosition(this->x[this->imageIndex], this->y[this->imageIndex]);
}
void Tools::sfmlMananger::DrawImages(){
	this->canvas->draw(*this->cartoons[this->images]);
	if (this->DrawOnTop) this->DrawImageTop();
	else if (!this->DrawOnTop) this->DrawImageBottom();
};
void Tools::sfmlMananger::InitPoints(){
	if (!(this->hasErrmsg = this->table->hasErrors()))
		this->points = this->reconstruct(this->table->select(content::current));
	if (!(this->hasErrmsg = this->table->hasErrors()) && this->points > 0) this->ProcPoints();
	else if (this->imageIndex == -1 && this->images > 0) this->imageIndex = 0; this->convertToPoints();
}
void Tools::sfmlMananger::centerImage(){
	if (this->ImageMissing[this->imageIndex]) this->halfOfWidth2[this->imageIndex] = this->widthOfMissing;
	else this->halfOfWidth2[this->imageIndex] = static_cast<int>(std::round(this->pointsList[One][this->indexer] / 2));
	if (this->ImageMissing[this->imageIndex]) this->halfOfHeight2[this->imageIndex] = this->heightOfMissing;
	else this->halfOfHeight2[this->imageIndex] = static_cast<int>(std::round(this->pointsList[Two][this->indexer] / 2));
	this->y[this->imageIndex] = static_cast<float>(this->halfOfHeight - this->halfOfHeight2[this->imageIndex]);
	this->x[this->imageIndex] = static_cast<float>(this->halfOfWidth - this->halfOfWidth2[this->imageIndex]);
}
void Tools::sfmlMananger::DrawImageTop(){
	for (this->indexer = 0; this->indexer < this->points; this->indexer++)
		this->canvas->draw(*this->circles[this->indexer]);
	if (this->images != 0 && this->imageIndex >= 0)
		this->canvas->draw(*this->cartoons[this->imageIndex]);
}
void Tools::sfmlMananger::convertToPoints(){
	for (this->indexer = 0; this->indexer < this->points; this->indexer++){
		if (this->pointsList[Three][this->indexer] >= this->minRadius) continue;
		this->circles[this->indexer]->setOrigin(this->minRadius, this->minRadius);
		this->circles[this->indexer]->setFillColor(sf::Color::Red);
		this->circles[this->indexer]->setRadius(this->minRadius);
	}
}
void Tools::sfmlMananger::DrawImageBottom(){
	if (this->images != 0 && this->imageIndex >= 0)
		this->canvas->draw(*this->cartoons[this->imageIndex]);
	for (this->indexer = 0; this->indexer < this->points; this->indexer++)
		this->canvas->draw(*this->circles[this->indexer]);
}
void Tools::sfmlMananger::controlKeystate(){
	if (!this->alternateKeyPressed && this->keyPressed(controlKey)){
		this->ctrlKeyPressed = !this->ctrlKeyPressed; if (this->imageIndex < 0) return;
		if (this->ctrlKeyPressed) this->endChar = '\0'; else this->endChar = '*';
		this->updateTitles(controlKey); this->canvas->setTitle(this->filenames[this->imageIndex]);
	}
}
void Tools::sfmlMananger::alternateKeystate(){
	if (!this->ctrlKeyPressed && this->keyPressed(alternateKey)){
		this->alternateKeyPressed = !this->alternateKeyPressed; if (this->imageIndex < 0) return;
		if (this->alternateKeyPressed) this->endChar = '\0'; else this->endChar = '-';
		this->updateTitles(alternateKey); this->canvas->setTitle(this->filenames[this->imageIndex]);
	}
}
void Tools::sfmlMananger::drawing(bool editable){
	this->canvas->create(*this->mode, "loading..");
	this->canvas->setFramerateLimit(60); 
	this->GetImages(); this->InitPoints();
	while (this->canvas->isOpen()){ this->canvas->clear();
		 while (this->canvas->pollEvent(*this->event))
			 if (this->event->type == sf::Event::Closed)
				 this->canvas->close();
		this->GetPoints();
		this->DrawImages();
		this->controlKeystate();
		this->alternateKeystate();
		this->pointsNavigatorNsizer();
		this->pointsmovementcontroler();
		this->canvas->display();
	}
}
void Tools::sfmlMananger::pointsNavigatorNsizer(){
	if (!this->ctrlKeyPressed && !alternateKeyPressed){
		if (this->keysPressed[rightArrowKey]){
		}
		else if (this->keysPressed[leftArrowKey]){

		}
		else if (this->keysPressed[downArrowKey]){
		}
		else if (this->keysPressed[upArrowKey]){

		}
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
	case Tools::alternateKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)
			&& this->keysPressed[alternateKey]) return this->keysPressed[alternateKey] = false;
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
			&& !this->keysPressed[alternateKey]) return this->keysPressed[alternateKey] = true; break;
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
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			&& this->keysPressed[upArrowKey]) return this->keysPressed[upArrowKey] = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			&& !this->keysPressed[upArrowKey])return this->keysPressed[upArrowKey] = true; break;
	case Tools::leftArrowKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			&& this->keysPressed[leftArrowKey]) return this->keysPressed[leftArrowKey] = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			&& !this->keysPressed[leftArrowKey])return this->keysPressed[leftArrowKey] = true;break;
	case Tools::downArrowKey:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			&& this->keysPressed[downArrowKey]) return this->keysPressed[downArrowKey] = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			&& !this->keysPressed[downArrowKey])return this->keysPressed[downArrowKey] = true; break;
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
void Tools::sfmlMananger::pointsmovementcontroler(){
	if (!this->ctrlKeyPressed && alternateKeyPressed){
		if (this->keysPressed[rightArrowKey]){
		}
		else if (this->keysPressed[leftArrowKey]){

		}
		else if (this->keysPressed[downArrowKey]){
		}
		else if (this->keysPressed[upArrowKey]){

		}
	}
}
void Tools::sfmlMananger::updateTitles(keyboard key){
	for (this->indexer = 0; this->indexer < this->images; this->indexer++){
		for (this->inDexer = 0; this->filenames[this->indexer][this->inDexer] != this->endChar; this->inDexer++) continue;
		if (key == controlKey && this->ctrlKeyPressed) this->filenames[this->indexer][this->inDexer] = '*';
		else if (key == controlKey && !this->ctrlKeyPressed) this->filenames[this->indexer][this->inDexer] = '\0';
		else if (key == alternateKey && this->alternateKeyPressed) this->filenames[this->indexer][this->inDexer] = '-';
		else if (key == alternateKey && !this->alternateKeyPressed) this->filenames[this->indexer][this->inDexer] = '\0';
	}
}
int Tools::sfmlMananger::QueriesToDatabase(bool query) {
	if (!query){
		if (this->databaseHits == this->ctrlKeyHits && (
			(this->ctrlKeyPressed && this->keyPressed(enterKey)) ||
			(this->ctrlKeyPressed && this->keyPressed(rightArrowKey)) ||
			(this->ctrlKeyPressed && this->keyPressed(leftArrowKey))))
			return ++this->ctrlKeyHits;
		else if (this->ctrlKeyPressed && 
			(this->keyPressed(upArrowKey) 
			|| this->keyPressed(downArrowKey)))
		this->DrawOnTop = !this->DrawOnTop;
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


