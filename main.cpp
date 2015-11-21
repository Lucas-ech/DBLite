#include <iostream>
#include "Database.h"
#include "BloonModel.h"

int main()
{
    Database db("tlw.db");
    model::BloonModel b(std::make_shared<Database>(db));
    const DbResults *results;
    results = b.get("ID", 1);
    std::cout << "Nombre de résultats : " << results->size() << std::endl;
    for (auto res : *(*results)[0])
    {
            std::cout << res.first << " = " << res.second << std::endl;
    }
    b.freeResults();
    return 0;
}