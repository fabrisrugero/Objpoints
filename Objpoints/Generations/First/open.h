#pragma once
#include "../Zero/sfmlManager.h"
#include "../Zero/option.h"
#include <thread>
namespace Tools{
	class open : public option{
		int InDexer;
		int indeXer;
		void abort();
		char* errmsg;
		bool opendb();
		bool IsDbImage;
		bool hasErrmsg;
		bool IsNewPath;
		int decimalplaces;
		bool threadIsBusy;
		bool IsValidInput();
		std::thread* thread;
		sfmlMananger* window;
		char colsoutput[500];
		Tools::dbTable* table;
		char* validUserInputs;
		static const char* dbs;
		const int setwidth = 10;
		static const char* pngs;
		static const char* jpgs;
		static const char* jpegs;
		bool extMatcher(int start, int ext);
	public:
		void output(bool results = true);
		void outputIntroductions();
		void deconstruct();
		void reconstruct();
		open(Menu index);
		bool conected;
		bool update();
		~open();
	};
}