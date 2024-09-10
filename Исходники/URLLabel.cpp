void
URLLabel::openURL( const QUrl& url )
{
    if ( !url.isEmpty() )
    {
        LOGL( 3, "Opening in browser: " << url );

#ifndef Q_WS_WIN
        QDesktopServices::openUrl( QUrl::fromEncoded( url.toString().toUtf8() ) );
#else
        QDesktopServices::openUrl( url );
#endif
    }
}