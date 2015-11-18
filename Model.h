#ifndef MODEL_H
#define MODEL_H

#include "Include.h"
#include <memory>
#include "Database.h"

namespace model {
	class Model {

		public:
			Model(std::shared_ptr<Database> db);
			virtual ~Model();
			virtual void createTable() = 0;
      		//virtual bool isExist = 0;

		protected:
			//virtual void callback(void *NotUsed, int argc, char **argv, char **azColName) = 0;
			std::shared_ptr<Database> m_db;

	};
}

#endif
