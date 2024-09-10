sysInfoThread::sysInfoThread(QObject *parent) :
    QThread(parent)
{
    mutex.lock();
    sysInfoTimer = new QTimer();
    connect(sysInfoTimer,SIGNAL(timeout()),
            this,SLOT(getSystemInfo()),Qt::DirectConnection);
    inf = new SystemInfo;
    mutex.unlock();

}