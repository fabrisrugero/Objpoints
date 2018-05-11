#pragma once
#include "dbTable.h"
#include <SFML\Graphics.hpp>
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		double centerycoord(double y, int height);
		double centerxcoord(double x, int width);
		const int maxFileLenght = 150;
		void extractName(char* path);
		const int bottom_chars = 13;
		int reconstruct(int points);
		const char* bottom_corner;
		sf::RenderWindow *canvas;
		Tools::dbTable* table;
		sf::Sprite* cartoons;
		bool canvasIsCreated;
		sf::VideoMode* mode;
		double** pointsList;
		int* halfOfHeight2;
		void DrawImages();
		void DrawPoints();
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
		bool success;
		float *x, *y;
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


