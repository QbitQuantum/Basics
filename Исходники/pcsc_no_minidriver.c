BOOL MonitorReaders(SCARDCONTEXT hContext)
{
  DWORD  dwReaders, dwReadersOld = 0;
  SCARD_READERSTATE *rgscState;
	LPSTR  szReaders = NULL;
  DWORD  dwReadersSz; 
  DWORD  maxReaders;
	BOOL   bFirstRun = TRUE;
  DWORD  i, j;
	LONG   rc;

  /* Constant MAXIMUM_SMARTCARD_READERS is only 10 in Windows SDK */
  /* This is not enough for most of our tests. 64 sounds good...  */
  maxReaders = MAXIMUM_SMARTCARD_READERS;
  if (maxReaders<64) maxReaders = 64;

  rgscState = calloc(maxReaders, sizeof(SCARD_READERSTATE));
  if (rgscState == NULL)
  {
    printf("Out of memory\n");
    return FALSE;
  }

	for (;;)
	{
  	/* Get the list of available readers */
    dwReadersSz = SCARD_AUTOALLOCATE;
		rc = SCardListReaders(hContext,
                          NULL,                /* Any group */
                          (LPTSTR) &szReaders, /* Diabolic cast for buffer auto-allocation */
                          &dwReadersSz);       /* Beg for auto-allocation */
	  
		if (rc == SCARD_E_NO_READERS_AVAILABLE)
		{
		  /* No reader at all */
			dwReaders = 0;
		} else
    if (rc != SCARD_S_SUCCESS)
		{
      printf("SCardListReaders error 0x%08lX (%lu).\n", rc, rc);
			break;
		} else
		{
			/* Track events on found readers. */
			LPTSTR pReader = szReaders;

			for (dwReaders=0; dwReaders<maxReaders; dwReaders++)
			{
        /* End of multi-string array */
				if (*pReader == '\0')
					break;

        /* Remember this reader's name */
				rgscState[dwReaders].szReader = pReader;

        /* Jump to next entry in multi-string array */
				pReader += strlen(pReader) + 1;
			}
		}

		if (bFirstRun)
    {
      /* Program startup, display the number of readers */
      if (dwReaders == 0)
      {
        printf("No PC/SC reader\n\n");
      } else
      {
        printf("%ld PC/SC reader%s found\n\n", dwReaders, dwReaders ? "s" : "");
      }
    }
      
		if (dwReadersOld != dwReaders)
		{
			/* Reader added, or reader removed           */
      /* (re)set the initial state for all readers */
			for (i=0; i<dwReaders; i++)
				rgscState[i].dwCurrentState = SCARD_STATE_UNAWARE;

      if (!bFirstRun)
      {
        int c;

        /* Not the program startup, explain the event */
				if (dwReadersOld > dwReaders)
				{
          c = (int) dwReadersOld-dwReaders;
					printf("%d reader%s ha%s been removed from the system\n\n", c, (c==1)?" ":"s", (c==1)?"s":"ve");
				}
				else
				{
          c = (int) dwReaders-dwReadersOld;
					printf("%d reader%s ha%s been added to the system\n\n", c, (c==1)?" ":"s", (c==1)?"s":"ve");
				}
			}

      dwReadersOld = dwReaders;
		}

    if (dwReaders == 0)
    {
      /* We must wait here, because the SCardGetStatusChange doesn't wait  */
      /* at all in case there's no reader in the system. Silly, isn't it ? */
      Sleep(1000);
    }

		/*
     * Interesting part of the job : call SCardGetStatusChange to monitor all changes
     * taking place in the PC/SC reader(s)
     */
		rc = SCardGetStatusChange(hContext,
			                        INFINITE,
			                        rgscState,
			                        dwReaders);	
		
		if (rc != SCARD_S_SUCCESS)
    {
      printf("SCardGetStatusChange error 0x%08lX (%lu).\n", rc, rc);

      if (rc == SCARD_F_INTERNAL_ERROR)
      {
        /* Oups ? Restard from scratch after 2500ms */
        if (szReaders != NULL)
        {
          SCardFreeMemory(hContext, szReaders);
          szReaders = NULL;
        }
        Sleep(2500);
        continue;
      }
      break;
    }

		for (i=0; i<dwReaders; i++)
		{
      BOOL just_inserted = FALSE;

      if (rgscState[i].dwEventState & SCARD_STATE_CHANGED)
      {
        /* Something changed since last loop        */
        if ( (rgscState[i].dwEventState & SCARD_STATE_PRESENT)
         && !(rgscState[i].dwCurrentState & SCARD_STATE_PRESENT) )
          just_inserted = TRUE;

        /* Remember new current state for next loop */
        rgscState[i].dwCurrentState = rgscState[i].dwEventState;
      } else
      {
        /* Nothing new, don't display anything for this reader */
        /* (unless we're in the first run)                     */
        if (!bFirstRun)
          continue;
      }

			if (just_inserted)
			{
				printf("Card inserted in %s\n", rgscState[i].szReader);

				if (rgscState[i].dwEventState & SCARD_STATE_MUTE)
				{
					printf("\tCard is mute\n");
				} else
				{
					printf("\tATR: ");
					for (j=0; j<rgscState[i].cbAtr; j++)
						printf("%02X", rgscState[i].rgbAtr[j]);
					printf("\n");

					if (!ProcessCardAtr(hContext, rgscState[i].rgbAtr, rgscState[i].cbAtr))
            return FALSE;

					printf("\n");
				}
			}
		}

    /* Free the list of readers  */
    if (szReaders != NULL)
    {
      SCardFreeMemory(hContext, szReaders);
      szReaders = NULL;
    }
      
    /* Not the first run anymore */
		bFirstRun = FALSE;
	}


  /* Never go here (Ctrl+C kill us before !) */
  free(rgscState);
  return TRUE;
}