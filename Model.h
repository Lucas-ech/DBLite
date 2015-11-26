#ifndef MODEL_H
#define MODEL_H

#include <deque>
#include <map>
#include <memory>
#include <string>
#include <sstream>

#include "Database.h"
#include "QueryBuilder.h"

typedef std::deque<std::map<std::string, std::string>* > DbResults;

namespace model {
    class Model {

        public:
            Model(std::shared_ptr<Database> db, std::string tableName);
            virtual ~Model();
            std::string getTableName() const;
            const DbResults& getAll();
            const DbResults& get(std::string col, std::string value);
            const DbResults& get(std::string col, int value);
            void freeResults(); //TODO: unique_ptr, auto free ?
            static void sanitize(std::string &value);

        protected:
            virtual void createTable() = 0;
            static int requestCallback(void *array, int argc, char **argv, char **azColName);
            std::shared_ptr<Database> m_db;
            std::string m_tableName;
            //TODO: Check memory bloon allocation tas & pile depassement
            //TODO: Remove in-class results
            DbResults m_results;
    };
}

#endif
