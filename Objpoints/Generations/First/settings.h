#pragma once
#include <SFML\Graphics.hpp>
#include "../Zero/option.h"
namespace Tools{
	struct settings : public option{
		static bool setPath(int index, char* output);// set the output to valid database
		static void canvasVisible(bool state);
		static const int QUERY_SIZE = 300;
		void output(bool results = true);
		static const int MAX_COLUMNS = 7;
		static const int MAX_CHARS = 50;
		static sf::RenderWindow *canvas;
		static int setPath(int index);// set the static "validuserinputs" to valid database
		static bool IscanvasVisible();
		void outputIntroductions();
		static int maxGroupIndex;
		static char* defaultdir;
		static char** databases;
		static char** groups;
		static int defaultdb;
		settings(Menu index);
		static int grps;
		static int dbs;
		bool update();
		~settings();
	private:
		bool IsValidInput();
		static bool canvasIsVisible;
	};
}