bool SystemUtils::setUserPassword(const QString &password, const QString &user)
{
	QStringList args;
	if(password.isEmpty()) args << "--delete";
	const QString username = user.isEmpty() ? currentUser() : user;
	args << username;
	QProcess process;
	process.start(PASSWD_PROCESS, args);
	if(!process.waitForStarted(1000)) {
		process.kill();
		return false;
	}
	
	process.write(password.toUtf8());
	process.putChar(NEWLINE_CHAR);
	
	// Confirmation
	process.write(password.toUtf8());
	process.putChar(NEWLINE_CHAR);
	
	if(!process.waitForFinished(1000)) {
		process.kill();
		return false;
	}
	
	return process.exitCode() == 0;
}