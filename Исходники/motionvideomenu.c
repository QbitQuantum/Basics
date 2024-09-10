void _reentrant SyncSMVFrame(void)
{
    DWORD dw_time, dw_SkipJpegBlock;
    LONG dwCurrentTime;

	//read the current RTC
   	stc_dwCurrentTime = ReadRTC() * 1000;
    if( stc_iHandle != -1)
    {
		//calculate the current time from audio decoder
        dw_time = ((DWORD)g_wSongByteTotalHigh << 24) + (DWORD)g_wSongByteTotalLow;
        dw_time *= (DWORD)1000000;
        dw_time /= (DWORD)g_SmvWave_dwAvgBytesPerSec;      // Elapsed time in us

		//find the nearest JPEG block to the current point of audio decoder
		//the next JPEG block is preferred to the previous block
		//since frame drop within one JPEG block is time consuming

		//If more preference for the next block, increase the value added to dw_time in the following equation
        dw_SkipJpegBlock = (dw_time + (DWORD)((stc_iDurationInJpegBlock * 6) / 10)) / (DWORD)stc_iDurationInJpegBlock;
		if( (dw_SkipJpegBlock * (DWORD)stc_iDurationInJpegBlock) >= dw_time )
		{
			//the next block is selected. Adjust the LastTime to the starting point of next JPEG block
			stc_dwLastTime = stc_dwCurrentTime + ((dw_SkipJpegBlock * (DWORD)stc_iDurationInJpegBlock) - dw_time);
		}
		else
		{
			//the previous block is selected. Adjust the LastTime to the starting point of previous JPEG block.
			//Then, we use frame drop machanism to fine tune the synchronization
			stc_dwLastTime = stc_dwCurrentTime - (dw_time - (dw_SkipJpegBlock * (DWORD)stc_iDurationInJpegBlock));
		}
		//update the number of frame leave for rendering
        stc_dwTotalFrame = stc_dwTotalFrameBackup - dw_SkipJpegBlock * (DWORD)stc_iFrameInJpegBlock;
		//this is the file offset for the selected JPEG block
        dw_SkipJpegBlock = (dw_SkipJpegBlock * stc_iByteinJpegBlock) + stc_dwVideoStart;
        Fseek( stc_iHandle, dw_SkipJpegBlock, SEEK_SET);

		//initialize JPEG decoder the the selected JPEG block
		SmvCurrentJpeg.iHandle = stc_iHandle;
		SmvCurrentJpeg.DisplayParams.x = 0;
		SmvCurrentJpeg.DisplayParams.y = 0;
		SmvCurrentJpeg.DecParams.output_image_width = stc_iVideoWidth;
		SmvCurrentJpeg.DecParams.output_image_height = stc_iFrameHeight*stc_iFrameInJpegBlock;
		SMV_InitDecoder();

    }
    else
	{
		//??
        stc_dwLastTime = stc_dwCurrentTime - stc_iFrameDuration;
    }

	stc_iNumFrameStop = 0;

}