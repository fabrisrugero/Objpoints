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
		int handlErrors();
		Tools::query* query;
		char* querystatement;
		const int lenght = 14;
		const char* sqlcommand;
		void select(int content);
		bool IsEqual(const char *a, const char *b);
	public:
		~dbTable();
		bool *ignoredcolumns;
		bool connectedTo(char* db);
		int select(content content);
		bool hasErrors(char* arr = nullptr);
		int initcolumns(char* output, int setwidth);
		dbTable(char* db, int end = 0, int str = 0);
		void select(char* content, int COL, int row);
		void where(Tools::columns column, const char* value);
	};
}