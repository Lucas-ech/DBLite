#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <stdexcept>
#include <string>

class QueryBuilder {

    public:
        explicit QueryBuilder(std::string query);
        ~QueryBuilder();
        void append(std::string sql);
        void bind(std::string tag, std::string value);
        void bind(std::string tag, int value);
        void bind(std::string tag, float value);
        void bindParam(std::string tag, std::string value);
        std::string getQuery() const;

    private:
        void tagFormat(std::string &tag);
        bool replaceTag(std::string tag, std::string value);
        void escape(std::string &value);
        void addQuotes(std::string &str);
        std::string m_query;
};

#endif
