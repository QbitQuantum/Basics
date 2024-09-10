void asCMemoryMgr::FreeUnusedMemory()
{
	// It's necessary to protect the scriptNodePool from multiple 
	// simultaneous accesses, as the parser is used by several methods
	// that can be executed simultaneously.
	ENTERCRITICALSECTION(cs);

	int n;
	for( n = 0; n < (signed)scriptNodePool.GetLength(); n++ )
		userFree(scriptNodePool[n]);
	scriptNodePool.Allocate(0, false);

	LEAVECRITICALSECTION(cs);

	// The engine already protects against multiple threads 
	// compiling scripts simultaneously so this pool doesn't have 
	// to be protected again.
	for( n = 0; n < (signed)byteInstructionPool.GetLength(); n++ )
		userFree(byteInstructionPool[n]);
	byteInstructionPool.Allocate(0, false);
}