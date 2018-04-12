#include "../../Enums/enums.h"
namespace Tools{
	class dbTable{




	public:
		~dbTable();
		bool errors(char* arr = nullptr);
		void select(const char* content);
		void select(Tools::content content);
		dbTable(char* db, int end = 0, int str = 0);
		bool connectedTo(char* db, int end = 0, int str = 0);
	};
}