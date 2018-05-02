#pragma once
#include "../Zero/option.h"
#include <fstream>
namespace Tools{
	struct settings : public option{
		static const int QUERY_SIZE = 300;
		void output(bool results = true);
		static const int MAX_COLUMNS = 7;
		static const int MAX_CHARS = 50;
		static int setPath(int index);
		// set the static "defaultPath" to a fullpath
		// set the static "validUserInputs" to a filename
		void outputIntroductions();
		static int maxGroupIndex;
		static char* defaultPath;
		static int defaultPaths;
		static char** groups;
		settings(Menu index);
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
		char** fullPaths;
		int* pathLenghts;
		bool* removePaths;
		bool IsValidInput();
		std::fstream* settingsFile;
		static const int MAX_PATHS = 20;
	};
}