BOOL SaveAEArtFile( const char *path, OPENFILENAMEA *ofn )
{
  memset( ofn, 0, sizeof(*ofn));
  ofn->lStructSize     = sizeof( OPENFILENAME );
  ofn->hwndOwner       = NULL;
  ofn->hInstance       = NULL;
  ofn->lpstrFilter     = (LPCSTR)"AsciiEngine Art Files\0*.AEArt\0\0";    
  (const char *)ofn->lpstrFile       = path;
  ofn->lpstrFile[0]    = '\0';
  ofn->nMaxFile        = MAX_PATH;
  ofn->lpstrTitle      = (LPCSTR)"Select A Location To Save To";
  ofn->Flags           = OFN_NONETWORKBUTTON |
                      OFN_PATHMUSTEXIST |
                      OFN_HIDEREADONLY;
  if (GetSaveFileNameA( ofn ))
    return( TRUE );
  return FALSE;
}