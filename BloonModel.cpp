#include "BloonModel.h"

//TODO: Check sqlite3_exec return value

namespace model {
    BloonModel::BloonModel(std::shared_ptr<Database> db) :
    Model(db, "Bloon")
    {
        createTable();
    }

    BloonModel::~BloonModel()
    {
    }

    void BloonModel::createTable()
    {
        m_db->request("CREATE TABLE IF NOT EXISTS Bloon("  \
                      "ID INT PRIMARY KEY    NOT NULL," \
                      "health         INT    NOT NULL," \
                      "speed          INT    NOT NULL," \
                      "earn           INT    NOT NULL," \
                      "shield         INT);", NULL);
    }

    void BloonModel::insert(int earn, int health, int shield, int speed)
    {
        m_db->request("INSERT INTO Bloon VALUES()", Model::requestCallback);
    }

}
