#include "query.h"
#include <cstring>
Tools::query::~query(){
	for (this->indexer = 0; this->indexer < this->max_columns; this->indexer++){
		delete[] this->values[this->indexer]; delete[] this->types[this->indexer];}
	this->max_columns = this->rows*this->columns + this->columns;
	for (this->Indexer = 0; this->Indexer < this->max_columns; this->Indexer++)
		delete[] this->results[this->Indexer];
	delete[] this->types;
	delete[] this->sizes;
	delete[] this->values;
	delete[] this->results;
	delete[] this->directory;
	delete[] this->types_lenght;
	delete[] this->values_lenght;
	delete[] this->querychararcters;
};
void Tools::query::clearbuffer(bool beforeBuild){
	if (beforeBuild){
		for (this->indexer = 0; this->indexer < this->query_size; this->indexer++)
			this->querychararcters[this->indexer] = '\0';
		this->position = 0;
	}
	else{
		for (this->indexer = 0; this->indexer < this->max_columns; this->indexer++){
			for (this->Indexer = 0; this->Indexer < this->values_lenght[this->indexer]; this->Indexer++)
				this->values[this->indexer][this->Indexer] = '\0';
			for (this->Indexer = 0; this->Indexer < this->types_lenght[this->indexer]; this->Indexer++)
				this->types[this->indexer][this->Indexer] = '\0';
			this->values_lenght[this->indexer] = this->types_lenght[this->indexer] = 0;
		}
	}
};
void Tools::query::clearbuffer(char* value, int lenght, int bufferlenght){
	for (this->indexer = lenght; this->indexer < bufferlenght ; this->indexer++)
		value[this->indexer] = '\0';
};
Tools::query::query(const char* directory, int query_size, int max_chars, int max_columns){
	this->indexer = 0;
	this->sizes = nullptr;
	this->results = nullptr;
	this->max_chars = max_chars;
	this->query_size = query_size;
	this->max_columns = max_columns;
	this->dir_size = strlen(directory);
	this->types_lenght = new int[max_chars]();
	this->initcolumns(&this->types, max_columns);
	this->values_lenght = new int[max_chars]();
	this->initcolumns(&this->values, max_columns);
	this->querychararcters = new char[query_size + 1];
	this->directory = new char[this->dir_size + 1];
	for (this->indexer = 0; this->indexer < this->dir_size; this->indexer++)
		this->directory[this->indexer] = directory[this->indexer];
};
void Tools::query::connectTo(char* sql, const char* database){
	this->clearbuffer();
	this->concantenate(this->directory, this->dir_size, database, 0);
	if (database != nullptr) this->concantenate(database, strlen(database), ".db", 3);
	for (this->indexer = 0; this->indexer < this->query_size; this->indexer++)
		sql[this->indexer] = this->querychararcters[this->indexer];
};
void Tools::query::copyrecords(char** query_results, int rows, int columns){
	this->deletecolms(&this->results, this->rows*this->columns + this->columns);
	this->initcolumns(&this->results, rows*columns + columns);
	if (this->sizes != nullptr) delete[] this->sizes;
	this->sizes = new size_t[rows*columns + columns];
	this->rows = rows; this->columns = columns;
	for (this->Indexer = 0; this->Indexer <= rows; ++this->Indexer){
		for (this->indexer = 0; this->indexer < columns; ++this->indexer){
			int cellPosition = (this->Indexer * columns) + this->indexer;
			this->sizes[cellPosition] = query_results[cellPosition] ? strlen(query_results[cellPosition]) : 0;
			for (size_t i = 0; i < this->sizes[cellPosition]; i++)	this->results[cellPosition][i] = query_results[cellPosition][i];
		}
	}
}
int Tools::query::cellposition(int columnindex, int rowindex){
	return (rowindex * this->columns) + columnindex;
};
int Tools::query::columnindex(const char* columname){
	for (this->indexer = 0; this->indexer < columns; ++this->indexer)
		if (this->IsEqual(columname, this->results[this->indexer])) return this->indexer;
	return -1;
}
size_t Tools::query::getlenght(int columindex, int rowindex){
	return this->sizes[(rowindex * this->columns) + columindex];
};
int Tools::query::dimensions(bool rowOrccolumn){
	if (rowOrccolumn) return this->rows;
	else return this->columns;
};
bool Tools::query::readcell(char *cell, int index){
	if (this->result = index < (this->rows*this->columns) + this->columns)
		for (this->Indexer = 0; this->Indexer < static_cast<int>(this->sizes[index]); this->Indexer++)
			cell[this->Indexer] = this->results[index][this->Indexer];
	return this->result;
};
void Tools::query::deleteRowInTable(char* sql, const char *table, int lenght, int column){
	this->clearbuffer();
	if (lenght == 0) lenght = strlen(table);
	this->concantenate("DELETE FROM ", 12, table, 0);
	this->concantenate(table, lenght, " WHERE ", 7);
	this->concantenate(this->types[column], this->types_lenght[column], " = ", 3);
	this->concantenate(this->values[column], this->values_lenght[column], ";", 1);
	for (this->indexer = 0; this->indexer < this->query_size; this->indexer++)
		sql[this->indexer] = this->querychararcters[this->indexer];
	this->clearbuffer(false);
};
void Tools::query::updateRowInTable(char* sql, const char *table, int lenght, int column){
	this->clearbuffer();
	if (lenght == 0) lenght = strlen(table);
	this->concantenate("UPDATE ", 7, table, lenght);
	this->concantenate(" SET ", 5, table, 0);
	for (int colum = 0; colum < this->max_columns; colum++){
		if (this->types_lenght[colum] == 0 || colum == column) continue;
		this->concantenate(this->types[colum], this->types_lenght[colum], " = ", 3);
		this->concantenate(this->values[colum], this->values_lenght[colum], ", ", 2);
	}
	this->position -= 2;
	this->concantenate(" WHERE ", 7, table, 0);
	this->concantenate(this->types[column], this->types_lenght[column], " = ", 3);
	this->concantenate(this->values[column], this->values_lenght[column], ";", 1);
	for (this->indexer = 0; this->indexer < this->query_size; this->indexer++)
		sql[this->indexer] = this->querychararcters[this->indexer];
	this->clearbuffer(false);
};
void Tools::query::insertIntoTable(char* sql, const char *table, int namelenght){
	this->clearbuffer();
	if (lenght == 0) lenght = strlen(table);
	this->concantenate("INSERT INTO ", 12, table, 0);
	this->concantenate(table, namelenght, " (", 2);
	for (this->Indexer = 0; this->Indexer < this->max_columns; this->Indexer++){
		if (this->types_lenght[Indexer] == 0) continue;
		this->concantenate(this->types[this->Indexer], this->types_lenght[this->Indexer], ", ", 2);
	}
	if (this->position > 14 + namelenght) this->position -= 2; else return;
	this->concantenate(") VALUES (", 10, table, 0);
	for (this->Indexer = 0; this->Indexer < this->max_columns; this->Indexer++){
		if (this->values_lenght[this->Indexer] == 0) continue;
		this->concantenate(this->values[this->Indexer], this->values_lenght[this->Indexer], ", ", 2);
	}
	this->position -= 2;
	this->concantenate(");", 2, table, 0);
	for (this->indexer = 0; this->indexer < this->query_size; this->indexer++)
		sql[this->indexer] = this->querychararcters[this->indexer];
	this->clearbuffer(false);
};
void Tools::query::selectFromTable(char* sql, const char *table, int lenght, int column){
	this->clearbuffer();
	if (lenght == 0) lenght = strlen(table);
	this->concantenate("SELECT ", 7, nullptr, 0);
	for (int colum = 0; colum < this->max_columns; colum++){
		if (this->types_lenght[colum] == 0 || colum == column) continue;
		this->concantenate(this->types[colum], this->types_lenght[colum], ", ", 2);}
	if (this->position > 7) this->position -= 2;
	else this->concantenate(nullptr, 0, "*", 1);
	this->concantenate(nullptr, 0, " FROM ", 6);
	if (column < 0) this->concantenate(table, lenght, " ORDER BY id ASC;", 17);
	else{ this->concantenate(table, lenght, " WHERE ", 7);
		this->concantenate(this->types[column], this->types_lenght[column], " = '", 4);
		this->concantenate(this->values[column], this->values_lenght[column], "' ORDER BY id ASC;", 18);}
	for (this->indexer = 0; this->indexer < this->query_size; this->indexer++)
		sql[this->indexer] = this->querychararcters[this->indexer];
	this->clearbuffer(false);
};
void Tools::query::concantenate(const char *a, int b, const char *c, int d){
	for (this->indexer = 0; this->position + this->indexer < this->query_size && this->indexer < b; this->indexer++)
		this->querychararcters[this->position + this->indexer] = a[this->indexer];
	this->position += this->indexer;
	for (this->indexer = 0; this->position + this->indexer < this->query_size && this->indexer < d; this->indexer++)
		this->querychararcters[this->position + this->indexer] = c[this->indexer];
	this->position += this->indexer;
};
void Tools::query::add(const char* value, Tools::query::Data column, bool addmore){
	this->lenght = strlen(value);
	if (this->index < this->max_columns && column == VALUE)
		for (this->indexer = 0; this->indexer < this->max_chars && this->indexer < this->lenght; this->indexer++)
			this->values[this->index][this->indexer] = value[this->indexer];
	else if (this->index < this->max_columns && column == TYPE)
		for (this->indexer = 0; this->indexer < this->max_chars && this->indexer < this->lenght; this->indexer++)
			this->types[this->index][this->indexer] = value[this->indexer];
	if (column == TYPE) this->types_lenght[this->index] = this->lenght;
	else if (column == VALUE) this->values_lenght[this->index] = this->lenght;
	if (addmore) this->index++;
	else this->index = 0;
	this->indexer = 0;
};
void Tools::query::initcolumns(char*** arr, int max_lenght){
	*arr = new char*[max_lenght];
	for (this->indexer = 0; this->indexer < max_lenght; this->indexer++)
		(*arr)[this->indexer] = new char[this->max_chars + 1]();
};
void Tools::query::deletecolms(char*** arr, int max_lenght){
	if (*arr == nullptr) return;
	for (this->indexer = 0; this->indexer < max_lenght; this->indexer++)
		delete[](*arr)[this->indexer];
	delete[](*arr);
};
int Tools::query::IsEqual(const char *a, const char *b){
	for (int i = 0; a[i] != '\0'; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}

