#pragma once
#include "../Zero/option.h"
namespace Tools{
	class history: public option{
		bool IsValidInput();
	public:
		void output(bool results = true);
		void outputIntroductions();
		history(Menu index);
		void deconstruct();
		void reconstruct();
		bool update();
		~history();
	};
}