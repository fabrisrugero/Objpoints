#pragma once
using namespace std;
namespace Tools{
	class query
	{
	public:
		~query();
		enum Data{ TYPE, VALUE };
		int dimensions(bool rowOrccolumns);
		bool readcell(char *cell, int index);
		int columnindex(const char* columname);
		int cellposition(int col, int rowindex);
		size_t getlenght(int columindex, int rowindex);
		void connectTo(char* sql, const char* database);
		void clearbuffer(char* value, int lenght, int bufferlenght);
		void copyrecords(char** query_result, int rows, int columns);
		void insertIntoTable(char* sql, const char *tablename, int namelenght);
		enum COLMN { COL_ONE, COL_TWO, COL_THREE, COL_FOUR, COL_FIVE, COL_SIX };
		void add(const char* value, Tools::query::Data column, bool addmore = false);
		query(const char* directory, int query_size, int max_chars, int max_columns);
		void deleteRowInTable(char* sql, const char *tablename, int lenght, int column);
		void selectFromTable(char* sql, const char *tablename, int lenght, int column = -1);
		void updateRowInTable(char* sql, const char *tablename, int namelenght, int column = 0);

	private:
		int rows;
		int index;
		int lenght;
		int columns;
		int indexer;
		int Indexer;
		bool result;
		int dir_size;
		char** types;
		int position;
		char** values;
		int max_chars;
		size_t* sizes;
		char** results;
		int query_size;
		char* directory;
		int max_columns;
		int* types_lenght;
		int* values_lenght;
		char* querychararcters;
		void clearbuffer(bool beforeBuild = true);
		int IsEqual(const char *a, const char *b);
		void initcolumns(char*** arr, int max_columns);
		void concantenate(const char *a, int b, const char *c, int d);
	};
}