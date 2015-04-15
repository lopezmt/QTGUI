#ifndef PARSE_H
#define PARSE_H

#include <QXmlStreamReader>
#include <QString>
#include <QFile>
#include <QDebug>
#include <map>
#include <QIODevice>

class Parser
{
private:
    std::string m_uifileuri ;
    QString m_prefix ;

public:
    Parser( std::string uifileuri , std::string prefix ) ;
    int parseXML( std::map< std::pair< QString , QString > , QString> & m ) ;
};


#endif // PARSE_H
