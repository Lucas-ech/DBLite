#include "DbRequest.h"

DbRequest::DbRequest(sqlite3_stmt *statement) :
m_statement(statement)
{
}

DbRequest::~DbRequest() {

}

void DbRequest::bind(int index, int value) {
    if(m_statement == nullptr) {
        throw std::runtime_error("No statement begun.");
    }
    sqlite3_bind_int(m_statement, index, value);
    sqlite3_step(m_statement);
}

void DbRequest::exec() {
    sqlite3_finalize(m_statement);
}