#ifndef WEATHERSTATIONWINDOWS_H
#define WEATHERSTATIONWINDOWS_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QXmlStreamReader>
#include <stdlib.h>
#include <iostream>
#include <QMessageBox>

using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class WeatherStationWindows; }
QT_END_NAMESPACE

class WeatherStationWindows : public QMainWindow
{
    Q_OBJECT

public:
    WeatherStationWindows(QWidget *parent = nullptr);
    ~WeatherStationWindows();

private:
    Ui::WeatherStationWindows *ui;
    int maxTem;
    int maxHum;

public:
    void showWarningTemp(const QString & str);
    void showWarningHum(const QString & str);

public slots:
    void updateTime(const QString &str);
    void updateDate(const QString &str);
    void updateSensorData(QByteArray buff);

private:
    void showAttentionTemp(const QString & str);
    void showAttentionHum(const QString & str);



};
#endif // WEATHERSTATIONWINDOWS_H
