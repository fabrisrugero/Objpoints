#include "../Zero/option.h"
namespace Tools{
	class settings : public option{
	public:
		void output(bool results = true);
		void outputIntroductions();
		settings(Menu index);
		bool IsValidInput();
		bool update();
		~settings();

	private:
	};
}