#ifndef LGEN_H
#define LGEN_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <string>
#include <QDir>

class LGen{
private:
    std::map< std::pair< QString , QString > , QString > m_map ;

    std::string m_filename ;
    std::string m_modelclass ;
    std::string m_directory ;
    std::string m_prefix ;

public:
    //    //constructor
    LGen( std::map<std::pair<QString,QString>,QString> & hmap ,
          std::string modelclass ,
          std::string directory="",
          std::string filename = "loader",
          std::string prefix=""
        ) ;

    void generateClass() ;


} ;


#endif // LGEN_H
