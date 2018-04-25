#pragma once
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		void extractName(char* path);
		bool canvasIsCreated;
		sf::VideoMode* mode;
		sf::Sprite cartoon;
		sf::Texture tex;
		char* filename;
		int fileLenght;
		int height;
		int width;
		int x, y;
	public:
		sfmlMananger(int width, int height, char* image);
		~sfmlMananger();
		void draw();

	};
}


