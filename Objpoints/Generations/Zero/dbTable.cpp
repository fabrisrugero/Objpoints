#include "dbTable.h"
#include "../First/settings.h"
bool Tools::dbTable::connectedTo(char* db, int end, int str){
	if (this->hasErrors) return false;
	char* database = new char[this->indexer = end - str];
	bool result = this->IsEqual(database, this->database);
	delete database; return result;
};
Tools::dbTable::dbTable(char* db, int end, int str){
	this->database = new char[this->indexer = end - str];
	for (this->Indexer = 0; this->Indexer < this->indexer; this->Indexer++) this->database[this->Indexer] = db[this->Indexer];
	this->query = new Tools::query(Tools::settings::defaultdir, this->QUERY_SIZE, this->MAX_CHARS, this->MAX_COLUMNS);
	this->querystatement = new char[this->QUERY_SIZE];
	this->sqlcommand = this->querystatement;
	this->table = "objectz_points";
	this->_errors = nullptr;
	this->initcolumns();
	query->connectTo(querystatement, db);
	if (sqlite3_open(sqlcommand, &this->db)) { 
		this->handlErrors();
		sqlite3_close(this->db);
	}
}
void Tools::dbTable::where(columns column, const char* value){
	this->query->clearbuffer(this->querystatement, 0, this->QUERY_SIZE);

};
void Tools::dbTable::select(Tools::content content){
	this->select(static_cast<int>(content));
	char **results = nullptr; int rows, columns; 
	if (sqlite3_get_table(this->db, this->sqlcommand, &results, &rows, &columns, &_errors)) return this->handlErrors();
	else this->query->copyrecords(results, rows, columns);
	sqlite3_free_table(results);
};
void Tools::dbTable::select(int content){
	switch (content){
	default:
	case distinct:
		query->add("DISTINCT", query->TYPE, true); 
		query->add(this->cols[objectz], query->TYPE);
		query->selectFromTable(this->querystatement, this->table, this->lenght);
		for (this->indexer = 0; querystatement[this->indexer] != '\0'; this->indexer++)
			if (querystatement[this->indexer] == ',') break; querystatement[this->indexer] == ' ';
		break;
	case group:
		break;
	case prevoius:
		break;
	case content::next:
		break;
	}
}
void Tools::dbTable::select(const char* content){

};
bool Tools::dbTable::errors(char* arr = nullptr){

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
	this->cols[points] = "points";
	this->cols[radius] = "radius";
	this->cols[id] = "id";
};
void Tools::dbTable::handlErrors(){
	this->errmsg = sqlite3_errmsg(this->db);
	for (this->indexer = 0; this->indexer < this->QUERY_SIZE; this->indexer++)
		if (this->errmsg[this->indexer] == '\0') break;
	if (this->_errors != nullptr) delete[] this->_errors; 
	this->_errors = new char[this->indexer];
	for (this->Indexer = 0; this->Indexer < this->indexer; this->Indexer++)
		this->_errors[this->Indexer] = this->errmsg[this->Indexer];
};
Tools::dbTable::~dbTable(){

}