#ifndef BLOON_MODEL_H
#define BLOON_MODEL_H

#include <deque>
#include <map>
#include <memory>
#include <string>
#include <sstream>

#include "Database.h"
#include "Model.h"

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
			void freeResults(); //TODO: unique_ptr, auto free ?
			void insert(int earn, int health, int shield, int speed);
			const DbResults* get(std::string col, std::string value);
			const DbResults* get(std::string col, int value);
			static void sanitize(std::string &value);

		protected:

		private:
			DbResults m_results; //TODO: Check memory bloon allocation tas & pile depassement
	};
}



#endif