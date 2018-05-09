#pragma once
#include "dbTable.h"
#include <SFML\Graphics.hpp>
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		void extractName(char* path);
		sf::RenderWindow *canvas;
		Tools::dbTable* table;
		bool canvasIsCreated;
		sf::VideoMode* mode;
		double** pointsList;
		void DrawTexture();
		sf::Sprite cartoon;
		void DrawPoints();
		void GetPoints();
		sf::Event *event;
		sf::Texture tex;
		bool hasPoints;
		bool IsVisible;
		char* filename;
		int fileLenght;
		bool hasErrmsg;
		char* results;
		bool success;
		int indexer;
		int Indexer;
		int points;
		int height;
		int width;
		int x, y;
	public:
		bool reconstruct(int width, int height, char* image);
		sfmlMananger(int width, int height, char* image);
		~sfmlMananger();
		sfmlMananger();
		void drawing();
	};
}


