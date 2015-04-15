#include "mgen.h"

//constructor
MGen::MGen( std::map< std::pair < QString , QString > , QString > & hmap ,
            std::string directory ,
            std::string filename ,
            std::string prefix
          )
    :hmap(hmap),filename(prefix+filename),directory(directory)
{
  m_prefix = prefix ;
}

//destructor
MGen::~MGen()
{
}

//METHODS

//Outputs the hmap into the Model.cpp
void MGen::generateClass()
{
    std::ofstream headerstream;
    QString headerFileName = QDir(this->directory.c_str()).filePath((this->filename+".h").c_str());
    headerstream.open(headerFileName.toStdString().c_str(),std::ios::out);

    qDebug()<<headerFileName;

    try{
        if(headerstream.is_open()) {
            genHeader(headerstream);

        }
    }catch(...) {
        std::cout<<"Output to model cpp file failed"<<std::endl;

    }

    headerstream.close();

    std::ofstream sourcestream;
    QString sourceFileName = QDir(this->directory.c_str()).filePath((this->filename+".cpp").c_str());
    sourcestream.open(sourceFileName.toStdString().c_str(),std::ios::out);
    

    try{
        if(sourcestream.is_open()) {
            genSource(sourcestream);

        }
    }catch(...) {
        std::cout<<"Output to model cpp file failed"<<std::endl;

    }

    sourcestream.close();

}

void MGen::genHeader(std::ofstream & headerstream) {
    headerstream<<"#ifndef "+this->filename+"_H"<<std::endl;
    headerstream<<"#define "+this->filename+"_H"<<std::endl<<std::endl;

    //generate the includes
    genIncludes(headerstream);

    //print class keyword and the class name
    headerstream << "class "<<this->filename<<" {"<<std::endl;

    //generate the field
    genField(headerstream);

    //make getter and setters public
    headerstream <<std::endl<< "public: "<<std::endl<<std::endl;

    genGetSet(headerstream,true);

    headerstream<<"};"<<std::endl<<std::endl;
    headerstream<<"#endif"<<std::endl;

}

void MGen::genSource(std::ofstream & sourcestream)
{
    sourcestream<<"#include \""+this->filename+".h\""<<std::endl<<std::endl;

    genGetSet(sourcestream,false);

}


void MGen::genIncludes(std::ofstream & headerstream)
{
    //get iterator from begin
    std::map<std::pair<QString,QString>,QString>::const_iterator it=hmap.begin();


    while(it != hmap.end())
    {


        //compare the value type to the header QString for now, see if both are same string, aka when compare returns 0
        if(std::string("QString").compare(it->second.toUtf8().constData())==0 &&

                //try to find the header first
                (usedHeader.find(it->second.toUtf8().constData()) == usedHeader.end())) {

            headerstream<<"#include <"<<it->second.toUtf8().constData()
                      <<">"<<std::endl<<std::endl;

            //put into set
            usedHeader.insert(it->second.toUtf8().constData());
        }

        it++;
    }

}


//generates fields
void MGen::genField(std::ofstream & headerstream)
{
    //get iterator from begin
    std::map<std::pair<QString,QString>,QString>::const_iterator it=hmap.begin();


    while(it != hmap.end())
    {

        headerstream<<"\t"<<it->second.toUtf8().constData()<<" "
                  <<it->first.second.toUtf8().constData()<<";"<<std::endl;



        it++;
    }


}


void MGen::genGetSet(std::ofstream & headerstream,bool headeronly)
{
    //get iterator from begin
    std::map<std::pair<QString,QString>,QString>::const_iterator it=hmap.begin();

    //while the point did not hit the end of the map
    while(it != hmap.end()) {

        //getter
        genGet(it,headerstream,headeronly);



        //setter
        genSet(it,headerstream,headeronly);

        it++;
    }

}

void MGen::genGet(std::map<std::pair<QString,QString>,QString>::const_iterator & it, std::ofstream & stream,bool headeronly)
{
    //generate Type getVarName();
   stream<<"\t"<<it->second.toUtf8().constData()<<" "<<(headeronly?"":this->filename+"::")
              <<"get"
             <<it->first.second.toUtf8().constData()<<"()";

    //Now depending on whether we are generating header or not
    if(headeronly)
    {
        stream<<";"<<std::endl;
        //exit, cause no need to generate the rest unless we are messing with source
        return;
    }
    else
    {
        stream<<"{"<<std::endl;

    }

    //generate body of getter
    stream<<"\t\treturn "<<
                 it->first.second.toUtf8().constData()<<";"<<std::endl;

    //end it
    stream<<"\t}"<<std::endl;

}

void MGen::genSet(std::map<std::pair<QString,QString>,QString>::const_iterator & it, std::ofstream & stream, bool headeronly)
{
    //generate Type setVarName(Type a);
    stream<<"\tvoid "<<(headeronly?"":this->filename+"::")
              <<"set"
             <<it->first.second.toUtf8().constData()<<"("
            <<it->second.toUtf8().constData()
           <<" a"
          <<")";

    //Now depending on whether we are generating header or not
    if(headeronly)
    {
        stream<<";"<<std::endl<<std::endl;
        return;

    }
    else
    {
        stream<<"{"<<std::endl;

    }

    //generate body of setter
    stream<<"\t\t"<<
                 it->first.second.toUtf8().constData()<<"=a;"
              <<std::endl;

    //end it
    stream<<"\t}"<<std::endl;

}








