int getwave(void)
{
	int r;
	static int pos=-1024;

	if (ifp == NULL)
	{
		// WaveIn
		do
		{
			mmr = waveInGetPosition(hwi,&mmt, sizeof(mmt));
			now_ptr = mmt.u.cb;
			if (now_ptr == BUFSIZE)
			{
				die("\nWAV Buffer Full!\n");
			}
			
			if (kbhit())
			{
				die("\nAbort...\n");
			}
			Sleep(0);
		} while (now_ptr<(read_ptr+0x1000));

#ifndef USE_RECORD_16BIT
//		8bit
		r = record_buf[read_ptr++];
#else
//		16bit 
		r = (record_buf[read_ptr+1] << 8) | record_buf[read_ptr];
		read_ptr += 2;
		r >>= 8;
#endif
	}
	else
	{
		// from WAV File
		if ( pos+1024 <= ftell(ifp) )