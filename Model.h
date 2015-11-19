#ifndef MODEL_H
#define MODEL_H

#include <deque>
#include <map>
#include <memory>
#include "Database.h"

typedef std::deque<std::map<std::string, std::string>* > DbResults;

namespace model {
	class Model {

		public:
			Model(std::shared_ptr<Database> db);
			virtual ~Model();
			virtual void createTable() = 0;
      		//virtual bool isExist = 0;

		protected:
			std::shared_ptr<Database> m_db;
			static int requestCallback(void *array, int argc, char **argv, char **azColName);

	};
}

#endif
