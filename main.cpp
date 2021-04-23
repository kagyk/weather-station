#include "WeatherStationWindows.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <iostream>
#include <stdlib.h>


#include "config_writer/Config.h"
#include "clocks/Clock.h"
#include "sensor/SensorController.h"



using std::cout;
using std::endl;
QString setupFileName;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setApplicationName("Weather Station");
    QApplication::setApplicationVersion("0.1");

    system("./script/sensors.sh &"); //запуск подыгрывающего скрипта

    QCommandLineParser parser;
    parser.setApplicationDescription("Weather Station");
    parser.setApplicationDescription("Программа метиостанция предназначена для вывода показаний температуры и влажности на экран, а так же для оповещения пользователя о превышение температуры и влажности установленного лимита");

    QCommandLineOption showGuiOpt("show", QApplication::translate("main", "Запустить метиостацию"));
    parser.addOption(showGuiOpt);

    QCommandLineOption tempLimitOpt("set-limit-temp", QApplication::translate("main", "Установить значение тепературы, при привышение которой происходит оповещение пользователя"),
                                    QApplication::translate("main", "temp"));
    parser.addOption(tempLimitOpt);

    QCommandLineOption humLimitOpt("set-limit-hum", QApplication::translate("main", "Установить значение влажности, при привышение которой происходит оповещение пользователя"),
                                   QApplication::translate("main", "humidity"));
    parser.addOption(humLimitOpt);

    QCommandLineOption setupFileOpt(QStringList() << "s" << "set-config-file", QApplication::translate("main", "Задать альтернативный путь к файлу настроек"),
                                    QApplication::translate("main", "directory"));
    parser.addOption(setupFileOpt);

    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    bool showGui = parser.isSet(showGuiOpt);
    bool tempLimit = parser.isSet(tempLimitOpt);
    bool humLimit = parser.isSet(humLimitOpt);

    QString setupDirStr="";
    QString humLimitStr="";
    QString tempLimitStr="";

    parser.isSet(setupFileOpt) == true ? setupDirStr = parser.value(setupFileOpt) : setupDirStr="conf";
    parser.isSet(humLimitOpt) == true ? humLimitStr = parser.value(humLimitOpt) : humLimitStr="0";
    parser.isSet(tempLimitOpt) == true ? tempLimitStr = parser.value(tempLimitOpt) : tempLimitStr="0";

    setupFileName="config.xml";
    Config configFile(QString(setupDirStr+"/"+setupFileName));

    if ( showGui == true )
    {
        if (( setupDirStr.isEmpty() == false ) && (setupDirStr.isNull() == false))
        {
            QDir setupDir(setupDirStr);
            if ( setupDir.exists() == false )
            {
                cout << "Ошибка: " << "Директория " << setupDirStr.toStdString() << " не найдена !!!!" << endl;
                exit(1);
            }
            QFile setupFile( QString(setupDirStr+"/"+setupFileName) );

            if ( setupFile.exists() == false )
            {
                cout << "Ошибка: " << "Конфигурационный файл " << setupFile.fileName().toStdString() << " не найден !!!!" << endl;
                exit(1);
            }
            WeatherStationWindows w;
            Clock timer;
            if ( configFile.getHumidity() > 0 )
            {
                w.showWarningHum(QString("Установлен лиминт влажности ")+QString().setNum(configFile.getHumidity())+QString(" %"));
                w.setMaxHum(configFile.getHumidity());
            }
            w.showWarningTemp(QString("Установлен лиминт температуры ")+QString().setNum(configFile.getTemp())+QString("⁰C"));
            w.setMaxTem(configFile.getTemp());
            w.show();

            QObject::connect( &timer, SIGNAL(showTime(const QString &)), &w, SLOT(updateTime(const QString&)) );
            QObject::connect( &timer, SIGNAL(showDate(const QString &)), &w, SLOT(updateDate(const QString&)) );

            SensorController *controller = new SensorController();
            controller->setRunFlag(true);
            controller->start();

            QObject::connect( controller, &SensorController::finished, controller, &QObject::deleteLater );
            QObject::connect( controller, SIGNAL(resultReady(QByteArray )), &w, SLOT(updateSensorData(QByteArray )) );


            return a.exec();
        }
    }
    else
    {

        if ( tempLimit == true )
        {
            configFile.setTemp(tempLimitStr.toInt());
            configFile.writeConfig();
        }

        if ( humLimit == true )
        {
            if ( ( humLimitStr.toUInt() > 100) || (humLimitStr.toUInt() < 0) )
            {
                cout << "Ошибка: относительная влажность должна лежать в пределах от 0 до 100 %"<<endl;
                exit(1);
            }
            configFile.setHumidity(humLimitStr.toUInt());
            configFile.writeConfig();
        }
        exit (0);
    }


}
