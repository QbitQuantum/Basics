void WindowsIdleDetector::timeout() {
    LASTINPUTINFO lif;
    lif.cbSize = sizeof( lif );
    const bool ret = GetLastInputInfo( &lif );
    if ( !ret ) {
        qWarning() << "Idle detection: GetLastInputInfo failed.";
        return;
    }

    const qint64 dwTime = static_cast<qint64>( lif.dwTime );
    const qint64 ctk = static_cast<qint64>( GetTickCount() );
    const int idleSecs = ( ctk - dwTime ) / 1000;
    if ( idleSecs >= idlenessDuration() )
        maybeIdle( IdlePeriod(QDateTime::currentDateTime().addSecs( -idleSecs ),
                              QDateTime::currentDateTime() ) );
}