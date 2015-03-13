#include "sgen.h"


//constructor
SGen:: SGen(std::map<std::pair<QString,QString>,QString> & hmap,std::string modelclass, std::string directory,std::string filename)
    :hmap(hmap),directory(directory), filename(filename),modelclass(modelclass){


}

//destructor
SGen::~SGen(){


}

//METHODS

//Outputs the hmap into the Saver.h
void SGen::generateClass() {
    std::ofstream savehstream;
    QString headerFileName = QDir(this->directory.c_str()).filePath((this->filename+".h").c_str());
    savehstream.open(headerFileName.toStdString().c_str(),std::ios::out);
    qDebug()<<headerFileName;

    try{
        if(savehstream.is_open()) {
            genMethodLine(savehstream,"#ifndef "+this->filename+"_H",0);
            genMethodLine(savehstream,"#define "+this->filename+"_H",0);

            //generate the includes
            genIncludes(savehstream);

            //print class keyword and the class name
            savehstream << "class "<<filename<<"{ "<<std::endl;



            //generate the field
            genField(savehstream);



            //make getter and setters public
            savehstream <<std::endl<< "public: "<<std::endl<<std::endl;

            //generate save method
            genMethod(savehstream, true);


            savehstream<<"};"<<std::endl;

            genMethodLine(savehstream,"#endif",0);

        }
    }catch(...) {
        std::cout<<"Output to model cpp file failed"<<std::endl;

    }

    savehstream.close();


    std::ofstream savesstream;
    QString cppFileName = QDir(this->directory.c_str()).filePath((this->filename+".cpp").c_str());
    savesstream.open(cppFileName.toStdString().c_str(),std::ios::out);

    try{
        if(savesstream.is_open()) {
            genMethodLine(savesstream,"#include \""+this->filename+".h\"",0);

            //generate save method
            genMethod(savesstream, false);

        }
    }catch(...) {
        std::cout<<"Output to model cpp file failed"<<std::endl;

    }

    savesstream.close();
}



void SGen::genIncludes(std::ofstream & savehstream) {
    savehstream<<INCLUDEHEADER<<" <QXmlStreamWriter>"<<std::endl;
    savehstream<<INCLUDEHEADER<<" <QFile>"<<std::endl<<std::endl;
    savehstream<<INCLUDEHEADER<<" <QString>"<<std::endl<<std::endl;
    savehstream<<INCLUDEHEADER<<" <string>"<<std::endl<<std::endl;
    savehstream<<INCLUDEHEADER<<" \""+this->modelclass+".h\""<<std::endl<<std::endl;
    savehstream<<INCLUDEHEADER<<" <QDebug>"<<std::endl<<std::endl;

}


//generates fields
void SGen::genField(std::ofstream & savehstream){



}



//generate the save method in the saver
void SGen::genMethod(std::ofstream & savestream, bool isHeader) {
    //get iterator from begin
    std::map<std::pair<QString,QString>,QString>::const_iterator it=hmap.begin();

    //used to determine amount of tab needed to properly indent this line
    int tab_index=1;

    //generate method signature
    genMethodLine(savestream,"void "+(isHeader? ("save("+this->modelclass+"& m);")
                                             :(filename+"::save("+this->modelclass+"& m){")),tab_index);


    //do not generate the rest if not header
    if(isHeader) {
        genSavetoXMLMethod(savestream,it, tab_index, isHeader);
        return;

    }

    tab_index++;

    //generate the file
    genMethodLine(savestream,"//First, address the appropriate instantiate",tab_index);
    genMethodLine( savestream,"QFile file(\"data.xml\");",tab_index);

    //open the file
    genMethodLine(savestream,"if(!file.open(QIODevice::WriteOnly)){",tab_index);
    //write lines in error handling
    genMethodLine(savestream,"//handle file open errors here ",tab_index+1);
    genMethodLine(savestream," qDebug()<<file.exists();",tab_index+1);
    genMethodLine(savestream,"}\n",tab_index);

    //generate the xml writer
    genMethodLine(savestream,"QXmlStreamWriter writer(&file);\n",tab_index);

    //call method that actually writes each field in model to xml file
    genMethodLine(savestream,"//write each field stored in model into xml",tab_index);
    genMethodLine(savestream,"saveToXML(m,writer);\n",tab_index);

    genMethodLine(savestream,"}\n\n",--tab_index);

    genSavetoXMLMethod(savestream,it, tab_index, isHeader);
}

//generate each line of method, indented. Also, puts ; at end. Default is one tab
void SGen::genMethodLine(std::ofstream & savestream,std::string s,int tab_amount) {

    for(;tab_amount>0;tab_amount--)
        savestream<<"\t";

    savestream<<s<<std::endl;
}

