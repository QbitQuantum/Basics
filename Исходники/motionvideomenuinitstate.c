int _reentrant OpenSMVFile(int aa, int b, int *pPtr)
{
	void _Y *       pBuffer = (WORD *) &g_wUserScratchY;
	_packed char    szFilename[MAX_FILENAME_LENGTH];
	SONGFILEINFO    SongInfo;
    int             a, rtn = MVIDEO_ERROR;
    DWORD           dwValue;

    aa;b;pPtr;
	if(stc_iHandle == -1)   {
    	SongInfo.m_wBufferLength = MAX_FILENAME_LENGTH;
    	SongInfo.m_pFilename = (_packed BYTE*)szFilename;
#ifndef USE_PLAYLIST3
        if( SysCallFunction(RSRC_PLAYLIST_CODEBANK,Playlist_GetCurrentSongFileInfo, 0, 0, (INT*)&SongInfo ) == PLAYLIST_SUCCESS )
#else
        if(JpegFile_GetCurrentSongFileInfo(0,0,(INT*)&SongInfo) == PLAYLIST_SUCCESS)
#endif
        {
    
        //open smw file
#ifdef   USE_PLAYLIST5
            g_CurrentFastKey = ((g_PL5_Playback.queue)->pos + g_PL5_Playback.currentplay)->file.lFastKey;
            stc_iHandle = FSFastOpen(g_CurrentFastKey, READ);
            if(stc_iHandle < 0)
#else
            if((stc_iHandle = Fopen( szFilename, (_packed char *)"r" )) < 0)
#endif
            {   stc_iHandle = -1;
                return(rtn);
            }

            // read RIFF trunk
            Fread( stc_iHandle, (void*)pBuffer, 8, DEFAULT_MEMORY, (INT)-1 );
            dwValue = 0;
            for( a = 7; a > 3; a-- )
                dwValue = (dwValue << 8 ) + GetByteFromArrayInY( pBuffer, a );

            //skip wave audio part
            if(Fseek( stc_iHandle, dwValue, SEEK_CUR ) < 0)
            {   Fclose( stc_iHandle );
                stc_iHandle = -1;
                return(rtn);
            }

			//extract motion video graphic header
            Fread( stc_iHandle, (void*)pBuffer, (16*3)+3, DEFAULT_MEMORY, (INT)-1 );
			stc_iByteinJpegBlock = 0;
    		for( a = 23; a > 20; a-- )
    			stc_iByteinJpegBlock = (stc_iByteinJpegBlock << 8) + GetByteFromArrayInY( pBuffer, a );
            stc_iVideoWidth = GetByteFromArrayInY( pBuffer, 9 );
            stc_iVideoHeight = GetByteFromArrayInY( pBuffer, 12 );
            if(stc_iVideoHeight & 0x0F)
                stc_iFrameHeight = (stc_iVideoHeight + 16) - (stc_iVideoHeight % 16);
            else
                stc_iFrameHeight = stc_iVideoHeight;
			stc_iFramePerSec = GetByteFromArrayInY( pBuffer, 24 );
            stc_iFrameDuration = (DWORD)1000000 / (DWORD)stc_iFramePerSec;  // Use us for handling non-integer FrameDuration
    		stc_dwTotalFrame = 0;
    		for( a = 29; a > 26; a-- )
    			stc_dwTotalFrame = (stc_dwTotalFrame << 8) + GetByteFromArrayInY( pBuffer, a );
            stc_dwTotalFrameBackup = stc_dwTotalFrame;
            stc_iFrameDrop = stc_iFrameDuration * 3 / 2;

			stc_iFrameInJpegBlock = 0;
			for( a = 38; a > 35; a-- )
				stc_iFrameInJpegBlock = (stc_iFrameInJpegBlock << 8) + GetByteFromArrayInY( pBuffer, a );

            stc_iDurationInJpegBlock = stc_iFrameDuration * stc_iFrameInJpegBlock;

			//the beginning of the first Jpeg block for frame data
            stc_dwVideoStart = Ftell(stc_iHandle);

            rtn = MVIDEO_SUCCESS;
        }
    }
    return(rtn);
}