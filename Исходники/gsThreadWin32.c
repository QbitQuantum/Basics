GSISemaphoreID gsiCreateSemaphore(gsi_i32 theInitialCount, gsi_i32 theMaxCount, char* theName)
{
	GSISemaphoreID aSemaphore = CreateSemaphoreA(NULL, theInitialCount, theMaxCount, theName);
	if (aSemaphore == NULL)
	{
		gsDebugFormat(GSIDebugCat_Common, GSIDebugType_Misc, GSIDebugLevel_WarmError,
			"Failed to create semaphore\r\n");
	}
	return aSemaphore;
}