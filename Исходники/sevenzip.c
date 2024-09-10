int Unseven(const char *filename, STRING **list)
{
  CFileInStream archiveStream;
  CLookToRead lookStream;
  CSzArEx db;
  SRes res;
  ISzAlloc allocImp;
  ISzAlloc allocTempImp;
  UInt16 *temp = NULL;
  size_t tempSize = 0;
  Bool do_save = (globaldata.gd_inidata->archive_dir && *(globaldata.gd_inidata->archive_dir))? False : True;
  char *subdir = NULL;
  // UInt32 parents[NUM_PARENTS_MAX];

//  printf("\n7z ANSI-C Decoder " MY_VERSION_COPYRIGHT_DATE "\n\n");

  if (!filename || !*filename) return -1; // error

  #if defined(_WIN32) && !defined(USE_WINDOWS_FILE) && !defined(UNDER_CE)
  g_FileCodePage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
  #endif

  allocImp.Alloc = SzAlloc;
  allocImp.Free = SzFree;

  allocTempImp.Alloc = SzAllocTemp;
  allocTempImp.Free = SzFreeTemp;

  #ifdef UNDER_CE
  if (InFile_OpenW(&archiveStream.file, L"\test.7z"))
  #else
  if (InFile_Open(&archiveStream.file, filename))
  #endif
  {
    PrintError("can not open input file");
    return -1;
  }

  FileInStream_CreateVTable(&archiveStream);
  LookToRead_CreateVTable(&lookStream, False);
  
  lookStream.realStream = &archiveStream.s;
  LookToRead_Init(&lookStream);

  CrcGenerateTable();

  SzArEx_Init(&db);
  
  res = SzArEx_Open(&db, &lookStream.s, &allocImp, &allocTempImp);
  
    if (res == SZ_OK)
    {
      UInt32 i;

      /*
      if you need cache, use these 3 variables.
      if you use external function, you can make these variable as static.
      */
      UInt32 blockIndex = 0xFFFFFFFF; /* it can have any value before first call (if outBuffer = 0) */
      Byte *outBuffer = 0; /* it must be 0 before first call for each new archive. */
      size_t outBufferSize = 0;  /* it can have any value before first call (if outBuffer = 0) */

      for (i = 0; i < db.NumFiles; i++)
      {
        size_t offset = 0;
        size_t outSizeProcessed = 0;
        // const CSzFileItem *f = db.Files + i;
        size_t len;
        unsigned isDir = SzArEx_IsDir(&db, i);
        len = SzArEx_GetFileNameUtf16(&db, i, NULL);
        // len = SzArEx_GetFullNameLen(&db, i);

        if (len > tempSize)
        {
          SzFree(NULL, temp);
          tempSize = len;
          temp = (UInt16 *)SzAlloc(NULL, tempSize * sizeof(temp[0]));
          if (!temp)
          {
            res = SZ_ERROR_MEM;
            break;
          }
        }

        SzArEx_GetFileNameUtf16(&db, i, temp);
/*
    { // progression output
      static char s[256];
      snprintf(s, 255, _("Extracting (%d%%)"), ((i + 1) * 100) / db.NumFiles);
      HandleSemaphoreText(s, list, !i ? 1 : 0);
    }*/
        if (isDir)
          ;//printf("/");
        else
        {
          res = SzArEx_Extract(&db, &lookStream.s, i,
              &blockIndex, &outBuffer, &outBufferSize,
              &offset, &outSizeProcessed,
              &allocImp, &allocTempImp);
          if (res != SZ_OK)
            break;
        }

        // write data to disk        
        {
          CSzFile outFile;
          size_t processedSize;
          size_t j;
          UInt16 *name = (UInt16 *)temp;
          const UInt16 *destPath = (const UInt16 *)name;
          WRes wres;
 
          for (j = 0; name[j] != 0; j++)
            if (name[j] == '/')
            {
              name[j] = 0;
              MyCreateDir(name, &subdir, &do_save);
              name[j] = CHAR_PATH_SEPARATOR;
            }
    
          if (isDir)
          {
            MyCreateDir(destPath, &subdir, &do_save);
            //printf("\n");
            continue;
          }
          if (do_save == False) continue;
          wres = OutFile_OpenUtf16(&outFile, destPath, &subdir, &do_save);
          if (wres == -1) continue;
          if (wres)
          {
            PrintError("can not open output file");
            res = SZ_ERROR_FAIL;
            break;
          }

          processedSize = outSizeProcessed;
          
          if (File_Write(&outFile, outBuffer + offset, &processedSize) != 0 || processedSize != outSizeProcessed)
          {
            PrintError(_("can not write output file"));
            res = SZ_ERROR_FAIL;
            break;
          }
          
          if (File_Close(&outFile))
          {
            PrintError(_("can not close output file"));
            res = SZ_ERROR_FAIL;
            break;
          }
          
          #ifdef USE_WINDOWS_FILE
          if (SzBitWithVals_Check(&db.Attribs, i))
            SetFileAttributesW(destPath, db.Attribs.Vals[i]);
          #endif
        }
        //printf("\n");
      }
      IAlloc_Free(&allocImp, outBuffer);
    }

  SzArEx_Free(&db, &allocImp);
  SzFree(NULL, temp);

  File_Close(&archiveStream.file);
  
  if (res == SZ_OK)
  {
    //printf("\nEverything is Ok\n");
    return 0;
  }
  
  if (res == SZ_ERROR_UNSUPPORTED)
    PrintError(_("decoder doesn't support this archive"));
  else if (res == SZ_ERROR_MEM)
    PrintError(_("can not allocate memory"));
  else if (res == SZ_ERROR_CRC)
    PrintError(_("CRC error"));
  else
    printf("<br />ERROR #%d\n", res);
  
  return -1;
}