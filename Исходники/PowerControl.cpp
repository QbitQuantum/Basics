void powerDown()
{
#ifdef ITALC_BUILD_WIN32
	LocalSystem::enablePrivilege( QString::fromWCharArray( SE_SHUTDOWN_NAME ), true );
	ExitWindowsEx( EWX_POWEROFF | SHUTDOWN_FLAGS, SHUTDOWN_REASON );
	LocalSystem::enablePrivilege( QString::fromWCharArray( SE_SHUTDOWN_NAME ), false );
#else
	if( LocalSystem::User::loggedOnUser().name() == "root" )
	{
		QProcess::startDetached( "poweroff" );
	}
	else
	{
		// Gnome shutdown
		QProcess::startDetached( "dbus-send --session --dest=org.gnome.SessionManager --type=method_call /org/gnome/SessionManager org.gnome.SessionManager.RequestShutdown" );
		// KDE 3 shutdown
		QProcess::startDetached( "dcop ksmserver ksmserver logout 0 2 0" );
		// KDE 4 shutdown
		QProcess::startDetached( "qdbus org.kde.ksmserver /KSMServer logout 0 2 0" );
		// KDE 5 shutdown
		QProcess::startDetached( "dbus-send --dest=org.kde.ksmserver /KSMServer org.kde.KSMServerInterface.logout int32:0 int32:2 int32:2" );
		// generic shutdown via consolekit
		QProcess::startDetached( "dbus-send --system --dest=org.freedesktop.ConsoleKit /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Stop" );
	}
#endif
}