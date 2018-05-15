#pragma once
#include "dbTable.h"
#include <SFML\Graphics.hpp>
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		const int maxFileLenght = 150;
		void extractName(char* path);
		const int bottom_chars = 13;
		int reconstruct(int points);
		const char* bottom_corner;
		sf::CircleShape **circles;
		sf::RenderWindow *canvas;
		Tools::dbTable* table;
		sf::Sprite* cartoons;
		bool canvasIsCreated;
		sf::VideoMode* mode;
		float** pointsList;
		int* halfOfHeight2;
		void ModifyPoint();
		void centerImage();
		void DrawImages();
		sf::Texture* texs;
		int* halfOfWidth2;
		char** filenames;
		void GetPoints();
		void GetImages();
		sf::Event *event;
		int halfOfHeight;
		int halfOfWidth;
		bool hasPoints;
		int imageIndex;
		bool hasErrmsg;
		char* results;
		void imgdex();
		float floater;
		bool success;
		float *x, *y;
		int inDexer;
		int indexer;
		int Indexer;
		int points;
		int height;
		int images;
		int width;
	public:
		void drawing(bool editable);
		~sfmlMananger();
		sfmlMananger();
	};
}


