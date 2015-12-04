#include "Database.h"

Database::Database(const char* dbfile) :
m_error(nullptr)
{
    // Checking if database exists
    std::ifstream fp(dbfile);
    if (!fp.good())
    {
        std::cerr << "WARNING: Database doesn't exist, creating..." << std::endl;
    }
    fp.close();

    int res = sqlite3_open(dbfile, &m_db);
    if (res != SQLITE_OK)
    {
        throw std::runtime_error("Can't open database.");
    }
}

Database::~Database()
{
    sqlite3_close(m_db);
}

int Database::request(const char* req, int (*callback)(void*, int, char**, char**), void* firstArg)
{
    int res = sqlite3_exec(m_db, req, callback, firstArg, &m_error);
    if (res != SQLITE_OK)
    {
        std::string error = std::to_string(*m_error);
        sqlite3_free(m_error);
        throw std::runtime_error("SQL error " + error);
    }
    return res;
}
