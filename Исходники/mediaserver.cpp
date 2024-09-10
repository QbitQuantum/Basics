void MediaServerControlTask::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == d->qssTimerId)
    {
        if (!d->soundserver)
        {
            d->soundserver = new QProcess(this);
            d->soundserver->setProcessChannelMode(QProcess::ForwardedChannels);
            d->soundserver->closeWriteChannel();

            connect(d->soundserver, SIGNAL(finished(int)), this, SLOT(soundServerExited()));
        }

        d->soundserver->start(Qtopia::qtopiaDir() + "bin/mediaserver");

        killTimer(d->qssTimerId);
        d->qssTimerId = 0;
    }