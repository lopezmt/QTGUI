#include "mgen.h"
#include "sgen.h"
#include "lgen.h"
#include "parse.h"
#include "QtToCppXMLCLP.h"
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    PARSE_ARGS;

    if( uifileuri.empty() || directory.empty() )
    {
      std::cerr << "You need to specify an output directory and an input UI file" << std::endl ;
      return EXIT_FAILURE ;
    }
    //Verifies that the UI file exists
    QFile my_qFile( (QString(uifileuri.c_str()) ) ) ;
    if( !my_qFile.exists() )
    {
        std::cerr << "UI file does not exist. Abort" << std::endl ;
        return EXIT_FAILURE ;
    }
    //Creates output directory
    QDir qDirectory( (QString(directory.c_str()) ) ) ;
    if( !qDirectory.exists() )
    {
        if( !qDirectory.mkpath(".") )
        {
            std::cerr << "Failed to create new directory "<< directory << std::endl ;
            std::cerr << "Abort" << std::endl ;
            return EXIT_FAILURE ;
        }
        else
        {
            std::cout << "Successfully created output directory " << directory << std::endl ;
        }
    }
    //Parses UI file
    if( prefixes.empty() )
    {
      std::string emptyString = "" ;
      prefixes.push_back( emptyString ) ;
      std::cout << "No prefix specified" << std::endl ;
    }
    for( size_t i = 0 ; i < prefixes.size() ; i++ )
    {
      std::cout << "Prefix: " << prefixes[ i ] << std::endl ;
      Parser parser( uifileuri , prefixes[ i ] ) ;
      std::map< std::pair < QString , QString > , QString > m ;
      if( parser.parseXML( m ) )
      {
        return EXIT_SUCCESS ;
      }
      //Creates automatically generated C++ classes
      MGen mgen( m , directory , modelname , prefixes[ i ] ) ;
      mgen.generateClass() ;

      LGen load( m , modelname , directory , loadername , prefixes[ i ] ) ;
      load.generateClass() ;

      SGen save( m , modelname , directory , savername , prefixes[ i ] ) ;
      save.generateClass() ;
    }
    return EXIT_SUCCESS ;
}


