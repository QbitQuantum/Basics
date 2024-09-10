QString OSInfo::getOSVersion() {
	static QString qsCached;

	if (! qsCached.isNull())
		return qsCached.isEmpty() ? QString() : qsCached;

	QString os;

#if defined(Q_OS_WIN)
	OSVERSIONINFOEXW ovi;
	memset(&ovi, 0, sizeof(ovi));

	ovi.dwOSVersionInfoSize=sizeof(ovi);
	if (!GetVersionEx(reinterpret_cast<OSVERSIONINFOW *>(&ovi))) {
		return QString();
	}

	os.sprintf("%d.%d.%d.%d", ovi.dwMajorVersion, ovi.dwMinorVersion, ovi.dwBuildNumber, (ovi.wProductType == VER_NT_WORKSTATION) ? 1 : 0);
#elif defined(Q_OS_MAC)
	SInt32 major, minor, bugfix;
	OSErr err = Gestalt(gestaltSystemVersionMajor, &major);
	if (err == noErr)
		err = Gestalt(gestaltSystemVersionMinor, &minor);
	if (err == noErr)
		err = Gestalt(gestaltSystemVersionBugFix, &bugfix);
	if (err != noErr)
		return QString::number(QSysInfo::MacintoshVersion, 16);

	char *buildno = NULL;
	char buildno_buf[32];
	size_t sz_buildno_buf = sizeof(buildno);
	int ret = sysctlbyname("kern.osversion", buildno_buf, &sz_buildno_buf, NULL, 0);
	if (ret == 0) {
		buildno = &buildno_buf[0];
	}

	os.sprintf("%lu.%lu.%lu %s",
	           static_cast<unsigned long>(major),
	           static_cast<unsigned long>(minor),
	           static_cast<unsigned long>(bugfix),
	           buildno ? buildno : "unknown");
#else
#ifdef Q_OS_LINUX
	QProcess qp;
	QStringList args;
	args << QLatin1String("-s");
	args << QLatin1String("-d");
	qp.start(QLatin1String("lsb_release"), args);
	if (qp.waitForFinished(5000)) {
		os = QString::fromUtf8(qp.readAll()).simplified();
		if (os.startsWith(QLatin1Char('"')) && os.endsWith(QLatin1Char('"')))
			os = os.mid(1, os.length() - 2).trimmed();
	}
	if (os.isEmpty())
		qWarning("OSInfo: Failed to execute lsb_release");

	qp.terminate();
	if (! qp.waitForFinished(1000))
		qp.kill();
#endif
	if (os.isEmpty()) {
		struct utsname un;
		if (uname(&un) == 0) {
			os.sprintf("%s %s", un.sysname, un.release);
		}
	}
#endif

	if (! os.isNull())
		qsCached = os;
	else
		qsCached = QLatin1String("");

	return qsCached;
}