DWORD WINAPI ListeningRoutine(LPVOID lpParam) 
{
	const int SAMPLING_FRAME_RATE = 1; // per second

	BOOL isCapturing = FALSE;
	VideoGrabber* videoGrabber = (VideoGrabber*)lpParam;
	static PTSTR captureFileName;
	
	while (videoGrabber->IsEnabled())
	{
		videoGrabber->GrabFrame(isCapturing);
		int recode;
		if (videoGrabber->mMotionDetectedDuringLastSecond) 
		{
			if (!isCapturing)
			{
				captureFileName = videoGrabber->GetNewDataFileName();
				MakeSureDirectoryPathExists(captureFileName);
				recode = capFileSetCaptureFile(videoGrabber->camhwnd, captureFileName);
				recode = capCaptureSequence(videoGrabber->camhwnd);
				isCapturing = TRUE;
			}
		} 
		else if (isCapturing)
		{
			// ISSUE: Sometimes motion detected when there is no motion in the scene actually.
			//        This is caused by automatic aperture enabled in webcam: the cam adjusting
			//        its aperture to avoid under/overexposition. Hence brightness of pixels is 
			//        changed and motion detection mechanism makes false alarm. However this can
			//        be patched because the effect causes capture of 2-3 sec. video stream. So
			//        quick and dirty solution would be to filter all streams shorter than 4 sec.
			recode = capCaptureStop(videoGrabber->camhwnd);
			recode = GetLastError();
			videoGrabber->GetDataAccumulator()->LogVideo(captureFileName);
			isCapturing = FALSE;
		}

		Sleep(1000/SAMPLING_FRAME_RATE); 
	}
	return FALSE;
}