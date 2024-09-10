BOOL SerialCommunicationThread::CloseSerialPort(void)
{
	if (COMFile != NULL)
	{
		//禁止串行端口所有事件
		SetCommMask(COMFile, 0);
		//清除数据终端就绪信号
		EscapeCommFunction(COMFile, CLRDTR);
		//丢弃通信资源的输出或输入缓冲区字符并终止在通信资源上挂起的读、写操操作
		PurgeComm(COMFile, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		CloseHandle(COMFile);
	}
	COMFile = NULL;

	return TRUE;
}