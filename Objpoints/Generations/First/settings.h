#pragma once
#include "../Zero/option.h"
#include <fstream>
namespace Tools{
	struct settings : public option{
		static int setPath(int index, bool newPath = false);
		static const int QUERY_SIZE = 300;
		void output(bool results = true);
		static const int MAX_COLUMNS = 7;
		static const int MAX_CHARS = 50;
		static int defaultPathIndex;
		void outputIntroductions();
		static int maxGroupIndex;
		static char* defaultPath;
		static char** groups;
		settings(Menu index);
		static int rootIndex;
		void deconstruct();
		void reconstruct();
		static int Paths;
		static int grps;
		bool update();
		~settings();
	private:
		char* lines;
		int indexer;
		bool remove;
		bool success;
		bool* removePaths;
		static int inDexer;
		bool IsValidInput();
		static int* pathLenghts;
		static char** fullPaths;
		std::fstream* settingsFile;
		static const int MAX_PATHS = 20;
	};
}