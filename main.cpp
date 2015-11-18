#include <iostream>
#include "Include.h"
#include "Database.h"
#include "BloonModel.h"

int main()
{
	Database db("tlw.db");
	model::BloonModel b(std::make_shared<Database>(db));
	//b.createTable();
	const DbResults *res;
	res = b.getAll();
	std::cout << (*res)[0].at("ID") << std::endl;
	//db.request("SELECT * FROM Bloon", NULL);
	return 0;
}