void WriteSharedMemory::run()
{
	while(1)
	{
		loadIntoSharedMem();
		_sleep(2);
	}
}