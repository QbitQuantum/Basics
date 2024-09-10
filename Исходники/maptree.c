SHPTreeHandle msSHPDiskTreeOpen(struct zzip_dir *zdir, const char * pszTree,
                                int debug)
{
  char    *pszFullname, *pszBasename;
  SHPTreeHandle psTree;

  char    pabyBuf[16];
  int     i;
#ifdef SHAPELIB_DISABLED
  char    bBigEndian;

  /* -------------------------------------------------------------------- */
  /*  Establish the byte order on this machine.         */
  /* -------------------------------------------------------------------- */
  i = 1;
  if( *((uchar *) &i) == 1 )
    bBigEndian = MS_FALSE;
  else
    bBigEndian = MS_TRUE;
#endif /* SHAPELIB_DISABLED */

  /* -------------------------------------------------------------------- */
  /*  Initialize the info structure.              */
  /* -------------------------------------------------------------------- */
  psTree = (SHPTreeHandle) msSmallMalloc(sizeof(SHPTreeInfo));

  /* -------------------------------------------------------------------- */
  /*  Compute the base (layer) name.  If there is any extension     */
  /*  on the passed in filename we will strip it off.         */
  /* -------------------------------------------------------------------- */
  pszBasename = (char *) msSmallMalloc(strlen(pszTree)+5);
  strcpy( pszBasename, pszTree );
  for( i = strlen(pszBasename)-1;
       i > 0 && pszBasename[i] != '.' && pszBasename[i] != '/'
       && pszBasename[i] != '\\';
       i-- ) {}

  if( pszBasename[i] == '.' )
    pszBasename[i] = '\0';

  /* -------------------------------------------------------------------- */
  /*  Open the .shp and .shx files.  Note that files pulled from      */
  /*  a PC to Unix with upper case filenames won't work!        */
  /* -------------------------------------------------------------------- */
  pszFullname = (char *) msSmallMalloc(strlen(pszBasename) + 5);
  sprintf( pszFullname, "%s%s", pszBasename, MS_INDEX_EXTENSION);
  psTree->fp = zzip_open_rb(zdir, pszFullname);
  if( psTree->fp == NULL ) {
      sprintf( pszFullname, "%s.QIX", pszBasename);
      psTree->fp = zzip_open_rb(zdir, pszFullname);
  }

  msFree(pszBasename); /* don't need these any more */
  msFree(pszFullname);

  if( psTree->fp == NULL ) {
    msFree(psTree);
    return( NULL );
  }

  zzip_fread( pabyBuf, 8, 1, psTree->fp );

  memcpy( &psTree->signature, pabyBuf, 3 );
  if( strncmp(psTree->signature,"SQT",3) ) {
    /* ---------------------------------------------------------------------- */
    /*     must check if the 2 first bytes equal 0 of max depth that cannot   */
    /*     be more than 65535. If yes, we must swap all value. The problem    */
    /*     here is if there's no Depth (bytea 5,6,7,8 in the file) all bytes  */
    /*     will be set to 0. So,we will test with the number of shapes (bytes */
    /*     1,2,3,4) that cannot be more than 65535 too.                       */
    /* ---------------------------------------------------------------------- */
    if (debug) {
      msDebug("WARNING in msSHPDiskTreeOpen(): %s is in old index format "
              "which has been deprecated.  It is strongly recommended to "
              "regenerate it in new format.\n", pszTree);
    }
    if((pabyBuf[4] == 0 && pabyBuf[5] == 0 &&
        pabyBuf[6] == 0 && pabyBuf[7] == 0)) {
      psTree->LSB_order = !(pabyBuf[0] == 0 && pabyBuf[1] == 0);
    } else {
      psTree->LSB_order = !(pabyBuf[4] == 0 && pabyBuf[5] == 0);
    }
    psTree->needswap = ((psTree->LSB_order) != (!bBigEndian));

    /* ---------------------------------------------------------------------- */
    /*     poor hack to see if this quadtree was created by a computer with a */
    /*     different Endian                                                   */
    /* ---------------------------------------------------------------------- */
    psTree->version = 0;
  } else {
    psTree->needswap = (( pabyBuf[3] == MS_NEW_MSB_ORDER ) ^ ( bBigEndian ));

    psTree->LSB_order = ( pabyBuf[3] == MS_NEW_LSB_ORDER );
    memcpy( &psTree->version, pabyBuf+4, 1 );
    memcpy( &psTree->flags, pabyBuf+5, 3 );

    zzip_fread( pabyBuf, 8, 1, psTree->fp );
  }

  if( psTree->needswap ) SwapWord( 4, pabyBuf );
  memcpy( &psTree->nShapes, pabyBuf, 4 );

  if( psTree->needswap ) SwapWord( 4, pabyBuf+4 );
  memcpy( &psTree->nDepth, pabyBuf+4, 4 );

  return( psTree );
}