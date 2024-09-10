//------------------------------------------------------------------------------
//initialize a pigfile, reading headers
//returns the size of all the bitmap data
void PiggyInitPigFile (char *filename)
{
	CFile					*cfP = cfPiggy + gameStates.app.bD1Data;
	char					szName [16];
	char					szNameRead [16];
	char					szPigName [FILENAME_LEN];
	int					nHeaderSize, nBitmapNum, nDataSize, nDataStart, i;
	CBitmap				bm;
	tPIGBitmapHeader	bmh;

PiggyCloseFile ();             //close old pig if still open
strcpy (szPigName, filename);
//rename pigfile for shareware
if (!stricmp (DefaultPigFile (), DefaultPigFile (1)) && 
	 !CFile::Exist (szPigName, gameFolders.szDataDir, 0))
	strcpy (szPigName, DefaultPigFile (1));
strlwr (szPigName);
if (!cfP->Open (szPigName, gameFolders.szDataDir, "rb", 0)) {
	if (!CopyPigFileFromCD (*cfP, szPigName))
		return;
	}
int pig_id = cfP->ReadInt ();
int pigVersion = cfP->ReadInt ();
if (pig_id != PIGFILE_ID || pigVersion != PIGFILE_VERSION) {
	cfP->Close ();              //out of date pig
	return;
	}
strncpy (szCurrentPigFile [0], szPigName, sizeof (szCurrentPigFile [0]));
nBitmapNum = cfP->ReadInt ();
nHeaderSize = nBitmapNum * sizeof (tPIGBitmapHeader);
nDataStart = nHeaderSize + cfP->Tell ();
nDataSize = cfP->Length () - nDataStart;
gameData.pig.tex.nBitmaps [0] = 1;
for (i = 0; i < nBitmapNum; i++) {
	PIGBitmapHeaderRead (&bmh, *cfP);
	memcpy (szNameRead, bmh.name, 8);
	szNameRead [8] = 0;
	if (bmh.dflags & DBM_FLAG_ABM)        
		sprintf (szName, "%s#%d", szNameRead, bmh.dflags & DBM_NUM_FRAMES);
	else
		strcpy (szName, szNameRead);
	memset (&bm, 0, sizeof (CBitmap));
	bm.SetWidth (bmh.width + ((short) (bmh.wh_extra & 0x0f) << 8));
	bm.SetHeight (bmh.height + ((short) (bmh.wh_extra & 0xf0) << 4));
	bm.SetBPP (1);
	bm.SetFlags (BM_FLAG_PAGED_OUT);
	bm.SetAvgColorIndex (bmh.avgColor);
	gameData.pig.tex.bitmapFlags [0][i+1] = bmh.flags & BM_FLAGS_TO_COPY;
	bitmapOffsets [0][i+1] = bmh.offset + nDataStart;
	Assert ((i+1) == gameData.pig.tex.nBitmaps [0]);
	PiggyRegisterBitmap (&bm, szName, 1);
	}
bPigFileInitialized = 1;
}