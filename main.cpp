#include <iostream>
#include "Database.h"
#include "Model.h"
#include "BloonModel.h"

int main()
{
    Database db("tlw.db");
    model::BloonModel b(std::make_shared<Database>(db));
    Results results(b.getAll());
    std::cout << "Nombre de résultats : " << results->size() << std::endl;
    if (results->size() > 0)
    {
        for (auto res : (*results)[0])
        {
          std::cout << res.first << " = " << res.second << std::endl;
        }
    }

    QueryBuilder q("SELECT * FROM :table WHERE ID = :id AND truc = :string");
    q.bindParam(":table", "Bloon");
    q.bind(":id", 28);
    q.bind(":string", "MACHI'N");

    std::cout << q.getQuery() << std::endl;

    return 0;
}
