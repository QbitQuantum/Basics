void outwnd_print(char *id, char *tmp)
{
	char *sptr;
	char *dptr;
	int i, nrows, ccol;
	outwnd_filter_struct *temp;

	if(gr_screen.mode == GR_DIRECT3D){
		return;
	}

	if (!outwnd_inited)
		return;

	if ( Outwnd_no_filter_file == 1 )	{
		Outwnd_no_filter_file = 2;

		outwnd_print( "general", "==========================================================================\n" );
		outwnd_print( "general", "DEBUG SPEW: No debug_filter.cfg found, so only general, error, and warning\n" );
		outwnd_print( "general", "categories can be shown and no debug_filter.cfg info will be saved.\n" );
		outwnd_print( "general", "==========================================================================\n" );
	}

	if (!id)
		id = "General";

	for (i=0; i<outwnd_filter_count; i++)
		if (!stricmp(id, outwnd_filter[i]->name))
			break;


	if (i == outwnd_filter_count)  // new id found that's not yet in filter list
	{
		// Only create new filters if there was a filter file
		if ( Outwnd_no_filter_file )	{
			return;
		}

		if (outwnd_filter_count >= MAX_FILTERS) {
			Assert(outwnd_filter_count == MAX_FILTERS);  // how did it get over the max?  Very bad..
			outwnd_printf("General", "Outwnd filter limit reached.  Recycling \"%s\" to add \"%s\"",
				outwnd_filter[MAX_FILTERS - 1]->name, id);

			i--;  // overwrite the last element (oldest used filter in the list)
		}

		Assert(strlen(id) < FILTER_NAME_LENGTH);
		outwnd_filter[i] = &real_outwnd_filter[i];  // note: this assumes the list doesn't have gaps (from deleting an element for example)
		strcpy(outwnd_filter[i]->name, id);
		outwnd_filter[i]->state = 1;
		outwnd_filter_count = i + 1;
		save_filter_info();
	}

	// sort the filters from most recently used to oldest, so oldest ones will get recycled first
	temp = outwnd_filter[i];
	while (i--)
		outwnd_filter[i + 1] = outwnd_filter[i];

	i++;
	outwnd_filter[i] = temp;

	if (!outwnd_filter[i]->state)
		return;

	if (mprintf_last_line == -1 )	{
		for (i=0; i<SCROLL_BUFFER_SIZE;i++)	{
			outtext[i][0] = 0;
		}

		mprintf_last_line = 0;
	}

	// printf out to the monochrome screen first
	if ( mono_driver != ((HANDLE)-1) ) {
		DWORD   cbReturned;

		DeviceIoControl (mono_driver, (DWORD)IOCTL_MONO_PRINT, tmp, strlen(tmp), NULL, 0, &cbReturned, 0 );
	} else {
		mono_print(tmp, strlen(tmp) );
	}

	sptr = tmp;
	ccol = strlen(outtext[mprintf_last_line] );
	dptr = &outtext[mprintf_last_line][ccol];
	nrows = 0;

#ifndef NDEBUG

	if ( Log_debug_output_to_file ) {
		if ( Log_fp != NULL ) {
			fputs(tmp, Log_fp);	
			fflush(Log_fp);
		}
	}

#endif

	while(*sptr) {
		if ( (*sptr == '\n') || (ccol >= MAX_LINE_WIDTH-1 ) )	{
			nrows++;
			mprintf_last_line++;
			if (mprintf_last_line >= SCROLL_BUFFER_SIZE )
				mprintf_last_line = 0;
			ccol = 0;
			if ( *sptr != '\n' )	{
				outtext[mprintf_last_line][ccol]	= *sptr;
				ccol++;
			}
			outtext[mprintf_last_line][ccol] = '\0';
			dptr = &outtext[mprintf_last_line][ccol];
		} else {
			*dptr++ = *sptr;
			*dptr = '\0';
			ccol++;
		}
		sptr++;
	} 

	if(gr_screen.mode == GR_DIRECT3D){
		return;
	}
//	if ( D3D_enabled )	{
//		return;		// Direct3D seems to hang sometimes printing to window
//	}

	if ( outwnd_disabled ){
		return;
	}

	if ( !OutputActive )	{
		int oldpos = GetScrollPos( hOutputWnd, SB_VERT );
		if ( oldpos != max_scroll_pos )	{
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			si.nPos = max_scroll_pos;
			SetScrollInfo(hOutputWnd, SB_VERT, &si, 1 );
			InvalidateRect(hOutputWnd,NULL,0);
			UpdateWindow(hOutputWnd);
		} else {
			if ( nrows )	{
				RECT client;
				ScrollWindow(hOutputWnd,0,-nTextHeight*nrows,NULL,NULL);
				GetClientRect(hOutputWnd, &client);
				client.top = client.bottom - nTextHeight*(nrows+1);
				InvalidateRect(hOutputWnd,&client,0);

				UpdateWindow(hOutputWnd);
			} else {
				Outwnd_changed++;
			}
		}
	}
}