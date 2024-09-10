bool CProactor::Initializer(const int &threadNum)
{
	iocp = NULL;

	if (!CreateIOCP(threadNum))
	{
		MYERRORPRINTF("CreateIOCP");
		return false;
	}

	if (!CreateThreadPool(threadNum))
	{
		MYERRORPRINTF("CreatetThreadPool");
		return false;
	}
	
	return true;
}