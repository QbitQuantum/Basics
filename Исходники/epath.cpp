bool EPath::mountNetwork(QChar drive) {
	// Mount network drive
	QProcess net_use;
	LAPP_ << "Mounting network path to " << drive.toAscii();
	QString mount_command = QString("net use %1: \"%2\"").arg(drive).arg(m_path);
	LDEBUG_ << "Executing: " << QSTR(mount_command);
	net_use.start(mount_command);
	net_use.waitForFinished();
	if (net_use.exitCode() != 0)
		return false;

	m_remote_path_mounted = true;

	m_usable_drive = drive;

	return true;
}