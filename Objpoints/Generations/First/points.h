#pragma once
#include <thread>
#include "../Zero/option.h"
#include "../Zero/sfmlManager.h"
namespace Tools{
	class points : public option{
		Tools::sfmlMananger* window;
		const int setwidth = 10;
		Tools::dbTable* table;
		char colsoutput[500];
		bool IsValidInput();
		std::thread* editor;
		bool editorIsOpen;
		bool issueWarning;
		content content;
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