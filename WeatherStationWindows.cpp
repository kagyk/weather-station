#include "WeatherStationWindows.h"
#include "./ui_WeatherStationWindows.h"

WeatherStationWindows::WeatherStationWindows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherStationWindows)
{
    ui->setupUi(this);

    this->ui->dataTextLabel->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    this->ui->timeTextLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}

WeatherStationWindows::~WeatherStationWindows()
{
    delete ui;
    system("kill -s 2 $(ps ax | grep \"./sensors.sh\" | grep -v \"grep\" | awk '{print $1}') &");
    system("kill -s 9 $(ps ax | grep \"./sensors.sh\" | grep -v \"grep\" | awk '{print $1}') &");

}

void WeatherStationWindows::updateTime(const QString &str)
{
    this->ui->timeTextLabel->setText(str);
}

void WeatherStationWindows::updateDate(const QString &str)
{
    this->ui->dataTextLabel->setText(str);
}

void WeatherStationWindows::updateSensorData(QByteArray buff)
{

    QXmlStreamReader xml(buff);
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
                this->ui->tempLabel->setText(val);
                this->showAttentionTemp(val);

            }
            if (xml.name() == "max_humidity")
            {
                xml.readNext();
                QString val=xml.text().toString();
                this->ui->humidityLabel->setText(val);
                this->showAttentionHum(val);
            }
            break;
        default:
            break;
        }
    }
}

void WeatherStationWindows::showAttentionTemp(const QString &str)
{
    if (str.toInt() >= this->maxTem)
    {
        QMessageBox::warning(this, QString("WeatherStation"),
                             QString("ВНИМАНИЕ температура достигла максимального лимита "+QString(str)+QString(" ⁰C")),
                             QMessageBox::Ok);
    }
}

void WeatherStationWindows::showAttentionHum(const QString &str)
{
    if (str.toInt() >= this->maxHum)
    {
        QMessageBox::warning(this, QString("WeatherStation"),
                             QString("ВНИМАНИЕ влажность достигла максимального лимита "+QString(str)+QString(" %")),
                             QMessageBox::Ok);
    }

}

void WeatherStationWindows::showWarningTemp(const QString &str)
{

    this->ui->warningTempLabel->setText(str);
}

void WeatherStationWindows::showWarningHum(const QString &str)
{

    this->ui->warningHumidityLabel->setText(str);
}

void WeatherStationWindows::setMaxTem(int tem)
{
    this->maxTem=tem;
}

void WeatherStationWindows::setMaxHum(int hum)
{
    this->maxHum=hum;
}

