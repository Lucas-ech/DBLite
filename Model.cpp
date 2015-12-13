#include "Model.h"

namespace model {
    Model::Model(std::shared_ptr<Database> db, std::string tableName) :
    m_db(db),
    m_tableName(tableName)
    {
    }

    Model::~Model()
    {
    }

    std::string Model::getTableName() const
    {
        return m_tableName;
    }

    Results Model::getAll()
    {
        QueryBuilder query("SELECT * FROM :table");
        query.bindParam(":table", m_tableName);

        WResults res(new DataResults);
        m_db->request(query.getQuery().c_str(), Model::requestCallback, &res);
        return std::move(res);
    }

    Results Model::get(std::string col, std::string value)
    {
        QueryBuilder query("SELECT * FROM :table WHERE :col = :value");
        query.bindParam(":table", m_tableName);
        query.bindParam(":col", col);
        query.bind(":value", value);

        WResults res(new DataResults);
        m_db->request(query.getQuery().c_str(), Model::requestCallback, &res);
        return std::move(res);
    }

    Results Model::get(std::string col, int value)
    {
        QueryBuilder query("SELECT * FROM :table WHERE :col = :value");
        query.bindParam(":table", m_tableName);
        query.bindParam(":col", col);
        query.bind(":value", value);

        WResults res(new DataResults);
        m_db->request(query.getQuery().c_str(), Model::requestCallback, &res);
        return std::move(res);
    }

    int Model::requestCallback(void *array, int argc, char **argv, char **azColName)
    {
        WResults *results = static_cast<WResults*>(array);
        (*results)->push_back({});
        for (int i=0; i<argc; i++)
        {
            (*results)->back()[azColName[i]] = argv[i];
        }
        return 0;
    }
}
