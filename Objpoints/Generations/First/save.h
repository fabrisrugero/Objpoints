#include "../Zero/option.h"
namespace Tools{
	class save : public option{
	public:
		void output(bool results = true);
		void outputIntroductions();
		save(Menu index);
		bool IsValidInput();
		bool update();
		~save();

	private:
	};
}
