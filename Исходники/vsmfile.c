NLM_EXTERN void ViewSortedProteins (SeqEntryPtr sep)
{
  Char         path [PATH_MAX];
  FILE        *fp;

  if (sep == NULL) return;
  TmpNam (path);
  fp = FileOpen(path, "w");
  if (fp == NULL) {
    Message (MSG_ERROR, "Unable to open %s", path);
    return;
  }
        
  WriteSortedProteinsToFile (fp, sep);

  FileClose(fp);

  LaunchGeneralTextViewer (path, "Sorted Proteins");
  FileRemove (path);
}