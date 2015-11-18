#include "Model.h"

namespace model {
	Model::Model(std::shared_ptr<Database> db) :
	m_db(db)
	{
	}

	Model::~Model()
	{
	}
}