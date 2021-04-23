#include "SensorController.h"

SensorController::SensorController(QObject *parent):QThread(parent), runFlag(false),
                            fileName("/tmp/weather_station.fifo"), fifoFile(this->fileName)
{

}

SensorController::~SensorController()
{

    this->setRunFlag(false);
    this->quit();
    this->wait();

}

void SensorController::setRunFlag(bool flag)
{
    this->runFlag=flag;
}

bool SensorController::getRunFlag() const
{
    return this->runFlag;
}

void SensorController::run()
{

    if ( !this->fifoFile.open(QIODevice::ReadOnly) )
    {
        cout<<"Ошибка: ошибка при открытие файла "<<fifoFile.fileName().toStdString()<<endl;
        exit(1);
    }
    QByteArray buff;
    while (this->runFlag)
    {
        sleep(1);
        buff=this->fifoFile.readAll();
        if ( buff.isEmpty() == false )
        {
            cout << buff.toStdString()<< endl;
            emit resultReady(buff);

        }
    }
    this->fifoFile.close();
}
