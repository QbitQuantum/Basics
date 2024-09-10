/*
 =======================================================================================================================
 =======================================================================================================================
 */
DWORD AUDIO_ProcessAList(void)
{
	int k = 1600;

	/* try/except is handled from the call to this function */
	__try
	{
		_control87(_RC_NEAR|_PC_64, _MCW_RC|_MCW_PC);

		if(_AUDIO_ProcessAList_Count_Cycles != NULL && currentromoptions.RSP_RDP_Timing)
		{
			k = _AUDIO_ProcessAList_Count_Cycles();
		}
		else if(_AUDIO_ProcessAList != NULL) 
			_AUDIO_ProcessAList();

        RestoreOldRoundingMode(((uint32) cCON31 & 0x00000003) << 8);
	}

	__except(NULL, EXCEPTION_EXECUTE_HANDLER)
	{
		/* Some people won't have a sound card. No error. */
		//MessageBox(0, "Exception", "", 0);
	}

	return k;
}