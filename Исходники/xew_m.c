/* export_cb : Export Callback
   Export to file the entry highlighted in the browser. */
void export_cb(FL_OBJECT *a, long l)
{
  Int4 index;
  int RetVal;
  unsigned char *pImgBuf;
  short Width;
  short Height;
  const char *format;

  RetVal = fl_get_browser(wad_brow);
  if ( RetVal == 1 )           /* first line is the legend */
    return;
  index = LinearMap[RetVal];
  
  switch (pEntryTag[index])
    {
    case TAG_MUS  : 
      GenFileName(pDirEnt[index].name, ".mus", TmpNameStr);
      RetVal = Gen_MUS_File(WADfp, pDirEnt[index], TmpNameStr);
      break;
    case TAG_SFX  :
      GenFileName(pDirEnt[index].name, ".wav", TmpNameStr);
      RetVal = Gen_WAV_File(WADfp, pDirEnt[index], TmpNameStr);
      break;
    case TAG_FLAT :
    case TAG_FULL :
    case TAG_IMG  :
      pImgBuf = ParseImgBlock(pDirEnt[index], pEntryTag[index], 
			      &Width, &Height, NULL, NULL, WADfp);
      if (pImgBuf == NULL) {
	RetVal = 4;
	break;
      }
      format = fl_get_choice_text( exp_img_fmt_cho );
      if ( !strcmp(format, PCX_STR ) ) {           /* pcx */
	GenFileName(pDirEnt[index].name, ".pcx", TmpNameStr);
	RetVal = PCX_WriteImage(pDirEnt[index], WADfp, Width, Height, 
				pImgBuf, 1, TmpNameStr);
      }
      else {  /* xpm */
	char **xpm;
	GenFileName(pDirEnt[index].name, ".xpm", TmpNameStr);
	/* don't just redraw, we don't know what's in the xpm: */
	xpm = CreateXpmImage( pImgBuf, Width, Height, 0, NULL ); 
	if ( xpm && CreateXpmFile( xpm, TmpNameStr ) ) 
	  RetVal = 0;
	else
	  RetVal = 666; /* why not? */
      }
      break;
    case TAG_HIRES:
      GenFileName(pDirEnt[index].name, ".pcx", TmpNameStr);
      RetVal = PCX_WriteImage(pDirEnt[index], WADfp, 640, 480, 
			      pBitMap, 4, TmpNameStr);
      break;
    default:
      RetVal = 1;
      break;
    }
  
  if (RetVal != 0) {
    Beep();
    Message("error generating external file \"%s\" (%d)\n", 
	   TmpNameStr, RetVal);
  }
  else
    Message("External file \"%s\" created OK\n", TmpNameStr); 
}