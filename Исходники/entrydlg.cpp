void TViewEntryDialog::EvDrawItem (UINT ctrlId, DRAWITEMSTRUCT& drawInfo)
#endif
{
	char Buf[128];

	// To be sure
	if ( CurrentEntry == NULL )
		return;

	// To be sure
	if ( ctrlId != IDC_VE_DUMP_LIST )
		return;

	// If there are no list box items, skip this message.
	if ( drawInfo.itemID == (UINT)-1 )
		return;

	// Build string to draw
	strcpy (Buf, "");
	if ( drawInfo.itemID == 0 )
	{
		char entryname[9];

		strncpy (entryname, CurrentEntry->dir.name, 8);
		entryname[8] = '\0';
		sprintf(Buf, "Contents of entry %s (size = %ld bytes):",
					 entryname, CurrentEntry->dir.size);
	}
	else
	{
		// Starting Offset in the entry
		ULONG EntryOffset = (ULONG)(drawInfo.itemID - 1) * NB_HEX_LINE;

		// Starting Offset in the wad file
		ULONG WadOffset   = CurrentEntry->dir.start + EntryOffset;

		// Number of chars for this line
		USHORT NbChars    = min(NB_HEX_LINE,
								(USHORT)(CurrentEntry->dir.size - EntryOffset));

		// Bytes of the line
		unsigned char HexBuf[NB_HEX_LINE];

		// Line len
		int len;
		int i;

		BasicWadSeek (CurrentEntry->wadfile, WadOffset);

		// Dump offset
		len = sprintf(Buf, "%06lX:\t", EntryOffset);

		// 16 hex values
		for (i = 0 ; i < NbChars ; i++)
		{
			BasicWadRead (CurrentEntry->wadfile, &(HexBuf[i]), 1);

			len += sprintf (&Buf[len], "%02X\t", HexBuf[i]);
		}

		// Add padding tabs
		for (; i < NB_HEX_LINE ; i++)
			len += sprintf(&Buf[len], "\t");
		// len += sprintf (&Buf[len], "\t");

		// 16 chars
		for (i = 0 ; i < NbChars ; i++)
		{
			char c = HexBuf[i];
			if ( ! isprint(c) )
				c = ' ';

			len += sprintf (&Buf[len], "%c", c);
		}
	}

	switch (drawInfo.itemAction)
	{
		case ODA_SELECT:
		case ODA_DRAWENTIRE:
		{
			// Retreive the average character width
			TEXTMETRIC tm;
			GetTextMetrics(drawInfo.hDC, &tm);

			// Setup tab stops in HexDump list
			int TabStops[NB_HEX_LINE+1];
			int i;

			TabStops[0] = 6 * tm.tmAveCharWidth;
			for (i = 1 ; i < NB_HEX_LINE ; i++)
				TabStops[i] = TabStops[i-1] + 3 * tm.tmAveCharWidth + 2;
			TabStops[i] = TabStops[i-1] + 4 * tm.tmAveCharWidth;

			TabbedTextOut(drawInfo.hDC,
						  drawInfo.rcItem.left, drawInfo.rcItem.top,
						  Buf, strlen(Buf),
						  NB_HEX_LINE+2, TabStops, 0);
#if 0
			/* Is the item selected? */
			if (drawInfo.itemState & ODS_SELECTED)
			{
				/* Draw a rectangle around bitmap to indicate the selection. */
				DrawFocusRect(drawInfo.hDC, &drawInfo.rcItem);
			}
#endif
		}
		break;

		case ODA_FOCUS:
			/*
			 * Do not process focus changes. The focus caret (outline
			 * rectangle) indicates the selection. The Which one? (IDOK)
			 * button indicates the final selection.
			 */
		  break;
	}
}