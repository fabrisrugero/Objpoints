#include "dbTable.h"
#include "../First/settings.h"
void Tools::dbTable::select(int content){
	switch (content){
	default: 
		break;
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
	case next:
		if (this->groupIndex < settings::maxGroupIndex) this->groupIndex++;
		else if (settings::maxGroupIndex > 0) this->groupIndex = 0;
		this->where(objectz, settings::groups[this->groupIndex]);
		break;
	case distinct:
		this->query->add("DISTINCT", query->TYPE, true);
		this->query->add(this->cols[objectz], query->TYPE);
		this->query->selectFromTable(this->querystatement, this->table, this->lenght);
		for (this->indexer = 0; querystatement[this->indexer] != '\0'; this->indexer++)
			if (querystatement[this->indexer] == ',') break; querystatement[this->indexer] = ' ';
		break;
	}
}
bool Tools::dbTable::hasErrors(char* arr){
	if (this->errors == nullptr) return false; if (arr == nullptr) return true;
	for (this->indexer = 0; this->errors[this->indexer] != '\0'; this->indexer++)
		arr[this->indexer] = this->errors[this->indexer];
	if (this->indexer < settings::QUERY_SIZE) arr[this->indexer] = '\0';
	return true;
};
bool Tools::dbTable::connectedTo(char* db){
	return this->IsEqual(db, this->database);
};
Tools::dbTable::dbTable(char* db, int end, int str){
	if (end -= str > 0) this->database = new char[end]; else this->database = nullptr;
	for (this->Indexer = 0; this->Indexer < end; this->Indexer++) this->database[this->Indexer] = db[this->Indexer]; this->database[this->Indexer] = '\0';
	if (this->database == nullptr) this->query = new Tools::query(Tools::settings::defaultdir, settings::QUERY_SIZE, settings::MAX_CHARS, settings::MAX_COLUMNS);
	else this->query = new Tools::query(this->database, settings::QUERY_SIZE, settings::MAX_CHARS, settings::MAX_COLUMNS);
	this->querystatement = new char[settings::QUERY_SIZE];
	this->sqlcommand = this->querystatement;
	this->table = "objectz_points";
	this->errors = nullptr;
	this->columns = 7;
	this->initcolumns();
	query->connectTo(querystatement, nullptr);
	if (sqlite3_open(sqlcommand, &this->db)) { 
		this->handlErrors();
		sqlite3_close(this->db);
	}
};
void Tools::dbTable::select(char* content, int COL, int row){
	this->query->readcell(content, query->cellposition(COL, row + 1));
	this->query->clearbuffer(content, query->getlenght(COL, row + 1), settings::MAX_CHARS);
}
int Tools::dbTable::select(content content){
	this->select(static_cast<int>(content)); char **results = nullptr; int rows, columns;
	if (sqlite3_get_table(this->db, this->sqlcommand, &results, &rows, &columns, nullptr)) return this->handlErrors();
	else this->query->copyrecords(results, rows, columns);
	sqlite3_free_table(results); return rows;
};
void Tools::dbTable::where(Tools::columns column, const char* value){
	this->query->add(value, query->VALUE);
	this->query->add(this->cols[column], query->TYPE);
	this->query->clearbuffer(this->querystatement, 0, settings::QUERY_SIZE);
	this->query->selectFromTable(this->querystatement, this->table, this->lenght, this->query->COL_ONE);
};
int Tools::dbTable::initcolumns(char* output, int setwidth){
	if (this->indeXer > 0) return this->columns; this->indeXer = -1;
	for (this->indexer = 0; this->indexer < this->columns*setwidth + 8; this->indexer++)
		output[this->indeXer += 1] = '-';
	output[this->indeXer += 1] = '\n'; int pixels = 0;
	for (this->Indexer = 0; this->Indexer < this->columns; this->Indexer++){
		output[this->indeXer += 1] = '|';  pixels = this->indeXer;
		this->indexer = static_cast<int>(std::floor((setwidth - this->widths[this->Indexer]) / 2));
		for (this->inDexer = 0; this->inDexer < this->indexer; this->inDexer++)
			output[this->indeXer += 1] = ' ';
		for (this->inDexer = 0; this->inDexer < this->widths[this->Indexer]; this->inDexer++)
			output[this->indeXer += 1] = this->cols[this->Indexer][this->inDexer];
		for (this->inDexer = 0; this->inDexer < this->indexer; this->inDexer++)
			output[this->indeXer += 1] = ' ';
		if (this->indeXer - pixels < setwidth) output[this->indeXer += 1] = ' ';
	}
	output[this->indeXer += 1] = '|'; output[this->indeXer += 1] = '\n';
	for (this->indexer = 0; this->indexer < this->columns*setwidth + 8; this->indexer++)
		output[this->indeXer += 1] = '-';
	output[this->indeXer += 1] = '\n';
	return this->columns;
};
bool Tools::dbTable::IsEqual(const char *a, const char *b){
	for (int i = 0; a[i] != '\0'; i++)
		if (a[i] != b[i])
			return false;
	return true;
}
int Tools::dbTable::handlErrors(){
	this->errmsg = sqlite3_errmsg(this->db);
	for (this->indexer = 0; this->indexer < settings::QUERY_SIZE; this->indexer++)
		if (this->errmsg[this->indexer] == '\0') break;
	if (this->errors != nullptr) delete[] this->errors; 
	this->errors = new char[this->indexer + 1];
	for (this->Indexer = 0; this->Indexer < this->indexer; this->Indexer++)
		this->errors[this->Indexer] = this->errmsg[this->Indexer];
	this->errors[this->Indexer] = '\0';
	return query->dimensions(true);
};
void Tools::dbTable::initcolumns(){
	this->widths = new int[this->columns]();
	this->cols = new const char*[this->columns];
	this->widths[objectz] = static_cast<int>(strlen(this->cols[objectz] = "objectz"));
	this->widths[IsPoint] = static_cast<int>(strlen(this->cols[IsPoint] = "IsPoint"));
	this->widths[pointx] = static_cast<int>(strlen(this->cols[pointx] = "pointx"));
	this->widths[pointy] = static_cast<int>(strlen(this->cols[pointy] = "pointy"));
	this->widths[pointz] = static_cast<int>(strlen(this->cols[pointz] = "points"));
	this->widths[radius] = static_cast<int>(strlen(this->cols[radius] = "radius"));
	this->widths[id] = static_cast<int>(strlen(this->cols[id] = "id"));
};
Tools::dbTable::~dbTable(){
	delete this->query;
	sqlite3_close(this->db);
	delete[] this->querystatement;
	if (this->database != nullptr)
		delete[] this->database;
}