bool SystemSession::logout(bool force) const
{
#ifdef Q_OS_LINUX
	if(mCapabilities & GnomeSessionManager)
	{
		QDBusInterface dbusInterface("org.gnome.SessionManager", "/org/gnome/SessionManager", "org.gnome.SessionManager", QDBusConnection::sessionBus());
		unsigned int code = (force ? 2 : 1);
		QDBusMessage reply = dbusInterface.call("Logout", code);

		if(reply.type() != QDBusMessage::ErrorMessage)
			return true;
	}
	if(mCapabilities & KdeKSMServer)
	{
		QDBusInterface dbusInterface("org.kde.ksmserver", "/KSMServer", "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
		QDBusMessage reply = dbusInterface.call("logout", 0, 3, (force ? 2 : 1));

		if(reply.type() != QDBusMessage::ErrorMessage)
			return true;
	}

	return false;
#endif
#ifdef Q_OS_WIN
	return ExitWindowsEx(EWX_LOGOFF | (force ? EWX_FORCE : 0), SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER);
#endif
}