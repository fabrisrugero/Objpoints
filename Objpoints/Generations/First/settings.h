#pragma once
#include "../Zero/option.h"
#include <fstream>
namespace Tools{
	struct settings : public option{
		static bool setPath(int index, char* output);// set the output to valid database
		static const int QUERY_SIZE = 300;
		void output(bool results = true);
		static const int MAX_COLUMNS = 7;
		static const int MAX_CHARS = 50;
		static int setPath(int index);// set the static "validuserinputs" to valid database
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
		char** fullPaths;
		int* pathLenghts;
		bool IsValidInput();
		std::ifstream* file;
		static const int MAX_PATHS = 20;
	};
}