#include "../Zero/option.h"
namespace Tools{
	class history: public option{
	public:
		void output(bool results = true);
		void outputIntroductions();
		history(Menu index);
		bool IsValidInput();
		bool update();
		~history();

	private:
	};
}