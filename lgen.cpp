
#include "lgen.h"
#include <iostream>

//constructor
LGen::LGen( std::map< std::pair< QString , QString > , QString > & hmap ,
            std::string modelclass ,
            std::string directory ,
            std::string filename
          )
{
this->m_map = hmap ;
this->m_modelclass = modelclass ;
this->m_directory = directory ;
this->m_filename = filename ;
}

void LGen::generateClass()
{
    QString headerFileName = QDir(this->m_directory.c_str()).filePath((this->m_filename+".h").c_str());
    QFile loaderh(headerFileName);
    if (loaderh.open(QFile::WriteOnly | QFile::Truncate))
    {
        QDebug out(&loaderh);

        out.nospace() << std::string("#ifndef "+this->m_filename+"_H\n").data();
        out.nospace() << std::string("#define "+this->m_filename+"_H\n\n").data();

        out.nospace() << "#include <QCoreApplication>\n#include <QString>\n";
        out.nospace() << "#include <QDebug>\n#include <map>\n";
        out.nospace() << "#include <QFile>\n";
        out.nospace() << std::string("#include \""+this->m_modelclass+".h\"\n").data();
        out.nospace() << "#include <QXmlStreamReader>\n";

        out.nospace() << "\n\n";
        out.nospace() << "class ";
        out.nospace() << this->m_filename.data();
        out.nospace() << "{";
        out.nospace() << "\n\n";


        out.nospace() << "\tQString tmpClassName;\n";
        out.nospace() << "\tQString tmpClassType;\n";

        out.nospace() << std::string("public:\n").data();

        out.nospace() << std::string("\n\t"+this->m_modelclass+" load("+this->m_modelclass+"& model);\n").data();


        out.nospace() << "\n};\n";
        out.nospace() << "#endif";
    }
    else
    {
        qDebug()<<"Loader failed to open";

    }

    loaderh.close();

    //source file
    QString sourceFileName = QDir(this->m_directory.c_str()).filePath((this->m_filename+".cpp").c_str());
    QFile loaders(sourceFileName);
    if (loaders.open(QFile::WriteOnly | QFile::Truncate))
    {
        QDebug out(&loaders);

        out.nospace() << std::string("#include \""+this->m_filename+".h\"").data();

        out.nospace() << std::string("\n\n\t"+this->m_modelclass+" "+this->m_filename+"::load("+this->m_modelclass+"& model)\n\t{\n").data();

        out.nospace() << "\t\tstd::map<std::pair<QString, QString>, QString> xmlTokens;\n";
        out.nospace() << "\t\ttypedef std::map<std::pair<QString, QString>, QString> Dict;\n";
        out.nospace() << "\t\ttypedef Dict::const_iterator It;\n\n";



        out.nospace() << "\t\tQFile* data = new QFile(\"data.xml\");\n";
        out.nospace() << "\t\tif (!data->open(QIODevice::ReadOnly | QIODevice::Text)) \n\t\t{\n";
        out.nospace() << "\t\t\tqDebug() << \"Not read only\";\n";
        out.nospace() << "\t\t}\n\n";
        out.nospace() << "\t\tQXmlStreamReader readXML(data);\n";
        out.nospace() << "\t\twhile(!readXML.atEnd() && !readXML.hasError()) \n\t\t{\n";
        out.nospace() << "\t\t\tQXmlStreamReader::TokenType token = readXML.readNext();\n";
        out.nospace() << "\t\t\tif(token == QXmlStreamReader::StartDocument) \n\t\t\t{\n";
        out.nospace() << "\t\t\t\tcontinue;\n";
        out.nospace() << "\t\t\t}\n";
        out.nospace() << "\t\t\telse if (readXML.isEndElement() != true) \n\t\t\t{\n";
        out.nospace() << "\t\t\t\tif(readXML.attributes().size()>2)\n";

        out.nospace() << "\t\t\t\t\txmlTokens[std::make_pair(readXML.attributes()[0].value().toString(), readXML.attributes()[1].value().toString())] = readXML.attributes()[2].value().toString();\n";
        out.nospace() << "\t\t\t}\n";
        out.nospace() << "\t\t}\n\n";

        for (std::map<std::pair<QString,QString>,QString>::const_iterator it= m_map.begin(); it != m_map.end(); ++it)
        {


            out.nospace() << "\t\ttmpClassType = " << it -> second << ";\n";

            out.nospace() << "\t\ttmpClassName = " << it -> first.second << ";\n\n";

            out.nospace() << "\t\tfor (It it= xmlTokens.begin(); it != xmlTokens.end(); ++it) \n\t\t{\n";

            out.nospace() << "\t\t\tif((it -> first.second).compare(tmpClassName) == 0) \n\t\t\t{\n";

            if (((QString)(it -> second)).compare("QString") == 0)
            {
                out.nospace() << "\t\t\t\t\tmodel.set" << (it -> first.second).toUtf8().constData();
                out.nospace() << "((QString)(it -> second));\n";
            }

            else if (((QString)(it -> second)).compare("bool") == 0)
            {
                out.nospace() << "\t\t\t\t\tint boolValue = ((QString)(it -> second)).toInt();\n";
                out.nospace() << "\t\t\t\t\tmodel.set" << (it -> first.second).toUtf8().constData();
                out.nospace() << "(static_cast<bool>(boolValue));\n";
            }

            else if (((QString)(it -> second)).compare("double") == 0)
            {
                out.nospace() << "\t\t\t\t\tdouble doubleValue = ((QString)(it -> second)).toDouble();\n";
                out.nospace() << "\t\t\t\t\tmodel.set" << (it -> first.second).toUtf8().constData();
                out.nospace() << "(doubleValue);\n";
            }

            else if (((QString)(it -> second)).compare("int") == 0)
            {
                out.nospace() << "\t\t\t\t\tint intValue = ((QString)(it -> second)).toInt();\n";
                out.nospace() << "\t\t\t\t\tmodel.set" << (it -> first.second).toUtf8().constData();
                out.nospace() << "(intValue);\n";
            }

            out.nospace() << "\t\t\t}\n\t\t}";
            out.nospace() << "\n\n";
        }

        out.nospace() << "\t\treturn model;";
        out.nospace() << "\n\t}";

    }

    loaders.close();

}




