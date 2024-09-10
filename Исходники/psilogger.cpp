PsiLogger::PsiLogger(const QString& logFileName)
	: QObject(QCoreApplication::instance())
	, file_(0)
	, stream_(0)
{
	bool enableLogging = false;
#ifdef Q_WS_WIN
	{
		QSettings sUser(QSettings::UserScope, "Yandex", "Online");
		enableLogging = sUser.contains("extra_log");
	}
#endif

	{
		char* p = getenv("ENABLE_LOGGING");
		if (p) {
			enableLogging = true;
		}

#ifdef YAPSI
		QString extraLogFileName = ApplicationInfo::homeDir() + "/extra-log";
		if (QFile::exists(extraLogFileName))
			enableLogging = true;
#endif
	}

	if (!enableLogging)
		return;

#ifdef YAPSI
	QString fileName = ApplicationInfo::homeDir() + "/";
	if (logFileName.isEmpty())
		fileName += "yachat-log.txt";
	else
		fileName += logFileName;
#else
	QString fileName = QDir::homePath() + "/";
	if (logFileName.isEmpty())
		fileName += "psilogger.txt";
	else
		fileName += logFileName;
#endif
	QFile::remove(fileName);
	file_ = new QFile(fileName);
	if (!file_->open(QIODevice::WriteOnly)) {
		qWarning("unable to open log file");
	}
	
	stream_ = new QTextStream();
	stream_->setDevice(file_);
	stream_->setCodec("UTF-8");
	qWarning("Logging started: '%s'", qPrintable(fileName));
#ifdef YAPSI
	log(QString("*** LOG STARTED %1 (%2 / %3) %4")
	    .arg(YaDayUse::ver())
	    .arg(YaDayUse::osId())
	    .arg(YaDayUse::osVer())
	    .arg(QDateTime::currentDateTime().toString(Qt::ISODate)));
#else
	log(QString("*** LOG STARTED %1")
	    .arg(QDateTime::currentDateTime().toString(Qt::ISODate)));
#endif
}