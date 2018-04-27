#pragma once
#include "../Zero/option.h"
namespace Tools{
	class points : public option{
		bool IsValidInput();
	public:
		void output(bool results = true);
		void outputIntroductions();
		points(Menu index);
		void deconstruct();
		void reconstruct();
		bool update();
		~points();
	};
}