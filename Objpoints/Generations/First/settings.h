#include "../Zero/option.h"
namespace Tools{
	struct settings : public option{
		void output(bool results = true);
		static bool setPath(int index);
		void outputIntroductions();
		static char* defaultdir;
		static char** dbPaths;
		static char** objects;
		static int defaultdb;
		settings(Menu index);
		static int dbs;
		bool update();
		~settings();
	private:
		bool IsValidInput();
	};
}