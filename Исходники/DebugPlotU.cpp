HRESULT __stdcall Log(
	__in const char * channelName,
	__in const char * format,
	...
)
{
	if ( (channelName == 0) ||
		 (format == 0) )
	{
		return E_INVALID_PARAMETER;
	}

	SharedChannelW * ch = ChannelObjLookUp::GetSharedChannel(channelName, CH_TYPE_LOG, 0);

	if (!ch->IsType(CH_TYPE_LOG))
		return E_PLOT_TYPE_MISMATCH;

	ch->Lock();

	const size_t TEXT_BUF_LEN = 4096;
	char * textBuffer = ch->GetTextBuffer(TEXT_BUF_LEN);

	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	_snprintf_s(
		textBuffer, 
		TEXT_BUF_LEN, 
		_TRUNCATE, 
		"[%d:%d:%.3f]: ",
		sysTime.wHour, 
		sysTime.wMinute,
		(double)(sysTime.wSecond*1000 + sysTime.wMilliseconds)/1000);

	size_t size1 = strlen(textBuffer);
	char * ptr2 = textBuffer + size1;

	va_list ap;
	va_start(ap, format);
	_vsnprintf_s(ptr2, TEXT_BUF_LEN - size1, _TRUNCATE, format, ap);
	va_end(ap);	

	ch->Write((const char *)textBuffer, strlen(textBuffer));

	ch->Unlock();

	return S_OK;
}