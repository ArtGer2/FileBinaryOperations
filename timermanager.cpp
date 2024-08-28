#include "timermanager.h"

TimerManager::TimerManager(QObject *parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeut, this, &TimerManager::onTimeout);
}

// Деструктор
TimerManager::~TimerManager() {
    if (timer->isActive()) {
        timer->stop();
    }
}

// Метод для запуска таймера
void TimerManager::startTimer(int interval) {
    if (interval > 0) {
        timer->start(interval);
        qDebug() << "Timer started with interval:" << interval << "ms";
    } else {
        qWarning() << "Invalid interval. Timer not started.";
    }
}

// Метод для остановки таймера
void TimerManager::stopTimer() {
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "Timer stopped.";
    }
}

void TimerManager::onTimeout() {
    qDebug() << "Timeout occurred. Processing files...";
    emit timeoutOccurred();
}
