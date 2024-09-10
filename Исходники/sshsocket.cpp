void sshsocket::edit()
{
    QTimer *timer = servers->at(index)->getTimer() ;
    if (timer != NULL)
    {
        if (timer->isActive())
        {
            timer->stop() ;
            delete timer ;
        }
    }

    QThread *thread = (QThread*)host->getThread() ;
    if (thread != NULL)
    {
        if (thread->isRunning())
        {
            thread->exit();
        }
    }
    servers->replace(index, host);
    model->new_updt(index);
}