void SGen::genSavetoXMLMethod(std::ofstream & savestream,std::map<std::pair<QString,QString>,QString>::const_iterator & it, int tab_index, bool isHeader) {


    //first generate the method signature
    genMethodLine(savestream,"void "+(isHeader? ("saveToXML("+this->modelclass+"& m,QXmlStreamWriter& writer);"
                                       ):(filename+std::string("::saveToXML("+this->modelclass+"& m,QXmlStreamWriter& writer){\n"))),tab_index);

    if(isHeader) {
            return;

    }

    tab_index++;
    //generate xml headers
    genMethodLine(savestream,"writer.setAutoFormatting(true);\n",tab_index);

    //start document
    genMethodLine(savestream,"writer.writeStartDocument();\n\n",tab_index);

    //parent namespace and
    genMethodLine(savestream,"writer.writeStartElement(\"m:ModelData\");",tab_index);
    genMethodLine(savestream,"writer.writeNamespace(\"https://github.com/QTGUIFolks/QTGUI\",\"m\");",tab_index);



    bool void_pointer=false;
    //recusively generate the tag for data
    while(it != hmap.end()) {

        //generate
        genMethodLine(savestream,"writer.writeEmptyElement(\"m:Data\");",tab_index);

        //Type attribute
        genMethodLine(savestream,"writer.writeAttribute(\"type\",\""+std::string(it->second.toUtf8().constData())+"\");",tab_index);

        //convert qstring to string
        genMethodLine(savestream,"writer.writeAttribute(\"name\",\""+std::string(it->first.second.toUtf8().constData())+"\");",tab_index);




        //qDebug()<<QString::fromStdString(to_string(it->second.compare(QString("QString"))));

        //value attribute generation

        //saves data, falls under different cases
        if(it->second.compare(QString("string"))==0) {
            //convert to qstring first
            genMethodLine(savestream,"writer.writeAttribute(\"value\",QString::fromStdString(m.get"+std::string(it->first.second.toUtf8().constData())+"()));",tab_index);

        } else if(it->second.compare(QString("QString"))==0) {
            //can just output the qstring
            genMethodLine(savestream,"writer.writeAttribute(\"value\",m.get"+std::string(it->first.second.toUtf8().constData())+"());",tab_index);


        } else if(!(it->second.compare(QString("int")) && it->second.compare(QString("double"))
                  && it->second.compare(QString("bool")))) {
            //can just output the qstring
            genMethodLine(savestream,"writer.writeAttribute(\"value\",QString::number(m.get"+std::string(it->first.second.toUtf8().constData())+"()));",tab_index);

        } else {
            //extremely bad way to do this

            //convert all data type with same size as long or less to a long and print as string
            if(!void_pointer) {
                genMethodLine(savestream,"//Enagaging hacky void pointer method of saving",tab_index);

                //void can be used as an intermediate to convert anything to another type
                //genMethodLine("void* pointer;",tab_index);

                //now it exists, don't need to redeclare
                void_pointer=true;
            }

            //genMethodLine("pointer=reinterpret_cast<void*>(&m.get"+std::string(it->first.second.toUtf8().constData())+"());",tab_index);

            //check if the value object is less or equal to the long type. We can save it as a long. Else discard
            genMethodLine(savestream,"if(sizeof(m.get"+std::string(it->first.second.toUtf8().constData())+"())<=sizeof(long)) {\n",tab_index++);
            genMethodLine(savestream,"//Don't care about the value, as long as it is less in memory size than an long, we can save it as a long",tab_index);

            //convert to string
            genMethodLine(savestream,"writer.writeAttribute(\"value\",QString::fromStdString(std::to_string(m.get"+std::string(it->first.second.toUtf8().constData())+"())));",tab_index--);

            // genMethodLine("writer.writeAttribute(\"value\",QString::fromStdString(std::to_string(*(static_cast<long*>(pointer)))));",tab_index--);
            genMethodLine(savestream,"} else {",tab_index++);
            //else for error handling
            genMethodLine(savestream,"//Generate error if the value is too big to fit",tab_index);
            genMethodLine(savestream,"writer.writeAttribute(\"value\",\"Error: Invalid attribute value\");",tab_index--);
            genMethodLine(savestream,"}",tab_index);


        }


        //genMethodLine("if(sizeof(m.get"+std::string(it->first.second.toUtf8().constData())+"))));",tab_index);
        //genMethodLine("writer.writeAttribute(\"value\",QString::fromStdString(to_string(static_cast<long long> (m.get"+std::string(it->first.second.toUtf8().constData())+"))));",tab_index);


        it++;
    }

    genMethodLine(savestream,"writer.writeEndElement();\n",tab_index);

    //end document
    genMethodLine(savestream,"writer.writeEndDocument();\n",tab_index);

    tab_index--;
    //close the method
    genMethodLine(savestream,"}",tab_index);

}


