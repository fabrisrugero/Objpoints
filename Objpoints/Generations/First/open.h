#pragma once
#include "../Zero/sfmlManager.h"
#include "../Zero/option.h"
namespace Tools{
	class open : public option{
		int InDexer;
		int indeXer;
		void abort();
		char* errmsg;
		bool opendb();
		bool IsDbImage;
		bool hasErrmsg;
		int decimalplaces;
		bool IsValidInput();
		char colsoutput[500];
		Tools::dbTable* table;
		static const char* dbs;
		const int setwidth = 10;
		static const char* pngs;
		static const char* jpgs;
		static const char* jpegs;
		bool extMatcher(int start, int ext);
	public:
		void output(bool results = true);
		void outputIntroductions();
		open(Menu index);
		bool update();
		~open();
	};
}