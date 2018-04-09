#include "../Zero/option.h"
namespace Tools{
	struct settings : public option{
		void output(bool results = true);
		static bool setPath(int index);
		void outputIntroductions();
		settings(Menu index);
		static char* dbPaths;
		static int defaultdb;
		static int dbs;
		bool update();
		~settings();
	private:
		bool IsValidInput();
	};
}