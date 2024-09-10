void __fastcall TFrameThread::Execute()
{

	while(!Terminated) {
		_clearfp();
//	printf("          %d\n", bmpQueue->size());
		if(!bmpQueue->empty()) {
			BITMAP * aBmp = NULL;
			unsigned int res = WaitForSingleObject(hMutex,INFINITE);
			if (res!=WAIT_OBJECT_0) {ReleaseMutex(hMutex);continue;}
			__try
			{
				aBmp = bmpQueue->front();
				bmpQueue->pop();
			}
			__finally
			{
				ReleaseMutex(hMutex);

			}

  			MainCaptureForm->DoFrame(aBmp);

			destroy_bitmap(aBmp);


		} else {