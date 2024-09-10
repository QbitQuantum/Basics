void Lout::RemoveAllOutputs()
{
	FlushAll();
	Locker lock( myLock );
	(void)lock;
	myOutput.erase( myOutput.begin(), myOutput.end() );
}