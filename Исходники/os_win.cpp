void os_init() {
	__cpuid(cpuinfo, 1);

#define MMXSSE 0x02800000
	if ((cpuinfo[3] & MMXSSE) != MMXSSE) {
		::MessageBoxA(NULL, "Mumble requires a SSE capable processor (Pentium 3 / Ahtlon-XP)", "Mumble", MB_OK | MB_ICONERROR);
		exit(0);
	}

	OSVERSIONINFOEXW ovi;
	memset(&ovi, 0, sizeof(ovi));

	ovi.dwOSVersionInfoSize = sizeof(ovi);
	GetVersionEx(reinterpret_cast<OSVERSIONINFOW *>(&ovi));
	bIsWin7 = (ovi.dwMajorVersion >= 7) || ((ovi.dwMajorVersion == 6) &&(ovi.dwBuildNumber >= 7100));
	bIsVistaSP1 = (ovi.dwMajorVersion >= 7) || ((ovi.dwMajorVersion == 6) &&(ovi.dwBuildNumber >= 6001));

#if _MSC_VER == 1800 && defined(_M_X64)
	// Disable MSVC 2013's FMA-optimized math routines on Windows
	// versions earlier than Windows 8 (6.2).
	// There are various issues on OSes that do not support the newer
	// instructions.
	// See issue mumble-voip/mumble#1615.
	if (ovi.dwMajorVersion < 5 || (ovi.dwMajorVersion == 6 && ovi.dwMinorVersion <= 1)) {
		_set_FMA3_enable(0);
	}
#endif

	unsigned int currentControl = 0;
	_controlfp_s(&currentControl, _DN_FLUSH, _MCW_DN);

	SetHeapOptions();
	enableCrashOnCrashes();
	mumble_speex_init();

#ifdef QT_NO_DEBUG
	QString console = g.qdBasePath.filePath(QLatin1String("Console.txt"));
	fConsole = _wfsopen(console.toStdWString().c_str(), L"a+", _SH_DENYWR);

	if (fConsole) {
#if QT_VERSION >= 0x050000
		qInstallMessageHandler(mumbleMessageOutputWithContext);
#else
		qInstallMsgHandler(mumbleMessageOutput);
#endif
	}

	QString hash;
	QFile f(qApp->applicationFilePath());
	if (! f.open(QIODevice::ReadOnly)) {
		qWarning("VersionCheck: Failed to open binary");
	} else {
		QByteArray a = f.readAll();
		if (a.size() > 0) {
			QCryptographicHash qch(QCryptographicHash::Sha1);
			qch.addData(a);
			hash = QLatin1String(qch.result().toHex());
		}
	}

	QString comment = QString::fromLatin1("%1\n%2\n%3").arg(QString::fromLatin1(MUMBLE_RELEASE), QString::fromLatin1(MUMTEXT(MUMBLE_VERSION_STRING)), hash);

	wcscpy_s(wcComment, PATH_MAX, comment.toStdWString().c_str());
	musComment.Type = CommentStreamW;
	musComment.Buffer = wcComment;
	musComment.BufferSize = static_cast<ULONG>(wcslen(wcComment) * sizeof(wchar_t));

	QString dump = g.qdBasePath.filePath(QLatin1String("mumble.dmp"));

	QFileInfo fi(dump);
	QDir::root().mkpath(fi.absolutePath());

	if (wcscpy_s(wcCrashDumpPath, PATH_MAX, dump.toStdWString().c_str()) == 0)
		SetUnhandledExceptionFilter(MumbleUnhandledExceptionFilter);

#endif

	g.qdBasePath.mkpath(QLatin1String("Snapshots"));
	if (bIsWin7)
		SetCurrentProcessExplicitAppUserModelID(L"net.sourceforge.mumble.Mumble");
}