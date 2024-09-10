DWORD WINAPI ContextWorkerThread( LPVOID lpParam ) 
{	
	// Thread ID
	int id = *((int*)lpParam); 
	int NumSimultaneousThreads=TCM_NUM_ELEMENTS_TO_ACCESS;
	ContextStructure* cs[TCM_MAX_SIMULTANEOUS_THREADS];
	//if(NumSimultaneousThreads<MAX_SIMULTANEOUS_THREADS)
	int i,ret=0;

	
	//Get context 
	for (i=0;i<NumSimultaneousThreads;i++)
	{
		
		ret=cm.GetFreeContext(cs[i]);
		if(ret)
		{
			printf("Error creating new context\n");
			return -1;
		}
	}

	Sleep( rand() % TCM_MAX_SLEEP_TIME );

	// Generate the pattern
	char *pattern;
	GeneratePattern(pattern);
	/*int max=64;
	for(int k=0,j=0;k<max/(int)(sizeof(int));k++,j+=sizeof(int))
	{
		printf("%d",*(int *)(pattern+j));
	}*/

	//Copy pattern to context
	for (i=0;i<NumSimultaneousThreads;i++)
	{
		memcpy(cs[i]->cachedb_key,pattern,CM_DEFAULT_CACHEDB_KEY_SIZE);
	//	memcpy(cs[i]->md_lookup_key,pattern,CM_DEFAULT_CACHEDB_KEY_SIZE);
		memcpy(cs[i]->md_lookup_value,pattern,CM_DEFAULT_MD_LOOKUP_VALUE_SIZE);
		memcpy(cs[i]->qdb_key,pattern,CM_DEFAULT_QDB_KEY_SIZE);
		memcpy(cs[i]->qdb_value,pattern,CM_DEFAULT_QDB_VALUE_SIZE);

	}

	//Compare if the context is correct 
	for (i=0;i<NumSimultaneousThreads;i++)
	{
		if(memcmp(cs[i]->cachedb_key,pattern,CM_DEFAULT_CACHEDB_KEY_SIZE)!=0)
		{
			printf("Pattern does not match created value\n");
			return -2;
		}
		//if(memcmp(cs[i]->md_lookup_key,pattern,CM_DEFAULT_CACHEDB_KEY_SIZE)!=0)
		//{
		//	printf("Pattern does not match created value\n");
		//	return -2;
		//}
		if(memcmp(cs[i]->md_lookup_value,pattern,CM_DEFAULT_MD_LOOKUP_VALUE_SIZE)!=0)
		{
			printf("Pattern does not match created value\n");
			return -2;
		}
		if(memcmp(cs[i]->qdb_key,pattern,CM_DEFAULT_QDB_KEY_SIZE)!=0)
		{
			printf("Pattern does not match created value\n");
			return -2;
		}
		if(memcmp(cs[i]->qdb_value,pattern,CM_DEFAULT_QDB_VALUE_SIZE)!=0)
		{
			printf("Pattern does not match created value\n");
			return -2;
		}
	}

	
	// Release Context
	for(i=0;i<NumSimultaneousThreads;i++)
	{
		ret=cm.ReleaseContext(cs[i]);
		if(ret)
		{
			printf("Error releasing context\n");
			return -2;
		}
	}
	printf("Thread %d passed test\n",id);
	delete [] pattern;
	return 0;
	
}