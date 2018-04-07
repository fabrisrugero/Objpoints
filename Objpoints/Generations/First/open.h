#include "../Zero/option.h"
namespace Tools{
	class open : public option{
	public:
		void output(bool results = true);
		void outputIntroductions();
		bool IsValidInput();
		open(Menu index);
		bool update();
		~open();

	private:
		int InDexer;
		bool dbOrImage;
		int decimalplaces;
		static const char* dbs;
		static const char* pngs;
		static const char* jpgs;
		static const char* jpegs;
		bool extMatcher(int start, int ext);
	};
}