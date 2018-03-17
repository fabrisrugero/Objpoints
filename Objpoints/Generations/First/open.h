#include "../Zero/option.h"
namespace Tools{
	class open : public option{
	public:
		void output(bool results = true);
		void outputIntroductions();
		open(Menu index);
		bool IsValidInput();
		bool update();
		~open();

	private:
	};
}