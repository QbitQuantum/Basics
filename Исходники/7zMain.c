int MY_CDECL main(int numargs, char *args[])
{
  CFileInStream archiveStream;
  CLookToRead lookStream;
  CSzArEx db;
  SRes res;
  ISzAlloc allocImp;
  ISzAlloc allocTempImp;
  UInt16 *temp = NULL;
  size_t tempSize = 0;
  // UInt32 parents[NUM_PARENTS_MAX];

  printf("\n7z ANSI-C Decoder " MY_VERSION_COPYRIGHT_DATE "\n\n");

  if (numargs == 1)
  {
    printf(
      "Usage: 7zDec <command> <archive_name>\n\n"
      "<Commands>\n"
      "  e: Extract files from archive (without using directory names)\n"
      "  l: List contents of archive\n"
      "  t: Test integrity of archive\n"
      "  x: eXtract files with full paths\n");
    return 0;
  }
  
  if (numargs < 3)
  {
    PrintError("incorrect command");
    return 1;
  }

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
  if (InFile_Open(&archiveStream.file, args[2]))
  #endif
  {
    PrintError("can not open input file");
    return 1;
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
    char *command = args[1];
    int listCommand = 0, testCommand = 0, fullPaths = 0;
    
    if (strcmp(command, "l") == 0) listCommand = 1;
    else if (strcmp(command, "t") == 0) testCommand = 1;
    else if (strcmp(command, "e") == 0) { }
    else if (strcmp(command, "x") == 0) { fullPaths = 1; }
    else
    {
      PrintError("incorrect command");
      res = SZ_ERROR_FAIL;
    }

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
        if (listCommand == 0 && isDir && !fullPaths)
          continue;
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
        if (SzArEx_GetFullNameUtf16_Back(&db, i, temp + len) != temp)
        {
          res = SZ_ERROR_FAIL;
          break;
        }
        */

        if (listCommand)
        {
          char attr[8], s[32], t[32];
          UInt64 fileSize;

          GetAttribString(SzBitWithVals_Check(&db.Attribs, i) ? db.Attribs.Vals[i] : 0, isDir, attr);

          fileSize = SzArEx_GetFileSize(&db, i);
          UInt64ToStr(fileSize, s);
          
          if (SzBitWithVals_Check(&db.MTime, i))
            ConvertFileTimeToString(&db.MTime.Vals[i], t);
          else
          {
            size_t j;
            for (j = 0; j < 19; j++)
              t[j] = ' ';
            t[j] = '\0';
          }
          
          printf("%s %s %10s  ", t, attr, s);
          res = PrintString(temp);
          if (res != SZ_OK)
            break;
          if (isDir)
            printf("/");
          printf("\n");
          continue;
        }

        fputs(testCommand ?
            "Testing    ":
            "Extracting ",
            stdout);
        res = PrintString(temp);
        if (res != SZ_OK)
          break;
        
        if (isDir)
          printf("/");
        else
        {
          res = SzArEx_Extract(&db, &lookStream.s, i,
              &blockIndex, &outBuffer, &outBufferSize,
              &offset, &outSizeProcessed,
              &allocImp, &allocTempImp);
          if (res != SZ_OK)
            break;
        }
        
        if (!testCommand)
        {
          CSzFile outFile;
          size_t processedSize;
          size_t j;
          UInt16 *name = (UInt16 *)temp;
          const UInt16 *destPath = (const UInt16 *)name;
 
          for (j = 0; name[j] != 0; j++)
            if (name[j] == '/')
            {
              if (fullPaths)
              {
                name[j] = 0;
                MyCreateDir(name);
                name[j] = CHAR_PATH_SEPARATOR;
              }
              else
                destPath = name + j + 1;
            }
    
          if (isDir)
          {
            MyCreateDir(destPath);
            printf("\n");
            continue;
          }
          else if (OutFile_OpenUtf16(&outFile, destPath))
          {
            PrintError("can not open output file");
            res = SZ_ERROR_FAIL;
            break;
          }

          processedSize = outSizeProcessed;
          
          if (File_Write(&outFile, outBuffer + offset, &processedSize) != 0 || processedSize != outSizeProcessed)
          {
            PrintError("can not write output file");
            res = SZ_ERROR_FAIL;
            break;
          }
          
          if (File_Close(&outFile))
          {
            PrintError("can not close output file");
            res = SZ_ERROR_FAIL;
            break;
          }
          
          #ifdef USE_WINDOWS_FILE
          if (SzBitWithVals_Check(&db.Attribs, i))
            SetFileAttributesW(destPath, db.Attribs.Vals[i]);
          #endif
        }
        printf("\n");
      }
      IAlloc_Free(&allocImp, outBuffer);
    }
  }

  SzArEx_Free(&db, &allocImp);
  SzFree(NULL, temp);

  File_Close(&archiveStream.file);
  
  if (res == SZ_OK)
  {
    printf("\nEverything is Ok\n");
    return 0;
  }
  
  if (res == SZ_ERROR_UNSUPPORTED)
    PrintError("decoder doesn't support this archive");
  else if (res == SZ_ERROR_MEM)
    PrintError("can not allocate memory");
  else if (res == SZ_ERROR_CRC)
    PrintError("CRC error");
  else
    printf("\nERROR #%d\n", res);
  
  return 1;
}