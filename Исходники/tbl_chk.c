static BioseqPtr FetchBioseqFromSmartNotId (CharPtr accn, Uint2Ptr pEntityID)
{
  BioseqPtr         bsp;
  Char              cmmd [256];
  Pointer           dataptr;
  Uint2             datatype;
  Uint2             entityID;
  FILE*             fp;
  OMProcControlPtr  ompcp;
  ObjMgrProcPtr     ompp;
  Char              path [PATH_MAX];
  Char              err_path [PATH_MAX];
  SeqEntryPtr       sep = NULL;
  SeqIdPtr          sip;
  TextSeqIdPtr      tsip;
  Int4              gi = 0;
  ValNodePtr        vnp;
  time_t            t1, t2;

  if (srcchkfetchcmd == NULL) {
    if (GetAppParam ("SEQUIN", "TBL_CHK", "FETCHSCRIPT", NULL, cmmd, sizeof (cmmd))) {
    	srcchkfetchcmd = StringSaveNoNull (cmmd);
    }
  }
  if (srcchkfetchcmd == NULL) {
    if (GetAppParam ("SEQUIN", "SMART", "FETCHSCRIPT", NULL, cmmd, sizeof (cmmd))) {
    	srcchkfetchcmd = StringSaveNoNull (cmmd);
    }
  }
  if (srcchkfetchcmd == NULL) return NULL;

  TmpNam (path);

  t1 = time(NULL);
#ifdef OS_UNIX
  sprintf (err_path, "%s.err", path);
  sprintf (cmmd, "csh %s %s > %s 2>%s", srcchkfetchcmd, accn, path, err_path);
  system (cmmd);
#endif
#ifdef OS_MSWIN
  sprintf (cmmd, "%s %s -o %s", srcchkfetchcmd, accn, path);
  system (cmmd);
#endif

  fp = FileOpen (path, "r");
  if (fp == NULL) {
    FileRemove (path);
#ifdef OS_UNIX
    FileRemove (err_path);
#endif
    return OM_MSG_RET_ERROR;
  }
  dataptr = ReadAsnFastaOrFlatFile (fp, &datatype, &entityID, FALSE, FALSE, TRUE, FALSE);
  FileClose (fp);
  FileRemove (path);
#ifdef OS_UNIX
  FileRemove (err_path);
#endif

  if (dataptr == NULL) return NULL;

  sep = GetTopSeqEntryForEntityID (entityID);

  if (sep == NULL) return NULL;
  sip = SmartGuessMakeId (accn);
  bsp = BioseqFindInSeqEntry (sip, sep);
  sip = SeqIdFree (sip);
  if (debug_mode) {
    t2 = time(NULL);
    if (t2 - t1 > 1) {
      printf("Time to download %s from SMART:%d\n", accn, t2 - t1);
    }
  }
  if (pEntityID != NULL) {
    *pEntityID = entityID;
  }
  return bsp;
}