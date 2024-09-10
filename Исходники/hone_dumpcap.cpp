//-----------------------------------------------------------------------------
bool HoneDumpcap::Initialize(QStringList args, QString appPath)
{
	m_args = args;
	if (!ParseArgs()) {
		return false;
	}

#ifdef WIN32
	m_dumpcapFileName = QString("%1/dumpcap_orig.exe").arg(appPath);
#else
	m_dumpcapFileName = QString("%1/dumpcap_orig").arg(appPath);
#endif

	if (m_operation == OperationCapture) {
		if (m_haveHoneInterface) {
			m_captureStart = QDateTime::currentMSecsSinceEpoch();
			if (m_parentPid.isEmpty()) {
				Log("Capturing on 'Hone'");
			}
			if (!OpenDriver() || !OpenCaptureFile()) {
				return false;
			}
		} else {
			connect(&m_dumpcapProcess, SIGNAL(error(QProcess::ProcessError)),      this, SLOT(OnError(QProcess::ProcessError)));
			connect(&m_dumpcapProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(OnFinished(int,QProcess::ExitStatus)));
			connect(&m_dumpcapProcess, SIGNAL(readyReadStandardError()),           this, SLOT(OnReadyReadStandardError()));
			connect(&m_dumpcapProcess, SIGNAL(readyReadStandardOutput()),          this, SLOT(OnReadyReadStandardOutput()));
			m_dumpcapProcess.start(m_dumpcapFileName, m_args);
			m_needEventLoop = true;
		}
	}
	return true;
}