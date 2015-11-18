#include "BloonModel.h"


namespace model {
	int BloonModel::requestCallback(void *array, int argc, char **argv, char **azColName)
	{
		DbResults *results = static_cast<DbResults*>(array);
		//Cleaning last values
		results->clear();
		results->resize(argc);
		for (int i=0; i<argc; i++)
		{
			(*results)[i][azColName[i]] = argv[i];
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		return 0;
	}

	BloonModel::BloonModel(std::shared_ptr<Database> db) :
	Model(db)
	{
	}

	BloonModel::~BloonModel()
	{
	}

	void BloonModel::createTable()
	{
		char* sql = "CREATE TABLE Bloon("  \
					"ID INT PRIMARY KEY	   NOT NULL," \
					"health         INT    NOT NULL," \
					"speed          INT    NOT NULL," \
					"earn           INT    NOT NULL," \
					"shield         INT );";
		m_db->request(sql, NULL);
	}

	bool BloonModel::isExist() const {
		return m_db->request("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='table_name'", BloonModel::requestCallback);
	}

	const DbResults* BloonModel::getAll() {
		m_db->request("SELECT * FROM Bloon", BloonModel::requestCallback, &m_results);
		return &m_results;
	}

}