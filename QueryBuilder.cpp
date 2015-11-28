#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(std::string query) :
m_query(query)
{
}

QueryBuilder::~QueryBuilder()
{
}

void QueryBuilder::bind(std::string tag, std::string value)
{
    escape(value);
    addQuotes(value);
    replaceTag(tag, value);
}

void QueryBuilder::bind(std::string tag, int value)
{
    replaceTag(tag, std::to_string(value));
}

void QueryBuilder::bind(std::string tag, float value)
{
    replaceTag(tag, std::to_string(value));
}

void QueryBuilder::bindParam(std::string tag, std::string value)
{
    replaceTag(tag, value);
}

std::string QueryBuilder::getQuery() const
{
    return m_query;
}

void QueryBuilder::tagFormat(std::string &tag)
{
    if (tag[0] != ':')
    {
        tag.insert(0, 1, ':');
    }
}

bool QueryBuilder::replaceTag(std::string tag, std::string value)
{
    tagFormat(tag);
    std::string::size_type pos = m_query.find(tag);

    //Tag not found
    if (pos == std::string::npos)
    {
        return false;
    }

    m_query.replace(pos, tag.length(), value);
    return true;
}

void QueryBuilder::escape(std::string &value)
{
    std::string::size_type pos(0);
    while ((pos = value.find("'", pos)) != std::string::npos)
    {
        value.replace(pos, 1, "\\'");
        pos += 2;
    }
}

void QueryBuilder::addQuotes(std::string &str)
{
    str.insert(str.begin(), 1, '`');
    str.insert(str.end(), 1, '`');
}