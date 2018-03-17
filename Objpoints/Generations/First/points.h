#include "../Zero/option.h"
namespace Tools{
	class points : public option{
	public:
		void output(bool results = true);
		void outputIntroductions();
		points(Menu index);
		bool IsValidInput();
		bool update();
		~points();

	private:
	};
}