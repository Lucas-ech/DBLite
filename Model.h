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
            Results getAll();
            Results get(std::string col, std::string value, int limit = -1);
            Results get(std::string col, int value, int limit = -1);

        protected:
            virtual void createTable() = 0;
            void prepareSelect(QueryBuilder &query, std::string col = "", int limit = -1, std::string condTag = ":value");
            static int requestCallback(void *array, int argc, char **argv, char **azColName);
            std::shared_ptr<Database> m_db;
            std::string m_tableName;
    };
}

#endif
