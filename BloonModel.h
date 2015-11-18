#ifndef BLOON_MODEL_H
#define BLOON_MODEL_H

#include <vector>
#include <map>
#include <memory>
#include <string.h>

#include "Database.h"
#include "Model.h"

typedef std::vector<std::map<std::string, std::string> > DbResults;

namespace model {
	struct Bloon {
		unsigned int id, health, speed, earn, shield;
	};

	class BloonModel : public Model {

		public:
			BloonModel(std::shared_ptr<Database> db);
			~BloonModel();
			void createTable();
			bool isExist() const;
			const DbResults* getAll();

		protected:

		private:
			static int requestCallback(void *array, int argc, char **argv, char **azColName);
			DbResults m_results; //TODO: Check memory bloon allocation tas & pile depassement
	};
}



#endif