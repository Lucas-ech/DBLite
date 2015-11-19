#include <iostream>
#include "Database.h"
#include "BloonModel.h"

int main()
{
	Database db("tlw.db");
	model::BloonModel b(std::make_shared<Database>(db));
	//b.createTable();
	const DbResults *results;
	results = b.getAll();
	std::cout << "Nombre de résultats : " << results->size() << std::endl;
	for (auto res : *results) {
		for (auto item : *res) {
			std::cout << item.first << " = " << item.second << std::endl;
		}
	}
	b.freeResults();
	return 0;
}