static void Z_TagDebug_f(void)
{
	TagBlockLabels_t AllTagBlockLabels_Local;
	qboolean bSnapShotTestActive = qfalse;

	memtag_t eTag = TAG_ALL;

	const char *psTAGName = Cmd_Argv(1);
	if (psTAGName[0])
	{
		// check optional arg...
		//
		if (!Q_stricmp(psTAGName,"#snap"))
		{
			bSnapShotTestActive = qtrue;

			AllTagBlockLabels_Local = AllTagBlockLabels;	// horrible great STL copy

			psTAGName = Cmd_Argv(2);			
		}

		if (psTAGName[0])
		{
			// skip over "tag_" if user supplied it...
			//
			if (!Q_stricmpn(psTAGName,"TAG_",4))
			{
				psTAGName += 4;
			}

			// see if the user specified a valid tag...
			//
			for (int i=0; i<TAG_COUNT; i++)
			{
				if (!Q_stricmp(psTAGName,psTagStrings[i]))
				{
					eTag = (memtag_t) i;
					break;
				}
			}
		}
	}
	else
	{
		Com_Printf("Usage: 'zone_tagdebug [#snap] <tag>', e.g. TAG_GHOUL2, TAG_ALL (careful!)\n");
		return;
	}

	Com_Printf("Dumping debug data for tag \"%s\"...%s\n\n",psTagStrings[eTag], bSnapShotTestActive?"( since snapshot only )":"");

	Com_Printf("%8s"," ");	// to compensate for code further down:   Com_Printf("(%5d) ",iBlocksListed);
	if (eTag == TAG_ALL)
	{
		Com_Printf("%20s ","Zone Tag");
	}
	Com_Printf("%9s\n","Bytes");
	Com_Printf("%8s"," ");
	if (eTag == TAG_ALL)
	{
		Com_Printf("%20s ","--------");
	}
	Com_Printf("%9s\n","-----");


	if (bSnapShotTestActive)
	{
		// dec ref counts in last snapshot for all current blocks (which will make new stuff go negative)
		//
		zoneHeader_t *pMemory = TheZone.Header.pNext;
		while (pMemory)
		{
			if (pMemory->eTag == eTag || eTag == TAG_ALL)
			{
				AllTagBlockLabels_Local[psTagStrings[pMemory->eTag]][pMemory->sOptionalLabel]--;
			}
			pMemory = pMemory->pNext;		
		}
	}

	// now dump them out...
	//
	int iBlocksListed = 0;
	int iTotalSize = 0;
	zoneHeader_t *pMemory = TheZone.Header.pNext;
	while (pMemory)
	{
		if (	(pMemory->eTag == eTag	|| eTag == TAG_ALL)
			&&  (!bSnapShotTestActive	|| (pMemory->iSnapshotNumber == giZoneSnaphotNum && AllTagBlockLabels_Local[psTagStrings[pMemory->eTag]][pMemory->sOptionalLabel] <0) )
			)
		{
			float	fSize		= (float)(pMemory->iSize) / 1024.0f / 1024.0f;
			int		iSize		= fSize;
			int		iRemainder 	= 100.0f * (fSize - floor(fSize));

			Com_Printf("(%5d) ",iBlocksListed);

			if (eTag == TAG_ALL)
			{
				Com_Printf("%20s",psTagStrings[pMemory->eTag]);
			}

			Com_Printf(" %9d (%2d.%02dMB) File: \"%s\", Line: %d\n",
						  pMemory->iSize,
 							  iSize,iRemainder,
												pMemory->sSrcFileBaseName,
															pMemory->iSrcFileLineNum
					   );
			if (pMemory->sOptionalLabel[0])
			{
				Com_Printf("( Label: \"%s\" )\n",pMemory->sOptionalLabel);
			}
			iBlocksListed++;
			iTotalSize += pMemory->iSize;
			
			if (bSnapShotTestActive)
			{
				// bump ref count so we only 1 warning per new string, not for every one sharing that label...
				//
				AllTagBlockLabels_Local[psTagStrings[pMemory->eTag]][pMemory->sOptionalLabel]++;
			}
		}
		pMemory = pMemory->pNext;		
	}

	Com_Printf("( %d blocks listed, %d bytes (%.2fMB) total )\n",iBlocksListed, iTotalSize, (float)iTotalSize / 1024.0f / 1024.0f);
}