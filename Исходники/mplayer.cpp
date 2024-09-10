// Save unfinished time
MPlayer::~MPlayer()
{
#ifdef Q_OS_LINUX
    if (!unfinished_time.isEmpty() && Settings::rememberUnfinished)
    {
        QByteArray data;
        QHash<QString, int>::const_iterator i = unfinished_time.constBegin();
        while (i != unfinished_time.constEnd())
        {
            QString name = i.key();
            if (!name.startsWith("http://"))
                data += name.toUtf8() + '\n' + QByteArray::number(i.value()) + '\n';
            i++;
        }
        data.chop(1); // Remove last '\n'
        if (data.isEmpty())
            return;
        QString filename = QDir::homePath() + "/.moonplayer/unfinished.txt";
        QFile file(filename);
        if (!file.open(QFile::WriteOnly))
            return;
        file.write(data);
        file.close();
    }
    else
    {
        QDir dir = QDir::home();
        dir.cd(".moonplayer");
        if (dir.exists("unfinished.txt"))
            dir.remove("unfinished.txt");
    }
#endif
}