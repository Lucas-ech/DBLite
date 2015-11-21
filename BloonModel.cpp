#include "BloonModel.h"

//TODO: Check sqlite3_exec return value

namespace model {
    BloonModel::BloonModel(std::shared_ptr<Database> db) :
    Model(db)
    {
    }

    BloonModel::~BloonModel()
    {
    }

    void BloonModel::createTable()
    {
        char* sql = "CREATE TABLE Bloon("  \
                    "ID INT PRIMARY KEY    NOT NULL," \
                    "health         INT    NOT NULL," \
                    "speed          INT    NOT NULL," \
                    "earn           INT    NOT NULL," \
                    "shield         INT);";
        m_db->request(sql, NULL);
    }

    bool BloonModel::isExist() const
    {
        return m_db->request("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='table_name'", BloonModel::requestCallback);
    }

    const DbResults& BloonModel::getAll()
    {
        m_db->request("SELECT * FROM Bloon", Model::requestCallback, &m_results);
        return m_results;
    }

    const DbResults& BloonModel::get(std::string col, std::string value)
    {
        sanitize(value);
        std::stringstream sql;
        sql << "SELECT * FROM Bloon WHERE " << col << " = '" << value << "'";
        m_db->request(sql.str().c_str(), Model::requestCallback, &m_results);
        m_results[0]->at("ID");
        return m_results;
    }

    const DbResults& BloonModel::get(std::string col, int value)
    {
        std::stringstream sql;
        sql << "SELECT * FROM Bloon WHERE " << col << " = '" << value << "'";
        m_db->request(sql.str().c_str(), Model::requestCallback, &m_results);
        return m_results;
    }

    void BloonModel::freeResults()
    {
        for (auto res : m_results)
        {
            delete res;
        }
    }

    void BloonModel::insert(int earn, int health, int shield, int speed)
    {
        m_db->request("INSERT INTO Bloon VALUES()", Model::requestCallback, &m_results);
    }

    void BloonModel::sanitize(std::string &value)
    {
        std::string::size_type pos(0);
        while ((pos = value.find("'", pos)) != std::string::npos)
        {
            std::cout << pos << std::endl;
            value.replace(pos, 1, "\\'");
            pos += 2;
        }
    }

}