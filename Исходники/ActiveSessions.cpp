void CActiveSessions::SendEvent(long id, PBYTE pData, size_t size)
{
	if(_thread <= 0)
		throw(ERR_UNKNOW);

#ifdef _OFS_WRITE_TRACE_INFO
	TCHAR str[80];
	_stprintf_s(str, 80, _T("[Active Session]->[SendEvent] Id = %ld"), id);
	//g_SupportClass.AddToLog(1, str);
	//	TRACE("\r\n Active Session's  SendEvent ID = %ld Size = %Iu Data = (*) %s (*)",ID,Size,pData);
#endif

	TCHAR sid[COFSMatrix::_sidSize];
	CActiveSession* pActiveSession = _matrix.Get(id, sid, COFSMatrix::_sidSize);
	ASSERT(pActiveSession != NULL);
	if(pActiveSession != NULL)
	{
		/// Использование
		pActiveSession->SetEvent(pData, size);
		/// После окончания использования освободить
		pActiveSession->ReleasePointer();
	}
}