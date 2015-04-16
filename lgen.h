#ifndef LGEN_H
#define LGEN_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <string>
#include <QDir>

class LGen{
public:
    typedef std::map< std::pair< QString , QString > , QString > MapType ;
    //    //constructor
    LGen( MapType & hmap ,
          std::string modelclass ,
          std::string directory="",
          std::string filename = "loader",
          std::string prefix=""
        ) ;

    void generateClass() ;
private:
    MapType m_map ;
    std::string m_filename ;
    std::string m_modelclass ;
    std::string m_directory ;
    std::string m_prefix ;
    QString m_indent ;


} ;


#endif // LGEN_H
