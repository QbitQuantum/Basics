CAccessWriteHandle * CAccessWriteHandle::getInstance()
{
	if(_instance == NULL )
	{
		writeInstanceLock.lock();
		if( _instance == NULL )
		{
			_instance= new CAccessWriteHandle();
		}
		writeInstanceLock.unlock();
	}
	return _instance;
}