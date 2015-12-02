#ifndef BLOON_MODEL_H
#define BLOON_MODEL_H

#include <deque>
#include <map>
#include <memory>
#include <string>

#include "Database.h"
#include "Model.h"

namespace model
{
    class BloonModel : public Model
    {
        public:
            explicit BloonModel(std::shared_ptr<Database> db);
            ~BloonModel();
            void insert(int earn, int health, int shield, int speed);

        protected:
            void createTable();
    };
}



#endif