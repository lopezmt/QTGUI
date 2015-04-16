#ifndef SGEN_H
#define SGEN_H

//define file name is not already done
#ifndef SAVERFILENAME
#define SAVERFILENAME "../COMP523ProjectQTParamCp/saver.h"
#endif

#ifndef INCLUDEHEADER
#define INCLUDEHEADER "#include"
#endif

//Define the header of the class
#define SAVERCLASSHEADER \
    "class Saver {"

//Termination character
#define SAVERCLASSTERMINATE\
    "};"


//Includes

#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <set>

#include <iostream>
#include <QDebug>
#include <QTextEdit>
#include <QDir>
#include <QXmlStreamWriter>


//Class used to strip data from the dictionary and streams into a cpp file current in
//the same directory
class SGen{

public:

    typedef std::map<std::pair<QString,QString>,QString> MapType ;
    //constructor
    SGen( std::map< std::pair< QString , QString > , QString > & hmap ,
          std::string modelclass ,
          std::string directory = "" ,
          std::string filename = "saver" ,
          std::string prefix = ""
        ) ;

    //destructor
    ~SGen();

    //METHODS

    //Outputs the hmap into the Saver.h
    void generateClass() ;


private:
    //generate the include files the saver needs
    void genIncludes(std::ofstream & savehstream);

    //generates fields
    void genField(std::ofstream & savehstream);

    //generate the save method in the saver
    void genMethod(std::ofstream & savehstream,bool isHeader);

    //generate each line of method, indented. Also, puts ; at end. Default is one tab
    void genMethodLine(std::ofstream & savestream,std::string s,int tab_amount=1);

    //method to generate the saver method to write out the model values upon save
    void genSavetoXMLMethod(std::ofstream & savestream,std::map<std::pair<QString,QString>,QString>::const_iterator & it, int tab_index, bool isHeader);

    const MapType & hmap;
    //file stream to print out to model file

    std::string filename;
    std::string directory;
    std::string modelclass;
    std::string m_prefix ;


};



#endif // SGEN_H
