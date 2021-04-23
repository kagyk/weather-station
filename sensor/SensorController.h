#ifndef SENSOR_CONTROLLER_H
#define SENSOR_CONTROLLER_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QXmlStreamReader>
#include <stdlib.h>


#include <iostream>

using namespace std;

class SensorController : public QThread
{
    Q_OBJECT

public:
    SensorController(QObject *parent = nullptr);
    ~SensorController() final;

private:
    bool runFlag;
    const QString fileName;
    QFile fifoFile;

public:
    void setRunFlag(bool flag);
    bool getRunFlag() const;

protected:
    void run() override final;

signals:
    void resultReady(QByteArray buff);


};
#endif
