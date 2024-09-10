int
File::unlock()
{
	if (m_hdl == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));
	if (!UnlockFileEx(m_hdl, 0, 0xffffffff, 0xffffffff, &ov))
	{
		return -1;
	}

	return 0;
}