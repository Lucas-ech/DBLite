#ifndef DBREQUEST_H
#define DBREQUEST_H

#include <string>
#include <memory>
#include <sqlite3.h>

class DbRequest
{
    public:
        DbRequest(sqlite3_stmt *statement);
        ~DbRequest();
        void bind(int index, int value);
        void bind(int index, std::string value);
        void exec();

    private:
        sqlite3_stmt *m_statement;
};

#endif
