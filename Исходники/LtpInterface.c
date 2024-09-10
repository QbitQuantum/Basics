int	  endLtp(LtpInterfaceType *ltpInterfaceP)
{
	
	//
	Boolean clearProfileB = false;
	applicationEnd();

	DeInitAudio( ltpInterfaceP->playbackP,false);
	DeInitAudio( ltpInterfaceP->recordP,false);
	ltpInterfaceP->playbackP = 0;
	ltpInterfaceP->recordP = 0;
	#ifdef _LTP_	
	
		if(ltpInterfaceP->ltpObjectP->sipOnB==false)
		{
			
		
			#ifdef _OWN_THREAD_
	
			ltpInterfaceP->pthreadstopB = true;
			while(ltpInterfaceP->pthreadstopB)
			{
				sleep(1);
			}
			//pthread_cancel(ltpInterfaceP->pthObj);
			//pthread_exit(ltpInterfaceP->pthObj);
			ltpInterfaceP->pthObj = 0;
		}	
		#endif
	#endif
	if(ltpInterfaceP->ltpObjectP->sipOnB)
	{
		sip_pj_DeInit(ltpInterfaceP->ltpObjectP);
		ltpInterfaceP->pjsipStartB = false;
	}
	if (ltpInterfaceP->ltpObjectP->ltpUserid[0]==0)
	{
		clearProfileB = true;
	}
	if(terminateThread()==0)
	{	
		free(ltpInterfaceP->ltpObjectP);
	}	
		ltpInterfaceP->ltpObjectP  = 0;
	
		/* destroys the mutex */
	ltpInterfaceP->pthreadstopB = true;
		pthread_mutex_destroy(&mutex);
	free(ltpInterfaceP);
	if(clearProfileB)
	{
		profileClear();
	}
	return 0;
}