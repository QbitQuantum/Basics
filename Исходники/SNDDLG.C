BOOL ExportSound( HWND hwndParent, WND_DATA *pWndData, INT index )
{
  INT n;
  LONG lsize;
  HFILE fh;
  BOOL bResult;
  OPENFILENAME ofn;
  CHAR szDirName[256], szFile[256], szFileTitle[256];

  struct
  {
    char    r_id[4];
    long    r_len;
    char    w_id[4];
    char    f_id[4];
    long    f_len;
    int     f_tag;
    int     f_channels;
    long    f_sample_rate;
    long    f_avg_bytes_per_sec;
    int     f_block_align;
    int     f_bits_per_sample;
    char    d_id[4];
    long    d_len;

  } hdr;

  static CHAR *szFilter = "WAV files (*.wav)\000*.wav\000";

  _fstrcpy( szDirName, szPath );

  n = _fstrlen( szDirName );

  if (n > 0)
  {
    if (szDirName[n-1] == '\\' )
    {
      szDirName[n-1] = '\0';
    }
  }
  
  _fstrcpy( szFile, pWndData->pSoundData[index].sound_name );

  _fmemset( &ofn, 0, sizeof(OPENFILENAME) );

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hwndParent;
  ofn.hInstance = hInst;
  ofn.lpstrFilter = szFilter;
  ofn.nFilterIndex = 1;
  ofn.lpstrFile= szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFileTitle = szFileTitle;
  ofn.nMaxFileTitle = sizeof(szFileTitle);
  ofn.lpstrInitialDir = szDirName;
  ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
  
  bResult = GetSaveFileName( &ofn );
    
  if ( !bResult )
  {
    DWORD dwError;
    
    dwError = CommDlgExtendedError();
    
    if ( dwError )
    {
      MsgBox( hwndParent,
              MB_ICONEXCLAMATION,
              "Common dialog error %lu",
              dwError );
    }
              
    return FALSE;
  }

  fh = _lcreat( szFile, READ );

  if ( fh == HFILE_ERROR )
  {
    MsgBox( hwndParent,
            MB_ICONEXCLAMATION,
            "Unable to create %s",
            (LPSTR)szFile );

    return FALSE;
  }

  lsize = pWndData->pSoundData[index].length;

  hdr.r_id[0] = 'R';
  hdr.r_id[1] = 'I';
  hdr.r_id[2] = 'F';
  hdr.r_id[3] = 'F';
  hdr.r_len = sizeof(hdr) + lsize - 8L;
  hdr.w_id[0] = 'W';
  hdr.w_id[1] = 'A';
  hdr.w_id[2] = 'V';
  hdr.w_id[3] = 'E';
  hdr.f_id[0] = 'f';
  hdr.f_id[1] = 'm';
  hdr.f_id[2] = 't';
  hdr.f_id[3] = ' ';
  hdr.f_len = 16L;
  hdr.f_tag = 1;
  hdr.f_channels = 1;
  hdr.f_sample_rate = 22050L;
  hdr.f_avg_bytes_per_sec = 22050L;
  hdr.f_block_align = 1;
  hdr.f_bits_per_sample = 8;
  hdr.d_id[0] = 'd';
  hdr.d_id[1] = 'a';
  hdr.d_id[2] = 't';
  hdr.d_id[3] = 'a';
  hdr.d_len = lsize;

  if ( _lwrite( fh, &hdr, sizeof(hdr) ) != sizeof(hdr) )
  {
    _lclose(fh);

    MsgBox( hwndParent,
            MB_ICONEXCLAMATION,
            "Error writing sound file header for %s",
            (LPSTR)szFile );

    return FALSE;
  }

  if ( _hwrite( fh, pWndData->pSoundData[index].data, lsize) != lsize )
  {
    _lclose(fh);

    MsgBox( hwndParent,
            MB_ICONEXCLAMATION,
            "Error writing sound file data for %s",
            (LPSTR)szFile );

    return FALSE;
  }

  _lclose(fh);

  return TRUE;
  
} // ExportSound