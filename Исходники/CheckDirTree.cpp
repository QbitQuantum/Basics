void
CheckDirModel::getFileInfoResult()
{
#ifdef Q_OS_MAC
    QProcess* p = qobject_cast< QProcess* >( sender() );
    Q_ASSERT( p );

    QByteArray res = p->readAll().trimmed();
    qDebug() << "Got output from GetFileInfo:" << res;
    // 1 means /Volumes is hidden, so we show it while the dialog is visible
    if ( res == "1" )
    {
        // Remove the hidden flag for the /Volumnes folder so all mount points are visible in the default (Q)FileSystemModel
        QProcess* showProcess = new QProcess( this );
        qDebug() << "Running SetFile:" << QString( "%1 -a v %2" ).arg( m_setFilePath ).arg( s_macVolumePath );
        showProcess->start( QString( "%1 -a v %2" ).arg( m_setFilePath ).arg( s_macVolumePath ) );
        connect( showProcess, SIGNAL( readyReadStandardError() ), this, SLOT( processErrorOutput() ) );
        m_shownVolumes = true;

        QTimer::singleShot( 500, this, SLOT( volumeShowFinished() ) );
    }

    p->terminate();
    p->deleteLater();
#endif
}