void AudioPlayerControlRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    QDBusInterface tracklist(QString::fromLatin1( "org.mpris.%1").arg(m_player),
                             QLatin1String( "/TrackList" ), QLatin1String( "org.freedesktop.MediaPlayer" ));

    QVariantList data = match.data().value<QVariantList>();

    /* Only Amarok part*/
    QString url = data[2].toString();
    int pos = posInPlaylist(url);
    kDebug() << "pos" << pos;
    QAction *a = match.selectedAction();
    if (data[3].toString().compare(NONE)) {
        if (!a)
        {
            a = action(data[3].toString());
        }
        if (a == action(QUEUE)) {
            KUrl::List list;
            list << KUrl(url);
            KRun::run(QLatin1String( "amarok --queue %u" ), list, 0);
        } else if (a == action(APPEND)) {
            if (!(pos > -1)) {
                tracklist.call(QDBus::NoBlock, QLatin1String( "AddTrack" ), url , false);
            }
        } else {
            //Action play was selected
            if (pos > -1) {
                tracklist.call(QDBus::NoBlock, QLatin1String( "PlayTrack" ), pos);
            } else {
                tracklist.call(QDBus::NoBlock, QLatin1String( "AddTrack" ), url, true);
            }
        }
    }/* Only Amarok part over */ else {
        if ((data[4].toString().compare(QLatin1String( "start" )) == 0)) {
            //The players's interface isn't available but it should be started
            if (!startPlayer()) {
                return;
            }
        }

        QDBusMessage msg = QDBusMessage::createMethodCall(QString::fromLatin1( "org.mpris.%1").arg(m_player),data[0].toString(),
                           data[1].toString(), data[2].toString());
        kDebug() << msg;
        QVariantList args;
        for (int i = 5;data.length() > i;++i) {
            args << data[i];
        }
        msg.setArguments(args);
        QDBusConnection::sessionBus().call(msg, QDBus::NoBlock);
    }
}