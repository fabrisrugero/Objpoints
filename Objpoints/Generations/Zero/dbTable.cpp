#include "dbTable.h"
#include "../First/settings.h"
bool Tools::dbTable::connectedTo(char* db, int end, int str){
	char* database = new char[this->indexer = end - str];
	bool result = this->IsEqual(database, this->database);
	delete database; return result;
};
Tools::dbTable::dbTable(char* db, int end, int str){
	this->database = new char[this->indexer = end - str];
	for (this->Indexer = 0; this->Indexer < this->indexer; this->Indexer++) this->database[this->Indexer] = db[this->Indexer];
	this->query = new Tools::query(Tools::settings::defaultdir, settings::QUERY_SIZE, settings::MAX_CHARS, settings::MAX_COLUMNS);
	this->querystatement = new char[settings::QUERY_SIZE];
	this->sqlcommand = this->querystatement;
	this->table = "objectz_points";
	this->errors = nullptr;
	this->initcolumns();
	query->connectTo(querystatement, db);
	if (sqlite3_open(sqlcommand, &this->db)) { 
		this->handlErrors();
		sqlite3_close(this->db);
	}
};
void Tools::dbTable::where(columns column, const char* value){
	this->query->add(value, query->VALUE);
	this->query->add(this->cols[column], query->TYPE);
	this->query->clearbuffer(this->querystatement, 0, settings::QUERY_SIZE);
	this->query->selectFromTable(this->querystatement, this->table, this->lenght, this->query->COL_ONE);
};
Tools::query* Tools::dbTable::select(content content){
	if (!this->select(static_cast<int>(content))) return nullptr; char **results = nullptr; int rows, columns;
	if (sqlite3_get_table(this->db, this->sqlcommand, &results, &rows, &columns, nullptr)) return this->handlErrors();
	else this->query->copyrecords(results, rows, columns);
	sqlite3_free_table(results); return this->query;
};
bool Tools::dbTable::select(int content){
	switch (content){
	case custom: 
		break;
	case group:
		this->groupIndex = 0;
		this->where(objectz, settings::groups[this->groupIndex]);
		break;
	case previous:
		if (this->groupIndex > 0) this->groupIndex--;
		else this->groupIndex = settings::maxGroupIndex;
		this->where(objectz, settings::groups[this->groupIndex]);
		break;
	case content::next:
		if (this->groupIndex < settings::maxGroupIndex) this->groupIndex++;
		else if (settings::maxGroupIndex > 0) this->groupIndex = settings::maxGroupIndex;
		this->where(objectz, settings::groups[this->groupIndex]);
		break;
	case distinct:
		query->add("DISTINCT", query->TYPE, true);
		query->add(this->cols[objectz], query->TYPE);
		query->selectFromTable(this->querystatement, this->table, this->lenght);
		for (this->indexer = 0; querystatement[this->indexer] != '\0'; this->indexer++)
			if (querystatement[this->indexer] == ',') break; querystatement[this->indexer] = ' ';
		break;
	}
}
bool Tools::dbTable::hasErrors(char* arr){
	if (this->errors == nullptr) return false; if (arr == nullptr) return true;
	for (this->indexer = 0; errors[this->indexer] != '\0'; this->indexer++)
		arr[this->indexer] = errors[this->indexer];
	if (this->indexer < settings::QUERY_SIZE) arr[this->indexer] = '\0';
	return true;
};
int Tools::dbTable::IsEqual(const char *a, const char *b){
	for (int i = 0; a[i] != '\0'; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}
void Tools::dbTable::initcolumns(){
	this->cols = new const char*[7];
	this->cols[objectz] = "objectz";
	this->cols[IsPoint] = "IsPoint";
	this->cols[pointx] = "pointx";
	this->cols[pointy] = "pointy";
	this->cols[pointz] = "points";
	this->cols[radius] = "radius";
	this->cols[id] = "id";
};
Tools::query* Tools::dbTable::handlErrors(){
	this->errmsg = sqlite3_errmsg(this->db);
	for (this->indexer = 0; this->indexer < settings::QUERY_SIZE; this->indexer++)
		if (this->errmsg[this->indexer] == '\0') break;
	if (this->errors != nullptr) delete[] this->errors; 
	this->errors = new char[this->indexer];
	for (this->Indexer = 0; this->Indexer < this->indexer; this->Indexer++)
		this->errors[this->Indexer] = this->errmsg[this->Indexer];
	return nullptr;
};
Tools::dbTable::~dbTable(){

}