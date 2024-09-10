void SpectraVFSCached::WaitForIO( IOHandle &_handle )
{
#ifdef SPECTRAVFS_ASYNC_IO
	//	Timer t;
	while ( _handle.isSet() )
	{
		SleepEx(1,true);
	}
	//	float time = t.GetElapsedSecs(); 
	//	printf("%f sec\n", time );
#endif
}