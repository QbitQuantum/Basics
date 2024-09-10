		static THREAD_SIGNATURE abortQueryMultiThread(void *pThis)
		{
			ISession *mSession = MVTApp::startSession();
			TestAbortQuery *threadCtx = new TestAbortQuery;
			threadCtx->mStartAbortQ = ((TestAbortQuery *)pThis)->mStartAbortQ;
			threadCtx->mSession = mSession;
			threadCtx->mStop = ((TestAbortQuery *)pThis)->mStop;
			HTHREAD lThreads;
			createThread(&abortQueryThread,threadCtx,lThreads);
			/*HTHREAD lThreads = CreateThread(NULL,0,&abortQueryThread,threadCtx,0,NULL);
			if(lThreads == NULL)
			{
				printf("Failed to create thread...\n\n");
				return -1;
			}
			SetThreadPriority(lThreads,2);*/
			
			threadCtx->quickTest();
			MVTestsPortability::threadsWaitFor(1, &lThreads);
			mSession->terminate();

			return 0;
		}