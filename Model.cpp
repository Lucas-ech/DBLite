#include "Model.h"

namespace model {
    Model::Model(std::shared_ptr<Database> db) :
    m_db(db)
    {
    }

    Model::~Model()
    {
    }

    int Model::requestCallback(void *array, int argc, char **argv, char **azColName)
    {
        DbResults *results = static_cast<DbResults*>(array);
        results->push_back(new std::map<std::string, std::string>);
        for (int i=0; i<argc; i++)
        {
            (*results->back())[azColName[i]] = argv[i];
        }
        return 0;
    }
}