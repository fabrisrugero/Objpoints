#pragma once
#include "../Zero/option.h"
namespace Tools{
	class points : public option{
		bool IsValidInput();
	public:
		void output(bool results = true);
		void outputIntroductions();
		points(Menu index);
		bool update();
		~points();
	};
}