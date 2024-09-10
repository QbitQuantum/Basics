int BLKFAM::ReadBuffer(PGLOBAL g)
  {
  int i, n, rc = RC_OK;

  /*********************************************************************/
  /*  Sequential reading when Placed is not true.                      */
  /*********************************************************************/
  if (Placed) {
    Placed = false;
  } else if (++CurNum < Rbuf) {
    CurLine = NxtLine;

    // Get the position of the next line in the buffer
    while (*NxtLine++ != '\n') ;

    // Set caller line buffer
    n = NxtLine - CurLine - Ending;
    memcpy(Tdbp->GetLine(), CurLine, n);
    Tdbp->GetLine()[n] = '\0';
    goto fin;
  } else if (Rbuf < Nrec && CurBlk != -1) {
    return RC_EF;
  } else {
    /*******************************************************************/
    /*  New block.                                                     */
    /*******************************************************************/
    CurNum = 0;

    if (++CurBlk >= Block)
      return RC_EF;

  } // endif's

  if (OldBlk == CurBlk)
    goto ok;         // Block is already there

  // fseek is required only in non sequential reading
  if (CurBlk != OldBlk + 1)
    if (fseek(Stream, BlkPos[CurBlk], SEEK_SET)) {
      sprintf(g->Message, MSG(FSETPOS_ERROR), BlkPos[CurBlk]);
      return RC_FX;
      } // endif fseek

  // Calculate the length of block to read
  BlkLen = BlkPos[CurBlk + 1] - BlkPos[CurBlk];

  if (trace)
    htrc("File position is now %d\n", ftell(Stream));

  // Read the entire next block
  n = fread(To_Buf, 1, (size_t)BlkLen, Stream);

  if (n == BlkLen) {
//  ReadBlks++;
    num_read++;
    Rbuf = (CurBlk == Block - 1) ? Last : Nrec;

   ok:
    rc = RC_OK;

    // Get the position of the current line
    for (i = 0, CurLine = To_Buf; i < CurNum; i++)
      while (*CurLine++ != '\n') ;      // What about Unix ???

    // Now get the position of the next line
    for (NxtLine = CurLine; *NxtLine++ != '\n';) ;

    // Set caller line buffer
    n = NxtLine - CurLine - Ending;
    memcpy(Tdbp->GetLine(), CurLine, n);
    Tdbp->GetLine()[n] = '\0';
  } else if (feof(Stream)) {
    rc = RC_EF;
  } else {
#if defined(UNIX)
    sprintf(g->Message, MSG(READ_ERROR), To_File, strerror(errno));
#else
    sprintf(g->Message, MSG(READ_ERROR), To_File, _strerror(NULL));
#endif

    if (trace)
      htrc("%s\n", g->Message);

    return RC_FX;
  } // endelse

  OldBlk = CurBlk;         // Last block actually read
  IsRead = true;           // Is read indeed

 fin:
  // Store the current record file position for Delete and Update
  Fpos = BlkPos[CurBlk] + CurLine - To_Buf;
  return rc;
  } // end of ReadBuffer