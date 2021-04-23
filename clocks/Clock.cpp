#include "Clock.h"


Clock::Clock(QObject *parrent):QObject(parrent),
    date(QDate::currentDate()), time(QTime::currentTime())
{
    this->startTimer(1000);

}

Clock::~Clock()
{
    this->killTimer(this->timerId);
}

void Clock::setTime()
{
    this->date=QDate::currentDate();
}

void Clock::setDate()
{
    this->time=QTime::currentTime();
}

void Clock::timerEvent(QTimerEvent *event)
{
    this->timerId=event->timerId();
    this->setDate();
    this->setTime();
    emit showTime( this->time.toString("hh:mm:ss") );
    emit showDate( this->date.toString("dd.MM.yyyy") );
}


