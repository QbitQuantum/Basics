int
WIN_Audio_close ( void )
{
	if ( dev != NULL ) 
    {
		while ( ScheduledBlocks > 0 ) {
			Sleep (ScheduledBlocks);
			while ( PlayedWaveHeadersCount > 0 )         // free used blocks ...
				free_memory ();
		}

		waveOutReset (dev);      // reset the device
		waveOutClose (dev);      // close the device
		dev = NULL;
	}

	DeleteCriticalSection ( &cs );
	ScheduledBlocks = 0;

    if (!g_bEnd)
    {
        g_hDuoduoWnd = FindWindow(NULL,"多多卖家版");
        if (g_hDuoduoWnd)
        {
            PostMessage(g_hDuoduoWnd,g_sPlayFinished,NULL,NULL);
        }else
        {
            //Box( "Can't find window named 多多卖家版" );
        }
    }

	return 0;
}