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
        QueryBuilder query;
        prepareSelect(query);

        WResults res(new DataResults);
        m_db->request(query.getQuery().c_str(), Model::requestCallback, &res);
        return std::move(res);
    }

    Results Model::get(std::string col, std::string value, int limit)
    {
      QueryBuilder query;
      prepareSelect(query, col, limit, ":value");
      query.bind(":value", value);

      WResults res(new DataResults);
      m_db->request(query.getQuery().c_str(), Model::requestCallback, &res);
      return std::move(res);
    }

    Results Model::get(std::string col, int value, int limit)
    {
        QueryBuilder query;
        prepareSelect(query, col, limit, ":value");
        query.bind(":value", value);

        WResults res(new DataResults);
        m_db->request(query.getQuery().c_str(), Model::requestCallback, &res);
        return std::move(res);
    }

    void Model::prepareSelect(QueryBuilder &query, std::string col, int limit, std::string condTag)
    {
        query.setQuery("SELECT * FROM :table");
        query.bindParam(":table", m_tableName);

        if (!col.empty())
        {
            query.append(" WHERE :col = :value");
            query.bindParam(":value", condTag);
            query.bindParam(":col", col);
        }

        if (limit > 0)
        {
            query.append(" LIMIT :l");
            query.bind(":l", limit);
        }
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
