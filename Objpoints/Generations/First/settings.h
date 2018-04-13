#pragma once
#include "../Zero/option.h"
namespace Tools{
	struct settings : public option{
		static const int QUERY_SIZE = 300;
		void output(bool results = true);
		static const int MAX_COLUMNS = 7;
		static const int MAX_CHARS = 50;
		static bool setPath(int index);
		void outputIntroductions();
		static int maxGroupIndex;
		static char* defaultdir;
		static char** dbPaths;
		static char** groups;
		static int defaultdb;
		settings(Menu index);
		static int dbs;
		bool update();
		~settings();
	private:
		bool IsValidInput();
	};
}