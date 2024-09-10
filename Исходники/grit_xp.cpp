/*! The 'append' mode for this function is special. Yes, it adds 
	new data to the file, but it also <i>replaces</i> old data of 
	the same name. Yes, this is proper procedure and should happen 
	in the others as well, but it's just easier in a binary 
	environment. The header file will still have double definitions,
	though.
	\todo	Code is inconsistent with the C/asm exporters. Rectify.
*/
bool grit_xp_gbfs(GritRec *gr)
{
	int ii, jj;

	// for new data
	int gr_count;
	BYTE *gr_data[4];
	GBFS_ENTRY gr_gben[4];

	// for total data
	int gb_count;
	GBFS_ENTRY *gbenL= gr_gben, *gbenD= NULL;

	ii= 0;

	// --- register the various fields ---

	// Graphics
	if(gr->gfxProcMode == GRIT_EXPORT)
	{
		grit_gbfs_entry_init(&gr_gben[ii], &gr->_gfxRec, 
			gr->symName, (gr->isTiled() ? E_AFX_TILE : E_AFX_BMP));
		gr_data[ii++]= gr->_gfxRec.data;
	}

	// Map
	if(gr->mapProcMode == GRIT_EXPORT)
	{
		grit_gbfs_entry_init(&gr_gben[ii], &gr->_mapRec, 
			gr->symName, (gr->isMetaTiled() ? E_AFX_MTILE :E_AFX_MAP));
		gr_data[ii++]= gr->_mapRec.data;

		// Meta map
		if(gr->isMetaTiled())
		{
			grit_gbfs_entry_init(&gr_gben[ii], &gr->_metaRec, 
				gr->symName, E_AFX_MMAP);
			gr_data[ii++]= gr->_metaRec.data;
		}
	}

	// Palette
	if(gr->palProcMode == GRIT_EXPORT)
	{
		grit_gbfs_entry_init(&gr_gben[ii], &gr->_palRec, 
			gr->symName, E_AFX_PAL);
		gr_data[ii++]= gr->_palRec.data;
	}

	gb_count= gr_count= ii;

	// --- create header and finish entries ---
	// Create basic header
	GBFS_FILE gbhdr;
	memcpy(gbhdr.magic, GBFS_magic, sizeof(GBFS_magic));
	gbhdr.dir_off= GBFL_SIZE;

	char name[MAXPATHLEN];
	strcpy(name, gr->dstPath);
	path_fix_sep(name);

	lprintf(LOG_STATUS, "Export to GBFS: %s into %s .\n", 
		gr->symName, name);


	FILE *fout= fopen("gbfs.tmp", "wb");
	if(fout == NULL)
		return false;

	u32 fpos= GBFL_SIZE + gr_count*GBEN_SIZE;
	fseek(fout, fpos, SEEK_SET);	// skip directory

	// Insert mode
	// Replace old with same name; insert new
	if(gr->bAppend)
	{
		FILE *fin= fopen(name, "rb");
		do
		{
			if(fin == NULL)
				break;

			GBFS_FILE oldhdr;
			// read and check file's header
			if(fread(&oldhdr, GBFL_SIZE, 1, fin) < 1)
			{	break;	}
			if(memcmp(oldhdr.magic, GBFS_magic, 16))
				break;

			// if we're here, we have a valid GBFS

			int old_count= oldhdr.dir_nmemb;
			gbenD= (GBFS_ENTRY*)malloc(old_count*GBEN_SIZE);
			if(gbenD==NULL)
				break;

			// Read directory
			fread(gbenD, GBEN_SIZE, old_count, fin);
			// check for obsoletes
			for(ii=0; ii<gr_count; ii++)
			{
				gbenL= (GBFS_ENTRY*)bsearch(&gr_gben[ii], gbenD, 
					old_count, GBEN_SIZE, gbfs_namecmp);
				if(gbenL == NULL)
					continue;
				// Obsolete found; remove from list;
				jj= (gbenL-gbenD);
				old_count--;
				memmove(gbenL, gbenL+1, (old_count-jj)*GBEN_SIZE);
			}
			// NOTE: old_count may have been modified
			gb_count= gr_count+old_count;

			// obsoletes are removed; write the rest to fout
			BYTE buf[1024];
			fpos= GBFL_SIZE + gb_count*GBEN_SIZE;
			fseek(fout, fpos, SEEK_SET);

			for(ii=0; ii<old_count; ii++)
			{
				fseek(fin, gbenD[ii].data_offset, SEEK_SET);
				gbenD[ii].data_offset= fpos;
				
				jj= gbenD[ii].len >> 10;
				while(jj--)
				{
					fread(buf, 1024, 1, fin);
					fwrite(buf, 1024, 1, fout);
				}
				if((jj= gbenD[ii].len & 1023) != 0)
				{
					fread(buf, jj, 1, fin);
					fwrite(buf, jj, 1, fout);
				}

				// pad to 16byte boundary
				for(fpos=ftell(fout); fpos & 0x0F; fpos++)
					fputc(0, fout);
			}

			// Combine lists
			gbenL= (GBFS_ENTRY*)malloc(gb_count*GBEN_SIZE);
			memcpy(gbenL, gr_gben, gr_count*GBEN_SIZE);
			memcpy(&gbenL[gr_count], gbenD, old_count*GBEN_SIZE);
			free(gbenD);
			gbenD= gbenL;
		} while(0);

		if(fin)
			fclose(fin);
	}