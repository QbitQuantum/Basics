// The intent of this function is to return the proper location for
// user-controlled settings on the current platform
// i.e. PROFILE\Application Data\xca on windows, HOME/.xca on UNIX,
// ~/Library/Preferences/xca on Mac OS X
QString getUserSettingsDir()
{
	QString rv;
#if defined(Q_OS_WIN32)
	LPITEMIDLIST pidl = NULL;
	TCHAR buf[255] = "";
	if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl))) {
	SHGetPathFromIDList(pidl, buf);
	}
	rv = buf;
	rv += QDir::separator();
	rv += "xca";
#elif defined(Q_OS_MAC)
  #if QT_VERSION < 0x050000
	rv = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
	rv.insert(rv.count() - QCoreApplication::applicationName().count(),
		QCoreApplication::organizationName());
  #else
	rv = QStandardPaths::writableLocation(
			QStandardPaths::GenericDataLocation) + "/data/" +
		QCoreApplication::organizationName() + "/" +
		QCoreApplication::applicationName();
  #endif
#else
	rv = QDir::homePath();
	rv += QDir::separator();
	rv += ".xca";
#endif
	return rv;
}