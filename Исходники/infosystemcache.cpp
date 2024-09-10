void
InfoSystemCache::pruneTimerFired()
{
    qDebug() << Q_FUNC_INFO << "Pruning infosystemcache";
    qlonglong currentMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();

    for ( int i = InfoNoInfo; i <= InfoLastInfo; i++ )
    {
        InfoType type = (InfoType)(i);
        QHash< QString, QString > fileLocationHash = m_fileLocationCache[type];
        const QString cacheDirName = m_cacheBaseDir + QString::number( (int)type );
        QFileInfoList fileList = QDir( cacheDirName ).entryInfoList( QDir::Files | QDir::NoDotAndDotDot );
        foreach ( QFileInfo file, fileList )
        {
            QString baseName = file.baseName();
            if ( file.suffix().toLongLong() < currentMSecsSinceEpoch )
            {
                if ( !QFile::remove( file.canonicalFilePath() ) )
                    tLog() << "Failed to remove stale cache file" << file.canonicalFilePath();
                else
                    qDebug() << "Removed stale cache file" << file.canonicalFilePath();
            }
            if ( fileLocationHash.contains( baseName ) )
                fileLocationHash.remove( baseName );
        }
        m_fileLocationCache[type] = fileLocationHash;
    }