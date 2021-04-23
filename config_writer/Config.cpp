#include "Config.h"


Config::Config(const QString &filename, QObject *parrent):QObject(parrent),
    config_file(filename), humidity(0), temp(0)
{
    cout << this->config_file.fileName().toStdString()<<endl;
    this->readConfig();

}

Config::~Config()
{

}

int Config::getHumidity() const
{
    return this->humidity;
}

int Config::getTemp() const
{
    return this->temp;
}

void Config::setTemp(int temp)
{
    this->temp = temp;
}

void Config::setHumidity(int humidity)
{
    this->humidity = humidity;

}

void Config::readConfig()
{
    if ( !this->config_file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cout << "Ошибка при открытие файла" << config_file.fileName().toStdString() << endl;
        exit (1);
    }
    QXmlStreamReader xml(&this->config_file);
    while(!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        switch (token)
        {
        case QXmlStreamReader::StartDocument:
            break;
        case QXmlStreamReader::StartElement:
            if (xml.name() == "max_temperature")
            {
                xml.readNext();
                QString val=xml.text().toString();
                this->setTemp(val.toInt());
            }
            if (xml.name() == "max_humidity")
            {
                xml.readNext();
                QString val=xml.text().toString();
                this->setHumidity(val.toInt());
            }
            break;
        default:
            break;
        }
    }
    config_file.close();
}


void Config::writeConfig()
{
    if ( !this->config_file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        cout << "Ошибка при открытие файла" << config_file.fileName().toStdString() << endl;
        exit (1);
    }

    cout << "влажность = " << this->humidity << endl;
    cout << "температура =" << this->temp << endl;

    QXmlStreamWriter xml(&this->config_file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("config");
    xml.writeStartElement("max_temperature");
    QString val;
    val.setNum( this->temp );
    xml.writeCharacters(val);
    xml.writeEndElement();

    xml.writeStartElement("max_humidity");
    val="";
    val.setNum(this->humidity);
    xml.writeCharacters(val);
    xml.writeEndElement();
    xml.writeEndDocument();
    this->config_file.close();
}

QFile &Config::getConfigFile()
{
    return this->config_file;
}
