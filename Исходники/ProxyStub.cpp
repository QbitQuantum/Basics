void ProxyStub::UnPackage(void*& pDataPool, tstring& data)
{
	TCHAR* pData = static_cast<TCHAR*>(pDataPool);
	data = pData;

	pDataPool = static_cast<void*>(pData + data.length() + 1);

}