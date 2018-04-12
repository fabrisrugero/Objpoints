#include "../Zero/option.h"
namespace Tools{
	class open : public option{
		int InDexer;
		bool opendb();
		bool IsDbImage;
		int decimalplaces;
		bool IsValidInput();
		Tools::dbTable* table;
		static const char* dbs;
		static const char* pngs;
		static const char* jpgs;
		static const char* jpegs;
		bool extMatcher(int start, int ext);
	public:
		void output(bool results = true);
		void outputIntroductions();
		open(Menu index);
		bool update();
		~open();
	};
}