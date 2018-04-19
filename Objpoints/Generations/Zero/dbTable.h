#pragma once
#include "../../Enums/enums.h"
#include "../../Lib/query.h"
#include "../../Lib/sqlite3.h"
namespace Tools{
	class dbTable{
		sqlite3 *db;
		int indexer;
		int Indexer;
		int indeXer;
		int inDexer;
		int* widths;
		int columns;
		char* errors;
		char* database;
		int groupIndex;
		const char** cols;
		const char* table;
		void initcolumns();
		const char* errmsg;
		Tools::query* query;
		char* querystatement;
		const int lenght = 14;
		const char* sqlcommand;
		bool select(int content);
		Tools::query* handlErrors();
		int IsEqual(const char *a, const char *b);
	public:
		~dbTable();
		bool connectedTo(char* db);
		bool hasErrors(char* arr = nullptr);
		Tools::query* select(content content);
		int initcolumns(char* output, int setwidth);
		dbTable(char* db, int end = 0, int str = 0);
		void where(Tools::columns column, const char* value);
	};
}