#ifndef CONFIG_H
#define CONFIG_H
#include <QObject>
#include <QFile>
#include <iostream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>



using namespace std;

class Config : public QObject
{
    Q_OBJECT

public:
    Config(const QString & filename, QObject *parrent=nullptr);
    ~Config() final;

private:
    QFile config_file;  // конфигурационный файл
    int humidity;       // максимальная влажность
    int temp;           // максимальная температура

public:
    int getHumidity() const;     // получить значение члена класса humidity
    int getTemp() const;        // получить значение члена класса temp
    void setTemp(int humidity = 0);     // установить значение члена класса temp
    void setHumidity(int temp = 0);     // установить значение члена класса humidity
    void readConfig();                  // прочитать весь конфиг и заполнить переменные humidity и temp
    void writeConfig();                 // записать текущие данные в конфиг
    QFile &getConfigFile();             //получить ссылку на член класса config_file


};
#endif
