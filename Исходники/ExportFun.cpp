bool CFunctionInterface::StartWork()
{
	m_hThread = (HANDLE)_beginthread( WorkThreadPro, 0, this);

	return true;
}