void TRACE(const CHAR* format,...)
{
#ifdef _DEBUG

	static const int BufferLen = 1212;        //注意此处大小根据需要修改
	va_list pNextArg;
	CHAR szMessageBuffer[BufferLen];
	szMessageBuffer[BufferLen-1] = '\0';
	va_start(pNextArg,format);
	_vsnprintf_s(szMessageBuffer,BufferLen-1,format, pNextArg);
	va_end(pNextArg);
	OutputDebugStringA(szMessageBuffer);

#endif        //#ifdef _DEBUG
}