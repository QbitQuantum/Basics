static bool doOpenUrl(const QUrl& url)
{
#ifdef Q_WS_WIN
	// on Vista it always returns iexplore.exe as default browser
	bool oldStyleDefaultBrowserInfo = QSysInfo::WindowsVersion < QSysInfo::WV_VISTA;

	QFileInfo browserFileInfo(defaultBrowser());
	if (oldStyleDefaultBrowserInfo && browserFileInfo.fileName() == "iexplore.exe") {
		return QProcess::startDetached(browserFileInfo.absoluteFilePath(),
		                               QStringList() << "-new" << url.toEncoded());
	}
	else {
		// FIXME: This is necessary for Qt 4.3.3 to handle all URLs correctly
		QT_WA(
			ShellExecuteW(0, 0, (WCHAR *)QString(url.toEncoded()).utf16(), 0, 0, SW_SHOWNORMAL);
		,
			QByteArray a = QString(url.toEncoded()).toLocal8Bit();	// must not call constData() of a temp object
			ShellExecuteA(0, 0, (CHAR *)a.constData(), 0, 0, SW_SHOWNORMAL);
		)
		return true;