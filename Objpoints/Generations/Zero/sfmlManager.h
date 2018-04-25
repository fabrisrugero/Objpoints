#pragma once
#include <SFML\Graphics.hpp>
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		void extractName(char* path);
		sf::RenderWindow *canvas;
		bool canvasIsCreated;
		sf::VideoMode* mode;
		sf::Sprite cartoon;
		sf::Event *event;
		sf::Texture tex;
		bool IsVisible;
		char* filename;
		int fileLenght;
		bool update();
		bool success;
		bool draw();
		int height;
		int width;
		int x, y;
	public:
		bool reconstruct(int width, int height, char* image);
		sfmlMananger(int width, int height, char* image);
		~sfmlMananger();
		sfmlMananger();
		void loop();
	};
}


