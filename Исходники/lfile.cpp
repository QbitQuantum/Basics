VOID UpdateFilebase (USHORT KeepDate)
{
   FILE *fp;
   DIR *dir;
   ULONG Total, Added;
   CHAR *p, Path[128], Temp[128];
   time_t today;
   struct stat statbuf;
   struct tm *ltm;
   struct dirent *ent;
   class TFileData *Data;
   class TFileBase *File;
   class TPacker *Packer;

   printf (" * Updating filebase\r\n");

   unlink ("file_id.diz");
   Packer = new TPacker (Cfg->SystemPath);

   if ((Data = new TFileData (Cfg->SystemPath)) != NULL) {
      if (Data->First () == TRUE)
         do {
            Total = 0L;
            Added = 0L;
            cprintf (" +-- %-15.15s %-32.32s ", Data->Key, Data->Display);
            if ((File = new TFileBase (Cfg->SystemPath, Data->Key)) != NULL) {
               strcpy (Temp, Data->Download);
               if (Temp[strlen (Temp) - 1] == '\\' || Temp[strlen (Temp) - 1] == '/')
                  Temp[strlen (Temp) - 1] = '\0';

               if (File->First () == TRUE)
                  do {
                     sprintf (Path, "%s%s", Data->Download, File->Name);
                     if (stat (AdjustPath (Path), &statbuf))
                        File->Delete ();
                  } while (File->Next () == TRUE);

               File->SortByName ();
               if ((dir = opendir (AdjustPath (Temp))) != NULL) {
                  while ((ent = readdir (dir)) != NULL) {
                     if (!strcmp (ent->d_name, ".") || !strcmp (ent->d_name, ".."))
                        continue;
                     if (!stricmp (ent->d_name, "files.bbs") || !stricmp (ent->d_name, "descript.ion"))
                        continue;
                     if (File->Read (ent->d_name) == FALSE) {
                        sprintf (Path, "%s%s", Data->Download, ent->d_name);
                        if (!stat (AdjustPath (Path), &statbuf)) {
                           File->Clear ();
                           strcpy (File->Area, Data->Key);
                           strcpy (File->Name, ent->d_name);
                           strcpy (File->Complete, Path);
                           File->Size = statbuf.st_size;
                           ltm = localtime ((time_t *)&statbuf.st_mtime);
                           File->Date.Day = (UCHAR)ltm->tm_mday;
                           File->Date.Month = (UCHAR)(ltm->tm_mon + 1);
                           File->Date.Year = (USHORT)(ltm->tm_year + 1900);
                           File->Date.Hour = (UCHAR)ltm->tm_hour;
                           File->Date.Minute = (UCHAR)ltm->tm_min;
                           if (KeepDate == FALSE) {
                              today = time (NULL);
                              ltm = localtime (&today);
                              File->UplDate.Day = (UCHAR)ltm->tm_mday;
                              File->UplDate.Month = (UCHAR)(ltm->tm_mon + 1);
                              File->UplDate.Year = (USHORT)(ltm->tm_year + 1900);
                              File->UplDate.Hour = (UCHAR)ltm->tm_hour;
                              File->UplDate.Minute = (UCHAR)ltm->tm_min;
                           }
                           else {
                              File->UplDate.Day = File->Date.Day;
                              File->UplDate.Month = File->Date.Month;
                              File->UplDate.Year = File->Date.Year;
                              File->UplDate.Hour = File->Date.Hour;
                              File->UplDate.Minute = File->Date.Minute;
                           }
                           File->Uploader = "Sysop";
                           File->CdRom = Data->CdRom;
                           File->Description->Add ("Description missing");
                           if (Packer != NULL) {
                              if (Packer->CheckArc (Path) == TRUE) {
#if defined(__LINUX__)
                                 mkdir ("lfiletmp", 0666);
#else
                                 mkdir ("lfiletmp");
#endif
                                 if (strstr (Packer->UnpackCmd, "%3") == NULL && strstr (Packer->UnpackCmd, "%f") == NULL)
                                    strcat (Packer->UnpackCmd, " %3");
                                 Packer->DoUnpack (Path, "lfiletmp", "file_id.diz");
                                 strcpy (Temp, "lfiletmp\\file_id.diz");
                                 if (!stat (AdjustPath (Temp), &statbuf)) {
                                    if ((fp = fopen (Temp, "rt")) != NULL) {
                                       File->Description->Clear ();
                                       while (fgets (Temp, sizeof (Temp) - 1, fp) != NULL) {
                                          if ((p = strchr (Temp, '\n')) != NULL)
                                             *p = '\0';
                                          if ((p = strchr (Temp, '\r')) != NULL)
                                             *p = '\0';
                                          File->Description->Add (Temp);
                                       }
                                       fclose (fp);
                                    }
                                    strcpy (Temp, "lfiletmp\\file_id.diz");
                                    unlink (AdjustPath (Temp));
                                 }
                                 rmdir ("lfiletmp");
                              }
                           }
                           File->Add ();
                           Added++;
                        }
                     }
                     Total++;
                  }
                  closedir (dir);
               }
               delete File;
            }
            cprintf ("Total: %5lu Added: %5lu\r\n", Total, Added);
         } while (Data->Next () == TRUE);
      delete Data;
   }

   if (Packer != NULL)
      delete Packer;
}