  void WaveTest_Play(char *pszFileName)
 {
     HWAVELIB hWaveLib = WaveLib_Init(pszFileName, FALSE);
	 PWAVELIB pWaveLib = (PWAVELIB)hWaveLib;
	 int x;
	 // hWaveLib = WaveLib_Init(pszFileName, FALSE);
     FileSize = GetSize();
	 FileLength = GetLength();
	 //waveOutGetDevCaps(&pWaveLib->hThread,&devicecapability, sizeof(devicecapability));
	 if(hWaveLib)
	 {
		 do
		 {
			PlaybackTimeNow =GetPlayTime(hWaveLib);
			PlaybackPercentage = (PlaybackTimeNow/total_time)*100;
			//printf("Querying device capabilities...\n");

			//loadbar(PlaybackTimeNow,total_time,10,10);
			//getPlaybackTimePercentage(FileLength, PlaybackTimeNow);
			showbar();
			
			if (PlaybackPercentage >= 0 && PlaybackPercentage < 10)
			 {
				 //waveOutGetVolume(pWaveLib->hWaveOut,&volume);
				 nextvolume = 0x0000;
				 nextvolume = ((int)PlaybackPercentage*25)<<8;
				 waveOutSetVolume(pWaveLib->hWaveOut,nextvolume);
				 printf("Ch1++|Vol:%X|", nextvolume);
			 }
			 else if (PlaybackPercentage >= 10 && PlaybackPercentage < 20)
			 {
				 nextvolume = 0xFF00 -  (((int)(PlaybackPercentage-10)*25)<<8);
				 waveOutSetVolume(pWaveLib->hWaveOut,nextvolume);
				 printf("Ch1--|Vol:%X|", nextvolume);
			 }
			 else if (PlaybackPercentage >= 20 && PlaybackPercentage < 30)
			 {
				 nextvolume = 0x0000;
				 nextvolume = ((int)(PlaybackPercentage-20)*25);
				 waveOutSetVolume(pWaveLib->hWaveOut,nextvolume);
				 printf("Ch2++|Vol:00%X|", nextvolume);
			 }
			 else if (PlaybackPercentage >= 30 && PlaybackPercentage < 40)
			 {
				 nextvolume = 0x00FF - ((int)(PlaybackPercentage-30)*25);
				 waveOutSetVolume(pWaveLib->hWaveOut,nextvolume);
				 printf("Ch2--|Vol:00%X|", nextvolume);
			 }
			 else if (PlaybackPercentage >= 40 && PlaybackPercentage < 50)
			 {
				 nextvolume = 0x0000;
				 nextvolume = (((int)(PlaybackPercentage-40)*25<<8)) | ((int)(PlaybackPercentage-40)*25);
				 waveOutSetVolume(pWaveLib->hWaveOut,nextvolume);
				 printf("Ch1&2++|Vol:%X|", nextvolume);
			 }
			 else if (PlaybackPercentage >= 50 && PlaybackPercentage < 70)
			 {
				 playbackrate = ((((int)(PlaybackPercentage-50)*25)/64)<<16);
				 result = waveOutSetPlaybackRate(pWaveLib->hWaveOut,playbackrate);
				 if (result == MMSYSERR_INVALHANDLE){
					 printf("nohandle");}
				 else if (result == MMSYSERR_NODRIVER)
					 printf("nodriver");
				 else if (result == MMSYSERR_NOMEM)
					 printf("nomem");
				 else if (result == MMSYSERR_NOTSUPPORTED){
					 printf("notsup");//printf("WARNING: Changing playback rate unsupported.\n");
				 }
				 else if (result == MMSYSERR_NOERROR);
					 printf("@%dx|", (((int)(PlaybackPercentage-50)*25)/64));
			 }
			 else if (PlaybackPercentage >= 70 && PlaybackPercentage < 90)
			 {
				 //playbackrate = ((((int)(PlaybackPercentage-70)*25)/64)<<16);
				 waveOutGetPlaybackRate(pWaveLib->hWaveOut,&playbackrate);
				 //printf("@%dx|", (((int)(PlaybackPercentage-50)*25)/64));
				 printf("@%Xx|", playbackrate);
			 }
		 }

		 while(PlaybackTimeNow < FileLength);
		 printf("Playbacktime: %d | FileLength: %d",PlaybackTimeNow,total_time);
		 WaveLib_UnInit(hWaveLib);
	 }
	 else
	 {
		 WaveTest_PrintError();
	 }
     
 }