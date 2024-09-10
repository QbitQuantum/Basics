PRL_RESULT CDspHaClusterHelper::runProgram(const QString & sPath, const QStringList & lstArgs, QProcess & proc)
{
	WRITE_TRACE(DBG_INFO, "run %s %s", qPrintable(sPath), qPrintable(lstArgs.join(" ")));
	proc.start(sPath, lstArgs);
	if (!proc.waitForStarted(HAMAN_START_TMO)) {
		WRITE_TRACE(DBG_FATAL, "Failed to run %s : %s",
				QSTR2UTF8(sPath), QSTR2UTF8(proc.errorString()));
		return PRL_ERR_CLUSTER_RESOURCE_ERROR;
	}
	if (!proc.waitForFinished(HAMAN_EXEC_TMO)) {
		WRITE_TRACE(DBG_FATAL, "Failed to wait for finished %s : %s",
				QSTR2UTF8(sPath), QSTR2UTF8(proc.errorString()));
		proc.terminate();
		return PRL_ERR_CLUSTER_RESOURCE_ERROR;
	}
	if (proc.exitCode()) {
		WRITE_TRACE(DBG_FATAL, "%s failed : retcode : %d, stdout: [%s] stderr: [%s]",
			QSTR2UTF8(sPath),
			proc.exitCode(),
			proc.readAllStandardOutput().constData(),
			proc.readAllStandardError().constData()
			);
		return PRL_ERR_CLUSTER_RESOURCE_ERROR;
	}

	return PRL_ERR_SUCCESS;
}