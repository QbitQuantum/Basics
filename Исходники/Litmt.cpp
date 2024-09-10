BOOL CLitSingleLock::Lock(DWORD dwTimeOut)
{
	ATLASSERT(m_pObject != NULL || m_hObject != NULL);
	ATLASSERT(!m_bAcquired);
#ifdef _ENABLE_DEBUG_LOCK
	if(!m_strLockFunction.IsEmpty())
		AtlTrace(_T("begin to lock for %s at %s with object %08X\n"), m_strLockFunction,COleDateTime::GetCurrentTime().Format(_T("%M:%S")),this);
#endif
	m_bAcquired = m_pObject->Lock(dwTimeOut);
	return m_bAcquired;
}