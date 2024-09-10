bool isRestart()
{
	ULONG num=0;

	KeWaitForSingleObject(&g_secuHashMutex,Executive,KernelMode,FALSE,NULL);
	for(int i=0 ; i<SECURE_HASH_BUCKET_SIZE ; i++)
	{
		//SECURE_HASH* secuHash = g_secuHash[i];
		SECURE_HASH* secuHash = g_queryHash[i];
		while(secuHash)
		{
			num ++;
			if(num > 30)
			{
				releaseMutex();
				return true;
			}

			secuHash = secuHash->next;
		}
	}
	releaseMutex();
	return false;
}