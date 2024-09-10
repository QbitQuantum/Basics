// Add, update, freshen, or delete zip entries in a zip file. argc; /*
//   Number of tokens in command line. argv; /* Command line tokens.
int ZipProcess(struct Globals *pG)
{
  int a; // attributes of zip file
  ulg c; // start of central directory
  struct flist *f; // steps through "found" linked list
  int i; // arg counter, root directory flag
  int k; // next argument type, marked counter, comment size, entry count
  int marks; // replaces k as marked counter
  ulg n; // total of entry len's

  // int o; /* true if there were any ZEN_OPEN errors
  char *p; // steps through option arguments
  int r; // temporary variable
  ulg t; // file time, length of central directory
  //  int           first_listarg = 0;  // index of first arg of "process these files" list
  struct zlist *v; // temporary variable
  struct zlist **w; // pointer to last link in "zfiles" list
  struct zlist *z; // steps through "zfiles" linked list
  int altered; // RP 173 counter for altered comments

  int DestType; // 1.75  destination drive type
  unsigned long TotFiles = 0;
  unsigned /* long */__int64 TotSize = 0;
  unsigned long KeptCnt = 0; // number of 'kept' files
  unsigned __int64 KeptSize = 0; // size of 'kept' files
  unsigned long ofs; // current file offset
  int fsz; // file size;
  int No_File = 0; // 1.75 try if file does not exist
  long hi;

  // Process arguments
  diag("processing lists", pG);

  if (pG->verbose)
  {
    switch (pG->action)
    {
      case ADD:
        diag("action = ADD", pG);
        break;
      case UPDATE:
        diag("action = UPDATE", pG);
        break;
      case FRESHEN:
        diag("action = FRESHEN", pG);
        break;
      case PURGE:
        diag("action = PURGE", pG);
    }

    // zcount is no. of entries in linked-list
    // zfiles is name of the linked-list of filenames for the archive
    Inform(pG, 0, IDIAG, "zcount=%d (no. of files in ZIP already)", pG->zcount);
  }

  // if first_listarg is 0, then we didn't got any fspecs on cmd line
  if (pG->doall && (pG->action == UPDATE || pG->action == FRESHEN))
  {
    // if -update or -freshen with no args, do all, but, when present, apply
    //   filters
    for (z = pG->zfiles; z != NULL; z = z->nxt)
    {
      z->mark = pG->pcount ? filter(z->zname, pG): 1;
    }
  }

  if ((r = check_dup(pG)) != ZEN_OK)
  // remove duplicates in list
    return (ziperr(r, pG));

  // Check option combinations
  // ?????
  if (pG->action == PURGE && (pG->dispose || pG->recurse || pG->key))
    return (ziperr(ZEN_PARMS12, pG));
  if (pG->linkput && pG->dosify)
  {
    Inform(pG, 0, IWARNING, "can't use -y with -k, -y ignored");
    pG->linkput = 0;
  }

  // AllowGrow is the "allow append" indicator
  if (!pG->zcount && ((pG->action == ADD) || (pG->action == UPDATE)))
    pG->AllowGrow = 55;
  //1;   // RP173 - create new file normally

  // if zcount is 0, then zipfile doesn't exist, or is empty
  if (pG->zcount == 0 && ((pG->action != ADD && pG->action != UPDATE) || !pG
    ->AllowGrow))
  {
    // RCV150199 added UPDATE
    Inform(pG, 0, IWARNING, "%s: not found or empty", pG->zipfile);
    if (pG->zcount)
      FREE(pG->zsort);
    return 0;
  }

  if (pG->zcount)
  {
    FREE(pG->zsort);
    pG->zsort = NULL;
  }

  DestType = DriveType(pG->zipfile);
  if (pG->verbose < 0)
    Inform(pG, 0, IDIAG, "Destination type = %d", DestType);

  // RP - check destination type - if CD set tempath to Windows Temp
  if (pG->tempath == NULL && (DestType != DRIVE_FIXED && DestType !=
    DRIVE_RAMDISK))
  {
    unsigned int plen;
    plen = GetTempPath(2047, pG->ewemsg);
    if (plen && (pG->tempath = (char*)MALLOC(plen + 1)) != NULL)
      lstrcpy(pG->tempath, pG->ewemsg);
    else
      return (ziperr(ZEN_MEM10, pG));
  }

  // If -b not specified, set temporary path to zipfile path
  if (pG->tempath == NULL && ((p = strrchr(pG->zipfile, '\\')) != NULL || (p =
    strrchr(pG->zipfile, ':')) != NULL))
  {
    if (*p == ':')
      p++;
    if ((pG->tempath = (char*)MALLOC((int)(p - pG->zipfile) + 1)) == NULL)
      return (ziperr(ZEN_MEM10, pG));
    r =  *p;
    *p = 0;
    lstrcpy(pG->tempath, pG->zipfile);
    *p = (char)r;
  }

  // NOTE: "k" is being redefined below this point. Now, it going to
  // track the no. of marked files in the "zfiles" linked list.
  // For each marked entry in "zfiles" linked list, if not deleting, check
  //   if a corresponding "external" file exists. If updating or freshening,
  //   compare date of "external" file with entry in orig zipfile. Unmark if it
  //   external file doesn't exist or is too old, else mark it. Entries that
  //   are marked will cause that file to be rezipped.
  diag("checking marked entries", pG);

  marks = 0; // Initialize marked count

  // zfiles is name of the linked-list of filenames for the archive
  #ifdef USE_STRM_INPUT
    if (!pG->UseInStream)
  #endif
  for (z = pG->zfiles; z != NULL; z = z->nxt)
  {
    if (z->mark)
    {
      ulg FileAttr;
      #ifdef USE_EF_UX_TIME
        ztimbuf f_utim, z_utim;
      #endif
      #ifdef USE_EF_UX_TIME
        if (pG->action != PURGE && ((t = filetime(z->name, &FileAttr, (long*)
          NULL, &f_utim, pG)) == 0 || t < pG->before || ((pG->action == UPDATE
          || pG->action == FRESHEN) && (get_ef_ux_ztime(z, &z_utim) ?
          f_utim.modtime <= z_utim.modtime: t <= z->tim)) || (pG->ArchiveFiles
          && pG->action == FRESHEN && !(FileAttr &A_ARCHIVE))))
        {
          z->mark = 0;
          z->trash = t && t >= pG->before; // delete if -um or -fm
          if (pG->verbose)
          {
            Inform(pG, 0, 0, "%s %s", z->name, z->trash ? "up to date" :
              "missing or early");
          }
        }
        else
          marks++;
        // incr. number of marked entries
      #else
        if (pG->action != PURGE)
        {
          t = filetime(z->name, &FileAttr, &fsz /* NULL */, NULL, pG);
          //           && (
          //               (t = filetime( z->name, &FileAttr, &fsz /*NULL*/, NULL, pG )) == 0
          if ((t == 0 || t < pG->before || ((pG->action == UPDATE || pG->action
            == FRESHEN) && t <= z->tim) || (pG->ArchiveFiles && pG->action ==
            FRESHEN && !(FileAttr &A_ARCHIVE))) || ( /* (int) */fsz <  - 2))
          // RP - check size
          {
            z->mark = 0;
            z->trash = (t && t >= pG->before) || ( /* (int) */fsz <  - 2);
              // delete if -um or -fm
            //              z->trash = t && t >= pG->before;  // delete if -um or -fm
            if (pG->verbose)
            {
              Inform(pG, 0, 0, "%s %s", z->name, z->trash ? (int)fsz <  - 2 ?
                "now too big" : "up to date": "missing or early");
              //                    z->trash ? "up to date" : "missing or early" );
            }
          }
          else
          {
            TotSize += fsz;
            TotFiles++;
            marks++;
          }
        }
        else
        // PURGE
          marks++;
        // incr. number of marked entries
      #endif
    }
  }

  #ifdef USE_STRM_INPUT
    if (pG->UseInStream)
      marks = 1;
  #endif

  // RP - verify file specified to 'Purge'
  if (pG->action == PURGE && !marks)
    return (ziperr(ZEN_NONE03, pG));

  // Remove entries from "found" linked list if: Action is PURGE or FRESHEN
  //   or No "external" matching file is found, or if found, but is too old or
  //   The external file is equal to the ziparchive name while ziparchive name
  //   != "-" If filetime() returns any valid time, then at least we know the
  //   file was found.
  diag("checking new entries", pG);

  // fileio.c built the found list
  #ifdef USE_STRM_INPUT
    if (!pG->UseInStream)
  #endif
  for (f = pG->found; f != NULL;)
  {
    int sz = 0;
    if (pG->action == PURGE || pG->action == FRESHEN || (t = filetime(f->name,
      (ulg*)NULL, &sz, (ztimbuf*)NULL, pG)) == 0
    //         || (t = filetime( f->name, ( ulg * )NULL, ( long * )NULL, ( ztimbuf * )NULL, pG )) == 0
     || t < pG->before || (namecmp(GetFullPath(pG, f->name), pG->zipfile) == 0
       && strcmp(pG->zipfile, "-")) || (sz <  - 2))
    {
      if (sz <  - 2)
        Inform(pG, ZEN_SIZE04, IWARNING, "%s is too large", f->name); 
      if (pG->verbose && t < pG->before)
      {
        Inform(pG, 0, IDIAG, "rejecting %s as too early", f->name );
      }
      if (pG->verbose < 0)
        Inform(pG, 0, IDIAG, "expel being called for %s", f->name);
      f = fexpel(f, pG); // delete an entry in the list.
    }
    else
    // file found, and not too old.
      f = f->nxt;
    // save this one, link it up.
  }

  if (pG->found == NULL)
    diag("found list empty - a", pG);
  else
    diag("found list has at least one entry - a", pG);

  if ( /* ( pG->action == UPDATE || pG->action == FRESHEN ) && */(pG->adjust <=
    0))
    pG->adjust = 0;

  // Make sure there's something left to do RP adjust always 1
  if (marks == 0 && pG->found == NULL && !(pG->zfiles != NULL && (pG->latest ||
    pG->adjust || pG->junk_sfx)))
  {
    // FOUND WAS NULL HERE, so just figure out which error message to show
    //   the user
    if (pG->action == UPDATE || pG->action == FRESHEN)
    {
      finish(pG);
      Inform(pG, 0, IWARNING, "no files %s", (pG->action == UPDATE) ? "updated"
        : "freshened");
      return 0;
    }
    else if (pG->zfiles == NULL && (pG->latest || pG->adjust || pG->junk_sfx))
    {
      return (ziperr(ZEN_NAME01, pG));
    }
    else if (pG->recurse && (pG->pcount == 0) && (!pG->doall))
    //first_listarg > 0) )
    {
      // add the list of filenames from cmd line to error msg
      ///      for ( i = first_listarg; i < argc; i++ )
      ///        lstrcat( lstrcat( pG->errbuf, " " ), argv[i] );
      return (ziperr(ZEN_NONE01, pG));
    }
    else
      return (ziperr(ZEN_NONE02, pG));
  }

  // AllowGrow is false if writing temporary file
  pG->AllowGrow = (pG->AllowGrow && (marks == 0)
    // is allowed and no changes to existing
   && (pG->zipbeg || pG->zfiles != NULL) // something to append to
  );

  // continue on to add new files
  a = 0;

  // ignore self-extracting code in front of the zip file (for -J)
  if (pG->junk_sfx)
    pG->zipbeg = 0;

  // Count files and sizes which we have to Keep; RP Added
  w = &pG->zfiles;
  while ((z =  *w) != NULL)
  {
    if (pG->global_abort_sw)
      return (ziperr(ZEN_ABORT, pG));
    if (!z->mark)
    {
      KeptSize += (z->siz + (ulg)(4+LOCHEAD) + (ulg)z->nam + (ulg)z->ext);
      if (z->lflg &8)
        KeptSize += 16;
      KeptCnt++;
    }

    w = &z->nxt;
  }

  //Inform( pG, 0, IDIAG, "Kept = %u %Lu Total = %u %Lu", KeptCnt, KeptSize, TotFiles, TotSize );
  // Count files and sizes which we have to process; RCV Added
  // First the files in the old zip file...
  // RP - already calculated with new sizes
  // And the found list...
  for (f = pG->found; f != NULL; f = f->nxt)
  {
    if (pG->global_abort_sw)
      return (ziperr(ZEN_ABORT, pG));
    TotSize += f->len;
    TotFiles++;
  }
  //    Inform( pG, 0, IDIAG, "Found = %u %u", tc, ts );
  // OPEN ZIP FILE and temporary output file
  //  diag( "opening zip file and creating temporary zip file", pG );
  pG->hInz = INVALID_HANDLE_VALUE; //0;
  pG->hTempzf = INVALID_HANDLE_VALUE;
  pG->tempzn = 0;


  if (!pG->AllowGrow)
  {
    // check file exists
    No_File = access(pG->zipfile, 0) && errno == ENOENT;
    if (No_File && DestType == DRIVE_FIXED || DestType == DRIVE_RAMDISK)
    {
      // create file using given name
      diag("in dllzip - ready to create new file", pG);
      if ((pG->hOutz = CreateFile(pG->zipfile, GENERIC_WRITE, 0, NULL,
        CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL)) !=
        INVALID_HANDLE_VALUE)
      {
        pG->tempzip = pG->zipfile;

        pG->hTempzf = pG->hOutz;
        pG->AllowGrow =  - 1; // new files do grow
      }
    }
  }

  if (pG->AllowGrow > 0)
  {
    // zipfile is not stdout, and we are allowed to append
    // AllowGrow is true if we're just appending (-g)
    diag("in dllzip - ready to open for appending", pG);
    if ((pG->hOutz = CreateFile(pG->zipfile, GENERIC_READ | GENERIC_WRITE, 0,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
      NULL)) == INVALID_HANDLE_VALUE)
      return (ziperr(ZEN_NAME02, pG));
    pG->tempzip = pG->zipfile;

    pG->hTempzf = pG->hOutz;

    /* long */
    hi = 0;
    if (SetFilePointer(pG->hOutz, pG->cenbeg, &hi, FILE_BEGIN) ==
      INVALID_SET_FILE_POINTER && GetLastError())
      return (ziperr(GetLastError() ? ZEN_READ01 : ZEN_EOF01, pG));
    pG->tempzn = pG->cenbeg;
  }

  if (!pG->AllowGrow)
  {
    diag("in dllzip - ready to open for Exclusive Read", pG);
    if ((pG->zfiles != NULL || pG->zipbeg) && (pG->hInz = CreateFile(pG
      ->zipfile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL |
      FILE_FLAG_SEQUENTIAL_SCAN, NULL)) == INVALID_HANDLE_VALUE)
      return (ziperr(ZEN_NAME03, pG));
    if ((pG->tempzip = tempname(pG)) == NULL)
      return (ziperr(ZEN_MEM11, pG));

    //		if (pG->Verbose)
    Inform(pG, 0, IDIAG, "Temp Filename = %s", pG->tempzip);
    if ((pG->hTempzf = pG->hOutz = CreateFile(pG->tempzip, GENERIC_WRITE, 0,
      NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS |
      FILE_ATTRIBUTE_TEMPORARY, NULL)) == INVALID_HANDLE_VALUE)
      return (ziperr(ZEN_TEMP01, pG));
  }

  if (!pG->AllowGrow)
  {
    TotFiles += KeptCnt;
    TotSize += KeptSize;
  }
  // Pass total number of files and Total Filesize.    (moved)
  user_callback(zacCount, 0, TotFiles, NULL, pG);
  user_callback(zacSize, (long)(TotSize >> 32), ((unsigned)TotSize), NULL, pG);
  pG->BatchStarted = 1;

  if (!pG->AllowGrow && pG->zipbeg)
  {
    // copy a compressed file from old archive to new archive
    user_callback(zacItem, 0, pG->zipbeg, "SFX", pG);
    if ((r = fcopy(pG->hInz, pG->hOutz, pG->zipbeg, pG)) != ZEN_OK)
      return (ziperr(r, pG));
    pG->tempzn = pG->zipbeg;
  }

  // o = 0; /* no ZEN_OPEN errors yet
  // Process zip file, copying from old archive to new archive. Rezip any
  //   marked files
  if (pG->zfiles != NULL)
    diag("going through old zip file", pG);
  w = &pG->zfiles;

  while ((z =  *w) != NULL)
  {
    if (pG->global_abort_sw)
    {
      return (ziperr(ZEN_ABORT, pG));
    }

    if (z->mark == 1)
    {
      // This file is marked
      // if not deleting, rezip it
      if (pG->action != PURGE)
      {
        Inform(pG, 0, 0, "updating: %s", Oem2Iso(z->zname, pG));

        // zipup is in file zipup.c
        if ((r = zipup(z, pG->hOutz, pG)) != ZEN_OK && (int)(char)(r &0xFF) !=
          ZEN_OPEN && (int)(char)(r &0xFF) != ZEN_MISS)
        {
          return (ziperr(r, pG));
        }

        if ((int)(char)(r &0xFF) == ZEN_OPEN || (int)(char)(r &0xFF) ==
          ZEN_MISS)
        {
          if ((int)(char)(r &0xFF) == ZEN_OPEN)
          {
            Inform(pG, r, IWARNING, "could not open for reading: %s", z->name);
            user_callback(4, r, 0, z->name, pG);
          }
          else
          {
            Inform(pG, 0, IWARNING, "file and directory with the same name: %s",
              z->name);
            user_callback(4, r, 0, z->name, pG);
          }

          Inform(pG, 0, IWARNING, "will just copy entry over: %s", z->zname);

          if ((r = zipcopy(z, pG->hInz, pG->hOutz, pG)) != ZEN_OK)
          {
            sprintf(pG->errbuf, "was copying %s", z->zname);
            return (ziperr(r, pG));
          }

          z->mark = 0;
        }

        w = &z->nxt;
        pG->files_acted_on++;
      }
      else
      {
        // desired action is DELETE, this file marked
        // NOTE: no progress bar supt for DELETE yet
        Inform(pG, 0, 0, "deleting: %s", Oem2Iso(z->zname, pG));

        v = z->nxt; // delete entry from list
        FREE(z->name);
        FREE(z->zname);
        if (z->ext)
          FREE(z->extra);
        if (z->cext && z->cextra != z->extra)
          FREE(z->cextra);
        if (z->com)
          FREE(z->comment);
        FREE(z);
        *w = v;
        pG->zcount--;
        pG->files_acted_on++;
      }
    }
    else
    {
      // this file wasn't marked
      // copy the original entry verbatim
      if (!pG->AllowGrow)
      {
        Inform(pG, 0, 0, "keeping: %s", Oem2Iso(z->zname, pG));
        if ((r = zipcopy(z, pG->hInz, pG->hOutz, pG)) != ZEN_OK)
        {
          sprintf(pG->errbuf, "was copying %s", z->zname);

          // user_callback ( zacEndOfBatch, 0, 0, NULL, pG ); // done with a
          // batch of files
          return (ziperr(r, pG));
        }
      }
      w = &z->nxt;
    }
  } // end while

  // Process the "found" list, adding them to the zip file.
  // This is used to add files that weren't already in the archive.
  if (pG->verbose)
  {
    Inform(pG, 0, IDIAG, "Zipping up %d NEW entries from found list", pG
      ->fcount);
  }

  // For each new file to add (src names in found list), make a new entry
  //   for it in the "zfiles" linked list, zip up the new file, then remove the
  //   entry from the found list.
  // The last item in the for loop control deallocates spc for fname that
  //   was just zipped up
  for (f = pG->found; f != NULL; f = fexpel(f, pG))
  {
    // add a new entry to "zfiles" list, before we zip up the file. That way
    //   we'll be ready to update the ZIP file's directory later.
    if (pG->global_abort_sw)
    {
      // user_callback ( zacEndOfBatch, 0, 0, NULL, pG ); // done with a
      // batch of files
      return (ziperr(ZEN_ABORT, pG));
    }

    if ((z = (struct zlist*)MALLOC(sizeof(struct zlist))) == NULL)
    {
      return (ziperr(ZEN_MEM12, pG));
    }

    // RP 1.73 clear all fields
    memset(z, 0, sizeof(struct zlist));

    // Similar names below are confusing: f->name f->zname z->name z->zname
    // z z->nxt = NULL;
    z->name = f->name;
    f->name = NULL;

    z->zname = f->zname;
    f->zname = NULL;

    // z z->ext = z->cext = z->com = 0;
    // z z->extra = z->cextra = z->comment = NULL;
    // pRP173 z->ext = strlen( f->passw ); //Added RAEL
    // pRP173 z->extra = f->passw; //Added RAEL for per file password
    z->passw = f->passw; // p
    f->passw = NULL; // Added RAEL
    z->mark = 1;
    z->dosflag = f->dosflag;
    z->len = f->len; // RCV added.

    // zip it up
    Inform(pG, 0, 0, "  adding: %s", Oem2Iso(z->zname, pG));

    // This is it - try to zip up new file
    if ((r = zipup(z, pG->hOutz, pG)) != ZEN_OK && (int)(char)(r &0xFF) !=
      ZEN_OPEN && (int)(char)(r &0xFF) != ZEN_MISS)
    {
      return (ziperr(r, pG));
    }

    if ((int)(char)(r &0xFF) == ZEN_OPEN || (int)(char)(r &0xFF) == ZEN_MISS)
    {
      // o = 1;
      if ((int)(char)(r &0xFF) == ZEN_OPEN)
      {
        Inform(pG, r, IWARNING, "could not open for reading: %s", z->name);
      }
      else
      {
        Inform(pG, 0, IWARNING, "file and directory with the same name: %s", z
          ->name);
      }

      FREE(z->name);
      FREE(z->zname);
      FREE(z);
    }
    else
    {
      // "zipup" of this file was good
      *w = z;
      w = &z->nxt;
      pG->zcount++;
      pG->files_acted_on++;
    }
  }

  // Write central directory and end header to temporary zip
  diag("writing central directory", pG);
  hi = 0;
  ofs = SetFilePointer(pG->hOutz, 0, &hi, FILE_CURRENT);
  if (hi || (ofs > 0xFFFFFFF0u) || (ofs == INVALID_SET_FILE_POINTER &&
    GetLastError()))
  {
    return ziperr(ZEN_SIZE01, pG);
  }

  k = 0; // keep count of new fnames for ZIPfile's end header
  c = pG->tempzn; // get start of central directory
  n = t = 0;
  altered = 0; // RP 173 - count changes
  for (z = pG->zfiles; z != NULL; z = z->nxt)
  {
    // Handle callback and result for the filecomments... DLL v1.609,
    // Component v1.60L
    if (pG->action != PURGE)
    {
      memset(pG->ewetmp, 0, 513); // Clear all
      strncpy(pG->ewetmp, z->zname, 255); // Copy external filename
      if (z->com)
      // Copy old comment if present
        strncpy(pG->ewetmp + 256, z->comment, min(z->com, 255));
      else
        z->comment = 0;
      user_callback(12, 0, z->com, pG->ewetmp, pG);
      if (pG->callbackdata.error_code)
      {
        // User changed the comment
        FREE(z->comment);
        z->com = pG->callbackdata.fsize;
        if ((z->comment = (char*)MALLOC(z->com + 1)) == NULL)
          return (ziperr(ZEN_MEM37, pG));
        strncpy(z->comment, pG->callbackdata.filenameormsg, z->com + 1);
        altered++;
      }
    }

    if (pG->files_acted_on < altered)
    // RP 173 - comments changed is acted on
      pG->files_acted_on = altered;

    if ((r = putcentral(z, pG->hOutz, pG)) != ZEN_OK)
    {
      // v1.6014
      return (ziperr(r, pG));
    }

    pG->tempzn += 4+CENHEAD + z->nam + z->cext + z->com;
    n += z->len;
    t += z->siz;
    k++;
  }

  if (k == 0)
    Inform(pG, 0, IWARNING, "zip file empty");

  if ((pG->verbose) && (pG->action == ADD) && (!pG->global_error_code) && (pG
    ->files_acted_on > 0))
  {
    Inform(pG, 0, 0, "Total Bytes=%lu, compr bytes=%lu -> %d%% savings", n, t,
      percent(n, t));
  }

  t = pG->tempzn - c; // compute length of central
  diag("writing end of central directory", pG);

  if (k && ((r = putend(k, t, c, pG->hOutz, pG)) != ZEN_OK))
  {
    return (ziperr(r, pG));
  }

  //       if ( pG->hInz != INVALID_HANDLE_VALUE )
  //       {
  Close_Handle(&pG->hInz);
  //         pG->hInz = INVALID_HANDLE_VALUE;
  //       }

  // pG->tempzf = NULL;
  // if ( fclose ( pG->y ) )
  pG->hTempzf = INVALID_HANDLE_VALUE; //NULL;
  //       if ( pG->hOutz != INVALID_HANDLE_VALUE && !CloseHandle( pG->hOutz ) )
  if (!Close_Handle(&pG->hOutz))
  {
    return (ziperr(pG->AllowGrow ? ZEN_WRITE03 : ZEN_TEMP02, pG));
  }

  //       pG->hOutz = INVALID_HANDLE_VALUE;

  #ifdef DYN_ALLOC
    lm_free(pG);
  #endif

  //  if ( pG->verbose )
  //    Inform( pG, 0, IDIAG, "Files closed in: %X out: %x", pG->hInz, pG->hOutz );
  // Replace old zip file with new zip file, leaving only the new one
  //  if ( !pG->AllowGrow )     // && lstrcmp(pG->zipfile, pG->tempzip))
  if (!pG->AllowGrow && (k || pG->action != PURGE))
  // && lstrcmp(pG->zipfile, pG->tempzip))
  {
    diag("replacing old zip file with new zip file", pG);
    if ((r = replace(pG->zipfile, pG->tempzip, pG)) != ZEN_OK)
    {
      Inform(pG, 0, IWARNING, "new zip file left as: %s", pG->tempzip);
      FREE(pG->tempzip);
      pG->tempzip = NULL;

      return (ziperr(r, pG));
    }

    FREE(pG->tempzip);
    pG->tempzip = NULL;
  }

  // 1.78.1.2
  if (!k && pG->action == PURGE)
  // empty file - remove
  {
    a = pG->latest = 0;
    DeleteFile(pG->zipfile);
    if (!pG->AllowGrow)
      DeleteFile(pG->tempzip);
  }

  pG->tempzip = NULL;
  if (a)
    setfileattr(pG->zipfile, a);

  // Reset the archive bit when needed for all successfull zipped files
  if (pG->ResetArchiveBit && pG->action != PURGE)
  {
    unsigned cnt = 0; // 1.71.0.0 added extra callbacks
    diag("resetting archive bits", pG);
    for (z = pG->zfiles; z != NULL; z = z->nxt)
      if (z->mark)
        cnt++;
    if (cnt)
    {
      // new file op.
      // Pass total number of files. filesize.
      user_callback(zacXItem, 1, cnt, "*resetting archive bits", pG);
    }

    cnt = 0;
    for (z = pG->zfiles; z != NULL; z = z->nxt)
    {
      if (z->mark)
      {
        char *fullname;
        if (++cnt == 30)
        {
          user_callback(zacXProgress, 1, cnt, "", pG);
          cnt = 0;
          if (pG->global_abort_sw)
            break;
        }

        fullname = GetFullPath(pG, z->name); // v.16017
        if (!SetFileAttributes(fullname, GetFileAttributes(fullname)
          &~FILE_ATTRIBUTE_ARCHIVE))
        {
          Inform(pG, 0, IWARNING, "Archive bit could not be set for: %s", z
            ->name);
        }
      }
    }

    if (cnt)
    {
      user_callback(zacXProgress, 1, cnt, "", pG); // last few
    }
  }

  finish(pG);
  return 0;
}