#pragma once
#include "../Zero/option.h"
namespace Tools{
	class points : public option{
		const int setwidth = 10;
		Tools::dbTable* table;
		char colsoutput[500];
		bool IsValidInput();
		content content;
		bool IsUpdating;
		bool hasErrmsg;
		char* errmsg;
		void abort();
		int InDexer;
		int columns;
		int rows;
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