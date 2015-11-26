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

    const DbResults& Model::getAll()
    {
        freeResults();

        QueryBuilder query("SELECT * FROM :table");
        query.bindParam(":table", m_tableName);

        m_db->request(query.getQuery().c_str(), Model::requestCallback, &m_results);
        return m_results;
    }

    const DbResults& Model::get(std::string col, std::string value)
    {
        freeResults();

        QueryBuilder query("SELECT * FROM :table WHERE :col = :value");
        query.bindParam(":table", m_tableName);
        query.bindParam(":col", col);
        query.bind(":value", value);

        m_db->request(query.getQuery().c_str(), Model::requestCallback, &m_results);
        return m_results;
    }

    const DbResults& Model::get(std::string col, int value)
    {
        freeResults();

        QueryBuilder query("SELECT * FROM :table WHERE :col = :value");
        query.bindParam(":table", m_tableName);
        query.bindParam(":col", col);
        query.bind(":value", value);

        m_db->request(query.getQuery().c_str(), Model::requestCallback, &m_results);
        return m_results;
    }

    void Model::freeResults()
    {
        if (!m_results.empty())
        {
            for (auto res : m_results)
            {
                res->clear();
                delete res;
            }
            m_results.clear();
        }
    }

    void Model::sanitize(std::string &value)
    {
        std::string::size_type pos(0);
        while ((pos = value.find("'", pos)) != std::string::npos)
        {
            std::cout << pos << std::endl;
            value.replace(pos, 1, "\\'");
            pos += 2;
        }
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