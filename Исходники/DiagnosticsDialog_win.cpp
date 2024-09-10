DiagnosticsDialog::DiagnosticsDialog( QWidget *parent )
:	QDialog( parent )
{
	setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose, true );

	QString info;
	QTextStream s( &info );

	s << "<b>" << tr("Locale (time-, number format / codepage):") << "</b> ";
	QLocale::Language language = QLocale::system().language();
	QString locale = (language == QLocale::C ? "English/United States" : QLocale::languageToString( language ) );
	CPINFOEX CPInfoEx;
	if ( GetCPInfoEx( GetConsoleCP(), 0, &CPInfoEx ) != 0 )
		locale.append( " / " ).append( CPInfoEx.CodePageName );
	s << locale << "<br />";
	s << "<b>" << tr("User rights: ") << "</b>" << getUserRights() << "<br />";

	QStringList base = Common::packages( QStringList() << "Eesti ID kaardi tarkvara", false );
	if ( !base.isEmpty() )
		s << "<b>" << tr("Base version:") << "</b> " << base.join( "<br />" ) << "<br />";
	s << "<b>" << tr("ID-card utility version:") << "</b> "<< QCoreApplication::applicationVersion() << "<br />";

	s << "<b>" << tr("OS:") << "</b> " << Common::applicationOs() << "<br />";
	s << "<b>" << tr("CPU:") << "</b> " << getProcessor() << "<br /><br />";

	s << "<b>" << tr("Library paths:") << "</b> " << QCoreApplication::libraryPaths().join( ";" ) << "<br />";

	s << "<b>" << tr("Libraries") << ":</b><br />";
	s << getLibVersion( "digidoc" ) << "<br />";
	s << getLibVersion( "digidocpp" ) << "<br />";
	s << getLibVersion( "advapi32" ) << "<br />";
	s << getLibVersion( "crypt32" ) << "<br />";
	s << getLibVersion( "winscard" ) << "<br />";
	s << getLibVersion( "esteidcsp|esteidcm" ) << "<br />";
	s << getLibVersion( "libeay32" ) << "<br />";
	s << getLibVersion( "ssleay32" ) << "<br />";
	s << getLibVersion( "opensc-pkcs11" ) << "<br />";
	s << "QT (" << qVersion() << ")<br />" << "<br />";

	s << "<b>" << tr("Smart Card service status: ") << "</b>" << " " << (isPCSCRunning() ? tr("Running") : tr("Not running")) << "<br /><br />";

	s << "<b>" << tr("Card readers") << ":</b><br />" << getReaderInfo() << "<br />";

	QStringList browsers = Common::packages( QStringList() << "Mozilla" << "Google Chrome" );
	QSettings reg( "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Internet Explorer", QSettings::NativeFormat );
	browsers << QString( "Internet Explorer (%1)" ).arg( reg.value( "Version" ).toString() );
	s << "<b>" << tr("Browsers:") << "</b><br />" << browsers.join( "<br />" ) << "<br /><br />";

	diagnosticsText->setHtml( info );

	details = buttonBox->addButton( tr( "More info" ), QDialogButtonBox::HelpRole );
}