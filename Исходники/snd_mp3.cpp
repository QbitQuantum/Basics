// returns qtrue while still playing normally, else qfalse for either finished or request-offset-error
//
qboolean MP3Stream_GetSamples( channel_t *ch, int startingSampleNum, int count, short *buf, qboolean bStereo )
{
	qboolean qbStreamStillGoing = qtrue;

	const int iQuarterOfSlidingBuffer		=  sizeof(ch->MP3SlidingDecodeBuffer)/4;
	const int iThreeQuartersOfSlidingBuffer	= (sizeof(ch->MP3SlidingDecodeBuffer)*3)/4;

//	Com_Printf("startingSampleNum %d\n",startingSampleNum);

	count *= 2/* <- = SOF2; ch->sfx->width*/;	// count arg was for words, so double it for bytes;

	// convert sample number into a byte offset... (make new variable for clarity?)
	//
	startingSampleNum *= 2 /* <- = SOF2; ch->sfx->width*/ * (bStereo?2:1);

	if ( startingSampleNum < ch->iMP3SlidingDecodeWindowPos)
	{
		// what?!?!?!   smegging time travel needed or something?, forget it
		memset(buf,0,count);
		return qfalse;
	}

//	Com_OPrintf("\nRequest: startingSampleNum %d, count %d\n",startingSampleNum,count);
//	Com_OPrintf("WindowPos %d, WindowWritePos %d\n",ch->iMP3SlidingDecodeWindowPos,ch->iMP3SlidingDecodeWritePos);

//	qboolean _bDecoded = qfalse;

	while (!
		(
			(startingSampleNum			>= ch->iMP3SlidingDecodeWindowPos)
			&&
			(startingSampleNum + count	<  ch->iMP3SlidingDecodeWindowPos + ch->iMP3SlidingDecodeWritePos)
			)
			)
	{
//		if (!_bDecoded)
//		{
//			Com_Printf(S_COLOR_YELLOW"Decode needed!\n");
//		}
//		_bDecoded = qtrue;
//		Com_OPrintf("Scrolling...");

		int _iBytesDecoded = MP3Stream_Decode( (LP_MP3STREAM) &ch->MP3StreamHeader, bStereo );	// stereo only for music, so this is safe
//		Com_OPrintf("%d bytes decoded\n",_iBytesDecoded);
		if (_iBytesDecoded == 0)
		{
			// no more source data left so clear the remainder of the buffer...
			//
			memset(ch->MP3SlidingDecodeBuffer + ch->iMP3SlidingDecodeWritePos, 0, sizeof(ch->MP3SlidingDecodeBuffer)-ch->iMP3SlidingDecodeWritePos);
//			Com_OPrintf("Finished\n");
			qbStreamStillGoing = qfalse;
			break;
		}
		else
		{
			memcpy(ch->MP3SlidingDecodeBuffer + ch->iMP3SlidingDecodeWritePos,ch->MP3StreamHeader.bDecodeBuffer,_iBytesDecoded);

			ch->iMP3SlidingDecodeWritePos += _iBytesDecoded;

			// if reached 3/4 of buffer pos, backscroll the decode window by one quarter...
			//
			if (ch->iMP3SlidingDecodeWritePos > iThreeQuartersOfSlidingBuffer)
			{
				memmove(ch->MP3SlidingDecodeBuffer, ((byte *)ch->MP3SlidingDecodeBuffer + iQuarterOfSlidingBuffer), iThreeQuartersOfSlidingBuffer);
				ch->iMP3SlidingDecodeWritePos -= iQuarterOfSlidingBuffer;
				ch->iMP3SlidingDecodeWindowPos+= iQuarterOfSlidingBuffer;
			}
		}
//		Com_OPrintf("WindowPos %d, WindowWritePos %d\n",ch->iMP3SlidingDecodeWindowPos,ch->iMP3SlidingDecodeWritePos);
	}

//	if (!_bDecoded)
//	{
//		Com_Printf(S_COLOR_YELLOW"No decode needed\n");
//	}

	assert(startingSampleNum >= ch->iMP3SlidingDecodeWindowPos);
	memcpy( buf, ch->MP3SlidingDecodeBuffer + (startingSampleNum-ch->iMP3SlidingDecodeWindowPos), count);

//	Com_OPrintf("OK\n\n");

	return qbStreamStillGoing;
}