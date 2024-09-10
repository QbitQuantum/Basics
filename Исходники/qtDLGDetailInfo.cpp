void qtDLGDetailInfo::OnException(wstring functionName, wstring moduleName, quint64 exceptionOffset, quint64 exceptionCode, DWORD processID, DWORD threadID)
{
	qtDLGNanomite *pMainWindow = qtDLGNanomite::GetInstance();
	pMainWindow->lExceptionCount++;

	tblExceptions->insertRow(tblExceptions->rowCount());
		
	tblExceptions->setItem(tblExceptions->rowCount() - 1,0,
		new QTableWidgetItem(QString("%1").arg(exceptionOffset,16,16,QChar('0'))));
		
	tblExceptions->setItem(tblExceptions->rowCount() - 1,1,
		new QTableWidgetItem(QString("%1").arg(exceptionCode,8,16,QChar('0'))));

	tblExceptions->setItem(tblExceptions->rowCount() - 1,2,
		new QTableWidgetItem(QString().sprintf("%08X / %08X",processID,threadID)));

	if(functionName.length() > 0 )
		tblExceptions->setItem(tblExceptions->rowCount() - 1,3,
			new QTableWidgetItem(QString::fromStdWString(moduleName).append(".").append(QString::fromStdWString(functionName))));


	QString logMessage;

	if(functionName.length() > 0 && moduleName.length() > 0)
		logMessage = QString("[!] Exception - PID: %1 TID: %2 - ExceptionCode: %3 - ExceptionOffset: %4 - %5@%6")
		.arg(processID,6,16,QChar('0'))
		.arg(threadID,6,16,QChar('0'))
		.arg(exceptionCode,8,16,QChar('0'))
		.arg(exceptionOffset,16,16,QChar('0'))
		.arg(QString::fromStdWString(functionName))
		.arg(QString::fromStdWString(moduleName));
	else
		logMessage = QString("[!] Exception - PID: %1 TID: %2 - ExceptionCode: %3 - ExceptionOffset: %4")
		.arg(processID,6,16,QChar('0'))
		.arg(threadID,6,16,QChar('0'))
		.arg(exceptionCode,8,16,QChar('0'))
		.arg(exceptionOffset,16,16,QChar('0'));

	pMainWindow->logView->OnLog(logMessage);
	pMainWindow->UpdateStateBar(1);
}