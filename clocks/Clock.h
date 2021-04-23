#ifndef CLOCK_H
#define CLOCK_H
#include <QObject>
#include <QDate>
#include <QTime>
#include <QString>
#include <QTimerEvent>
#include <iostream>

using namespace std;

class Clock : public QObject
{
    Q_OBJECT

public:
    Clock(QObject *parrent=nullptr);
    ~Clock();

private:
    QDate date;
    QTime time;
    int timerId;

public slots:
    void setTime();
    void setDate();

protected:
    void timerEvent(QTimerEvent *event) override final;

signals:
    void showTime(const QString &str);
    void showDate(const QString &str);



};
#endif
