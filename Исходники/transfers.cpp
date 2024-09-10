void Transfers::stop()
{
    if ( !m_bActive )
    {
        return;
    }

    systemLog.postLog( LogSeverity::Notice, qPrintable( tr( "Stopping transfers..." ) ) );

    m_bActive = false;

    transfersThread.exit( 0, true );
    downloads.stop();
}