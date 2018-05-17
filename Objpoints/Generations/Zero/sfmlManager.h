#pragma once
#include "dbTable.h"
#include <SFML\Graphics.hpp>
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		int fetchFromDatabase(bool query);
		bool keyPressed(keyboard Key);
		const int maxFileLenght = 150;
		void extractName(char* path);
		const int bottom_chars = 13;
		int reconstruct(int points);
		const char* bottom_corner;
		sf::CircleShape **circles;
		sf::RenderWindow *canvas;
		Tools::dbTable* table;
		sf::Image** sfImages;
		sf::Sprite** cartoons;
		bool canvasIsCreated;
		sf::VideoMode* mode;
		bool ctrlKeyPressed;
		bool* keysPressed;
		float** pointsList;
		int* halfOfHeight2;
		void ModifyPoint();
		void centerImage();
		sf::Texture** texs;
		int* halfOfWidth2;
		int databaseHits;
		int ctrlKeyHits;
		void DrawImages();
		char** filenames;
		void GetPoints();
		void GetImages();
		sf::Event *event;
		int halfOfHeight;
		int halfOfWidth;
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


