#pragma once
#include "../Zero/option.h"
namespace Tools{
	class save : public option{
		bool IsValidInput();
	public:
		void output(bool results = true);
		void outputIntroductions();
		save(Menu index);
		bool update();
		~save();
	};
}
