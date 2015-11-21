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
        std::stringstream sql;
        sql << "SELECT * FROM " << m_tableName.c_str();
        m_db->request(sql.str().c_str(), Model::requestCallback, &m_results);
        return m_results;
    }

    const DbResults& Model::get(std::string col, std::string value)
    {
        freeResults();
        sanitize(value);
        std::stringstream sql;
        sql << "SELECT * FROM " << m_tableName.c_str() << " WHERE " << col << " = '" << value << "'";
        m_db->request(sql.str().c_str(), Model::requestCallback, &m_results);
        return m_results;
    }

    const DbResults& Model::get(std::string col, int value)
    {
        freeResults();
        std::stringstream sql;
        sql << "SELECT * FROM " << m_tableName.c_str() << " WHERE " << col << " = '" << value << "'";
        m_db->request(sql.str().c_str(), Model::requestCallback, &m_results);
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