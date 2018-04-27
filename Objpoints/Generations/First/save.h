#pragma once
#include "../Zero/option.h"
namespace Tools{
	class save : public option{
		bool IsValidInput();
	public:
		void output(bool results = true);
		void outputIntroductions();
		void deconstruct();
		void reconstruct();
		save(Menu index);
		bool update();
		~save();
	};
}
