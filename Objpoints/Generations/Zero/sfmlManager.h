#pragma once
#include "dbTable.h"
#include <SFML\Graphics.hpp>
#include "../First/settings.h"
namespace Tools{
	class sfmlMananger{
		int QueriesToDatabase(bool query);
		bool keyPressed(keyboard Key);
		const int maxFileLenght = 150;
		const int widthOfMissing = 315;
		const int heightOfMissing = 184;
		void extractName(char* path);
		const int bottom_chars = 13;
		int reconstruct(int points);
		const char* bottom_corner;
		sf::CircleShape **circles;
		sf::RenderWindow *canvas;
		const int height = 937;
		const int width = 939;
		char endChar;
		int NavElaspedTicks;
		int MovElaspedTicks;
		float incriment;
		const float augmentor = 0.1f;
		const int slowdown = 10;
		void convertToPoints();
		int pointIndex;
		const float minRadius = 3.0f;
		void controlKeystate();
		void alternateKeystate();
		void pointsmovementcontroler();
		void pointsNavigatorNsizer();
		Tools::dbTable* table;
		sf::Image** sfImages;
		sf::Sprite** cartoons;
		bool canvasIsCreated;
		sf::VideoMode* mode;
		bool ctrlKeyPressed;
		bool alternateKeyPressed;
		bool* keysPressed;
		bool DrawOnTop;
		const char* missing;
		const char* Grid;
		void DrawImageTop();
		void DrawImageBottom();
		void updateTitles(keyboard key);
		float** pointsList;
		int* halfOfHeight2;
		void centerImage();
		sf::Texture** texs;
		int* halfOfWidth2;
		int databaseHits;
		int ctrlKeyHits;
		bool* ImageMissing;
		void DrawImages();
		char** filenames;
		void InitPoints();
		void GetPoints();
		void ProcPoints();
		void GetImages();
		sf::Event *event;
		int halfOfHeight;
		int halfOfWidth;
		int imageIndex;
		bool hasErrmsg;
		char* results;
		void imgdex();
		float floater;
		float floAter;
		float Floater;
		bool success;
		float *x, *y;
		int inDexer;
		int indexer;
		int Indexer;
		int points;
		int images;

	public:
		void drawing(bool editable);
		~sfmlMananger();
		sfmlMananger();
	};
}


