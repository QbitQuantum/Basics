bool DBFFAM::AllocateBuffer(PGLOBAL g)
  {
  char c;
  int  rc;
  MODE mode = Tdbp->GetMode();

  Buflen = Blksize;
  To_Buf = (char*)PlugSubAlloc(g, NULL, Buflen);

  if (mode == MODE_INSERT) {
#if defined(WIN32)
    /************************************************************************/
    /*  Now we can revert to binary mode in particular because the eventual */
    /*  writing of a new header must be done in binary mode to avoid        */
    /*  translating 0A bytes (LF) into 0D0A (CRLF) by Windows in text mode. */
    /************************************************************************/
    if (_setmode(_fileno(Stream), _O_BINARY) == -1) {
      sprintf(g->Message, MSG(BIN_MODE_FAIL), strerror(errno));
      return true;
      } // endif setmode
#endif   // WIN32

    /************************************************************************/
    /*  If this is a new file, the header must be generated.                */
    /************************************************************************/
    int len = GetFileLength(g);

    if (!len) {
      // Make the header for this DBF table file
      struct tm  *datm;
      int         hlen, n = 0;
      ushort      reclen = 1;
      time_t      t;
      DBFHEADER  *header;
      DESCRIPTOR *descp;
      PCOLDEF     cdp;
      PDOSDEF     tdp = (PDOSDEF)Tdbp->GetDef();

      // Count the number of columns
      for (cdp = tdp->GetCols(); cdp; cdp = cdp->GetNext())
        if (!(cdp->Flags & U_SPECIAL)) {
          reclen += cdp->GetLong();
          n++;
          } // endif Flags

      if (Lrecl != reclen) {
        sprintf(g->Message, MSG(BAD_LRECL), Lrecl, reclen);
        return true;
        } // endif Lrecl

      hlen = HEADLEN * (n + 1) + 2;
      header = (DBFHEADER*)PlugSubAlloc(g, NULL, hlen);
      memset(header, 0, hlen);
      header->Version = DBFTYPE;
      t = time(NULL) - (time_t)DTVAL::GetShift();
      datm = gmtime(&t);
      header->Filedate[0] = datm->tm_year - 100;
      header->Filedate[1] = datm->tm_mon + 1;
      header->Filedate[2] = datm->tm_mday;
      header->Headlen = (ushort)hlen;
      header->Reclen = (ushort)reclen;
      descp = (DESCRIPTOR*)header;

      // Currently only standard Xbase types are supported
      for (cdp = tdp->GetCols(); cdp; cdp = cdp->GetNext())
        if (!(cdp->Flags & U_SPECIAL)) {
          descp++;
      
          switch ((c = *GetFormatType(cdp->GetType()))) {
            case 'S':           // Short integer
            case 'L':           // Large (big) integer
            case 'T':           // Tiny integer
              c = 'N';          // Numeric
            case 'N':           // Numeric (integer)
            case 'F':           // Float (double)
              descp->Decimals = (uchar)cdp->F.Prec;
            case 'C':           // Char
            case 'D':           // Date
              break;
            default:            // Should never happen
              sprintf(g->Message, "Unsupported DBF type %c for column %s",
                                  c, cdp->GetName());
              return true;
            } // endswitch c
      
          strncpy(descp->Name, cdp->GetName(), 11);
          descp->Type = c;
          descp->Length = (uchar)cdp->GetLong();
          } // endif Flags

      *(char*)(++descp) = EOH;

      //  Now write the header
      if (fwrite(header, 1, hlen, Stream) != (unsigned)hlen) {
        sprintf(g->Message, MSG(FWRITE_ERROR), strerror(errno));
        return true;
        } // endif fwrite

      Records = 0;
      Headlen = hlen;
    } else if (len < 0)
      return true;            // Error in GetFileLength

    /************************************************************************/
    /*  For Insert the buffer must be prepared.                             */
    /************************************************************************/
    memset(To_Buf, ' ', Buflen);
    Rbuf = Nrec;                     // To be used by WriteDB
  } else if (UseTemp) {
    // Allocate a separate buffer so block reading can be kept
    Dbflen = Nrec;
    DelBuf = PlugSubAlloc(g, NULL, Blksize);
  } // endif's

  if (!Headlen) {
    /************************************************************************/
    /*  Here is a good place to process the DBF file header                 */
    /************************************************************************/
    DBFHEADER header;

    if ((rc = dbfhead(g, Stream, Tdbp->GetFile(g), &header)) == RC_OK) {
      if (Lrecl != (int)header.Reclen) {
        sprintf(g->Message, MSG(BAD_LRECL), Lrecl, header.Reclen);
        return true;
        } // endif Lrecl

      Records = (int)header.Records;
      Headlen = (int)header.Headlen;
    } else if (rc == RC_NF) {
      Records = 0;
      Headlen = 0;
    } else              // RC_FX
      return true;                  // Error in dbfhead

    } // endif Headlen

  /**************************************************************************/
  /*  Position the file at the begining of the data.                        */
  /**************************************************************************/
  if (Tdbp->GetMode() == MODE_INSERT)
    rc = fseek(Stream, 0, SEEK_END);
  else
    rc = fseek(Stream, Headlen, SEEK_SET);

  if (rc) {
    sprintf(g->Message, MSG(BAD_DBF_FILE), Tdbp->GetFile(g));
    return true;
    } // endif fseek

  return false;
  } // end of AllocateBuffer