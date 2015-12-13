#ifndef MODEL_H
#define MODEL_H

#include <deque>
#include <map>
#include <memory>
#include <string>
#include <sstream>

#include "Database.h"
#include "QueryBuilder.h"

using DataResults = std::deque<std::map<std::string, std::string>>;
using Results = std::unique_ptr<const DataResults>;

namespace model {
    using WResults = std::unique_ptr<DataResults>;

    class Model {

        public:
            Model(std::shared_ptr<Database> db, std::string tableName);
            virtual ~Model();
            std::string getTableName() const;
            Results getAll(); //TODO: make const
            Results get(std::string col, std::string value);
            Results get(std::string col, int value);
            void freeResults(); //TODO: unique_ptr, auto free ?
            static void sanitize(std::string &value);

        protected:
            virtual void createTable() = 0;
            static int requestCallback(void *array, int argc, char **argv, char **azColName);
            std::shared_ptr<Database> m_db;
            std::string m_tableName;
    };
}

#endif
