void hgDumpWiggle(int trackCount, char *tracks[])
/* hgDumpWiggle - dump wiggle data from database or .wig file */
{
int i;
struct wiggle *wiggle;

for (i=0; i<trackCount; ++i)
    verbose(2, "#\ttrack: %s\n", tracks[i]);

if (db)
    {
    struct sqlConnection *conn = hAllocConn();
    struct sqlResult *sr;
    char **row;
    char query[256];
    char *wibFile = NULL;
    FILE *f = (FILE *) NULL;
    unsigned char *ReadData;    /* the bytes read in from the file */
    int dataOffset = 0;         /*      within data block during reading */
    int rowCount = 0;

    conn = sqlConnect(db);
    for (i=0; i<trackCount; ++i)
	{
	if (chr)
	    sqlSafef(query, 256, "select * from %s where chrom = \"%s\"\n", tracks[i], chr);
	else
	    sqlSafef(query, 256, "select * from %s\n", tracks[i]);
	verbose(2, "#\t%s\n", query);
	sr = sqlGetResult(conn,query);
	while ((row = sqlNextRow(sr)) != NULL)
	    {
	    ++rowCount;
	    wiggle = wiggleLoad(row + 1);  /* the +1 avoids the bin column*/
	    verbose(2, "#\trow: %d, start: %u, data range: %g: [%g:%g]\n", rowCount, wiggle->chromStart, wiggle->dataRange, wiggle->lowerLimit, wiggle->lowerLimit+wiggle->dataRange);
	    verbose(2, "#\tresolution: %g per bin\n",wiggle->dataRange/(double)MAX_WIG_VALUE);
	    if (wibFile)
		{
		if (differentString(wibFile,wiggle->file))
		    {
		    if (f != (FILE *) NULL)
			{
			fclose(f);
			freeMem(wibFile);
			}
		    wibFile = cloneString(wiggle->file);
		    f = mustOpen(wibFile, "r");
		    }
		}
	    else
		{
		wibFile = cloneString(wiggle->file);
		f = mustOpen(wibFile, "r");
		}
	    fseek(f, wiggle->offset, SEEK_SET);
	    ReadData = (unsigned char *) needMem((size_t) (wiggle->count + 1));
	    fread(ReadData, (size_t) wiggle->count,
		(size_t) sizeof(unsigned char), f);
	    verbose(2, "#\trow: %d, reading: %u bytes\n", rowCount, wiggle->count);
	    for (dataOffset = 0; dataOffset < wiggle->count; ++dataOffset)
                {
                unsigned char datum = ReadData[dataOffset];
                if (datum != WIG_NO_DATA)
		    {
		    double dataValue =
  wiggle->lowerLimit+(((double)datum/(double)MAX_WIG_VALUE)*wiggle->dataRange);
		    printf("%d\t%g\n",
	1 + wiggle->chromStart + (dataOffset * wiggle->span), dataValue);
		    }
		}
	    }
	}
    if (f != (FILE *) NULL)
	{
	fclose(f);
	}
    if (wibFile)
	freeMem(wibFile);

    sqlFreeResult(&sr);
    hFreeConn(&conn);
    }
else
    {
    warn("ERROR: file option has not been implemented yet ...");
    }
}	/*	void hgDumpWiggle(int trackCount, char *tracks[])	*/