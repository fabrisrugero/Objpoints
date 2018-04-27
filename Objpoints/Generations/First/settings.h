#pragma once
#include "../Zero/option.h"
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
		static char* defaultdir;
		static char** databases;
		static char** groups;
		static int defaultdb;
		settings(Menu index);
		void deconstruct();
		void reconstruct();
		static int grps;
		static int dbs;
		bool update();
		~settings();
	private:
		bool IsValidInput();
	};
}