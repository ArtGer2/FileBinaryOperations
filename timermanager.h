#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class TimerManager : public QObject {
    Q_OBJECT

public:
    explicit TimerManager(QObject *parent = nullptr);
    ~TimerManager();

    void startTimer(int interval);
    void stopTimer();

signals:
    void timeoutOccurred(); // Сигнал, который будет испускаться при каждом таймауте

private slots:
    void onTimeout(); // Слот, обрабатывающий событие таймаута

private:
    QTimer *timer;
};
#endif // TIMERMANAGER_H
