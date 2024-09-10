idupdater::idupdater( QObject *parent )
:	QNetworkAccessManager( parent )
,	m_autoupdate( false )
,	m_autoclose( false )
,	w(0)
{
	QLocale::Language language = QLocale::system().language();
	QString locale = language == QLocale::C ? "English/United States" : QLocale::languageToString( language );
#ifdef Q_OS_WIN
	CPINFOEX CPInfoEx = { 0 };
	if( GetCPInfoExW( GetConsoleCP(), 0, &CPInfoEx ) != 0 )
		locale += " / " + QString( (QChar*)CPInfoEx.CodePageName );
#else
	QString ctype = QProcessEnvironment::systemEnvironment().value( "LC_CTYPE" );
	locale += " / " + (!ctype.isEmpty() ? ctype : QProcessEnvironment::systemEnvironment().value( "LANG" ));
#endif

	QPCSC pcsc;
	QString userAgent = QString( "%1/%2 (%3) Locale: %4 Devices: %5")
		.arg( qApp->applicationName(), InstallChecker::installedVersion("{58A1DBA8-81A2-4D58-980B-4A6174D5B66B}"), applicationOs(), locale, pcsc.drivers().join("/") );
	qDebug() << "User-Agent:" << userAgent;
	request.setRawHeader( "User-Agent", userAgent.toUtf8() );
	connect( this, SIGNAL(finished(QNetworkReply*)), SLOT(reply(QNetworkReply*)) );
}