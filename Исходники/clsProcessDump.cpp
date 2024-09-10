clsProcessDump::clsProcessDump(HANDLE processHandle, DWORD processID, QString filePath, QWidget *pParent)
{
	QString dumpFilePath = QFileDialog::getSaveFileName(pParent,
		"Please select a path to save the dump",
		QString("DUMP_%1_%2.dmp").arg(filePath).arg(processID,6,10,QChar('0')),
		"Dump files (*.dmp)",
		NULL,
		QFileDialog::DontUseNativeDialog);

	if(dumpFilePath.length() <= 0) return;

	HANDLE dumpFile = CreateFileW(dumpFilePath.toStdWString().c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 

	if(dumpFile != INVALID_HANDLE_VALUE) 
	{
		MINIDUMP_TYPE dumpTyp   = (MINIDUMP_TYPE)(	MiniDumpWithFullMemoryInfo				| 
													MiniDumpWithIndirectlyReferencedMemory	|
													MiniDumpWithFullMemory					|
													MiniDumpWithHandleData					|	 
													MiniDumpWithProcessThreadData			|
													MiniDumpWithThreadInfo					| 
													MiniDumpWithUnloadedModules	); 

		if(MiniDumpWriteDump(processHandle, processID, dumpFile, dumpTyp, NULL, NULL, NULL))
			QMessageBox::information(pParent,"Nanomite","Process dump was successfull!",QMessageBox::Ok,QMessageBox::Ok);
	
		CloseHandle(dumpFile); 
		return;
	}

	QMessageBox::critical(pParent,"Nanomite","Process dump has failed!",QMessageBox::Ok,QMessageBox::Ok);
}