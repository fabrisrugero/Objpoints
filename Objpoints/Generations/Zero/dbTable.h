#include "../../Enums/enums.h"
#include "../../Lib/query.h"
#include "../../Lib/sqlite3.h"
namespace Tools{
	class dbTable{
		sqlite3 *db;
		int indexer;
		int Indexer;
		char* _errors;
		bool hasErrors;
		char* database;
		const char** cols;
		const char* table;
		void handlErrors();
		void initcolumns();
		const char* errmsg;
		Tools::query* query;
		char* querystatement;
		const int lenght = 14;
		const char* sqlcommand;
		void select(int content);
		const int MAX_CHARS = 50;
		const int MAX_COLUMNS = 7;
		const int QUERY_SIZE = 300;
		int IsEqual(const char *a, const char *b);
	public:
		~dbTable();
		void select(content content);
		void select(const char* content);
		bool errors(char* arr = nullptr);
		dbTable(char* db, int end = 0, int str = 0);
		void where(columns column, const char* value);
		bool connectedTo(char* db, int end = 0, int str = 0);
	};
}