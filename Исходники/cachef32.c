VOID InitProg(INT iArgc, PSZ rgArgv[])
{
APIRET    rc;
BYTE      szTranslate[256];
INT       iArg;
ULONG     ulLVB;
USHORT    uscbLVB;
ULONG     ulDataSize;
ULONG     ulParmSize;
BOOL      fSetParms = FALSE;
ULONG     ulParm;


   memset(szTranslate, 0, sizeof szTranslate);

   /*
      Determine if we run in the foreground
   */
   rc = VioGetBuf(&ulLVB, &uscbLVB, (HVIO)0);
   if (rc)
      fForeGround = FALSE;
   else
      fForeGround = TRUE;

   if (fForeGround)
      printf("FAT32 cache helper version %s.\n", FAT32_VERSION);
   else
      WriteLogMessage("FAT32 task detached");

   rc = DosGetNamedSharedMem((PVOID *)&pOptions, SHAREMEM, PAG_READ|PAG_WRITE);
   if (!rc)
      {
      fActive = TRUE;
      WriteLogMessage("Shared memory found!");
      }
   else
      {
      rc = DosAllocSharedMem((PVOID *)&pOptions, SHAREMEM, sizeof (LWOPTS), PAG_COMMIT|PAG_READ|PAG_WRITE);
      if (rc)
         DosExit(EXIT_PROCESS, 1);
      memset(pOptions, 0, sizeof pOptions);
      pOptions->bLWPrio = PRTYC_IDLETIME;
      WriteLogMessage("Shared memory allocated!");
      }

   ulDataSize = sizeof f32Parms;
   rc = DosFSCtl(
      (PVOID)&f32Parms, ulDataSize, &ulDataSize,
      NULL, 0, &ulParmSize,
      FAT32_GETPARMS, "FAT32", -1, FSCTL_FSDNAME);
   if (rc)
      {
      printf("DosFSCtl, FAT32_GETPARMS failed, rc = %d\n", rc);
      DosExit(EXIT_PROCESS, 1);
      }
   if (strcmp(f32Parms.szVersion, FAT32_VERSION))
      {
      printf("ERROR: FAT32 version (%s) differs from CACHEF32 version (%s)\n", f32Parms.szVersion, FAT32_VERSION);
      DosExit(EXIT_PROCESS, 1);
      }

   for (iArg = 1; iArg < iArgc; iArg++)
      {
      strupr(rgArgv[iArg]);
      if (rgArgv[iArg][0] == '/' || rgArgv[iArg][0] == '-')
         {
         switch (rgArgv[iArg][1])
            {
            case '?' :
               printf("USAGE: CACHEF32 [options]\n");
               printf("/Q (Quit)\n");
               printf("/N do NOT load lazy write deamon.\n");
               printf("/D:diskidle in millisecs.\n");
               printf("/B:bufferidle in millisecs.\n");
               printf("/M:maxage in millisecs.\n");
               printf("/R:d:,n sets read ahead sector count for drive d: to n.\n");
               printf("/FS use short file names internally.\n");
               printf("/FL use long file names internally.\n");
               printf("/L:on|off set lazy writing on or off.\n");
               printf("/P:1|2|3|4 Set priority of Lazy writer\n");
               DosExit(EXIT_PROCESS, 0);
               break;

            case 'P':
               if (rgArgv[iArg][2] != ':')
                  {
                  printf("Missing : after /P\n");
                  DosExit(EXIT_PROCESS, 1);
                  }
               if (rgArgv[iArg][3] < '1' ||
                   rgArgv[iArg][3] > '4')
                  {
                  printf("Lazy write priority should be from 1 to 4!\n");
                  DosExit(EXIT_PROCESS, 1);
                  }
               pOptions->bLWPrio = rgArgv[iArg][3] - '0';
               break;


            case 'N':
               fLoadDeamon = FALSE;
               break;

            case 'T':
               printf("The /T option is no longer supported.\n");
               printf("Please read the documentation.\n");
               break;

            case 'Q' :
               if (fActive)
                  {
                  if (pOptions->fTerminate)
                     printf("Terminate request already set!\n");
                  pOptions->fTerminate = TRUE;
                  printf("Terminating CACHEF32.EXE...\n");
                  DosExit(EXIT_PROCESS, 0);
                  }
               printf("/Q is invalid, CACHEF32 is not running!\n");
               DosExit(EXIT_PROCESS, 1);
               break;
            case 'D':
               if (rgArgv[iArg][2] != ':')
                  {
                  printf("ERROR: missing : in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               ulParm = atol(&rgArgv[iArg][3]);
               if (!ulParm)
                  {
                  printf("ERROR: Invalid value in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               f32Parms.ulDiskIdle = ulParm / TIME_FACTOR;
               fSetParms = TRUE;
               break;

            case 'B':
               if (rgArgv[iArg][2] != ':')
                  {
                  printf("ERROR: missing : in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               ulParm = atol(&rgArgv[iArg][3]);
               if (!ulParm)
                  {
                  printf("ERROR: Invalid value in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               f32Parms.ulBufferIdle = ulParm / TIME_FACTOR;
               fSetParms = TRUE;
               break;

            case 'M':
               if (rgArgv[iArg][2] != ':')
                  {
                  printf("ERROR: missing : in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               ulParm = atol(&rgArgv[iArg][3]);
               if (!ulParm)
                  {
                  printf("ERROR: Invalid value in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               f32Parms.ulMaxAge = ulParm / TIME_FACTOR;
               fSetParms = TRUE;
               break;

            case 'R':
               if (rgArgv[iArg][2] != ':')
                  {
                  printf("ERROR: missing : in %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               SetRASectors(&rgArgv[iArg][3]);
               break;
            case 'F':
               if (rgArgv[iArg][2] == 'S')
                  f32Parms.fUseShortNames = TRUE;
               else if (rgArgv[iArg][2] == 'L')
                  f32Parms.fUseShortNames = FALSE;
               else
                  {
                  printf("ERROR: Unknown option %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               fSetParms = TRUE;
               break;

            case 'L':
               if (!stricmp(&rgArgv[iArg][2], ":ON"))
                  {
                  rc = DosFSCtl(NULL, 0, NULL,
                              NULL, 0, NULL,
                     FAT32_STARTLW, "FAT32", -1, FSCTL_FSDNAME);
                  if (rc)
                     printf("Warning: Lazy writing is already active or cachesize is 0!\n");
                  }
               else if (!stricmp(&rgArgv[iArg][2], ":OFF"))
                  {
                  rc = DosFSCtl(NULL, 0, NULL,
                              NULL, 0, NULL,
                     FAT32_STOPLW, "FAT32", -1, FSCTL_FSDNAME);
                  if (rc)
                     printf("Warning: Lazy writing is not active!\n");
                  }
               else
                  {
                  printf("ERROR: Unknown option %s\n", rgArgv[iArg]);
                  DosExit(EXIT_PROCESS, 1);
                  }
               break;

            default :
               printf("ERROR: Unknown option %s\n", rgArgv[iArg]);
               DosExit(EXIT_PROCESS, 1);
               break;
            }

         }
      }

   if (LoadTranslateTable())
      fSetParms = TRUE;

   if (fSetParms)
      {
      if (f32Parms.ulDiskIdle < f32Parms.ulBufferIdle)
         {
         printf("DISKIDLE must be greater than BUFFERIDLE\n");
         DosExit(EXIT_PROCESS, 1);
         }

      ulParmSize = sizeof f32Parms;
      rc = DosFSCtl(
         NULL, 0, &ulDataSize,
         (PVOID)&f32Parms, ulParmSize, &ulParmSize,
         FAT32_SETPARMS, "FAT32", -1, FSCTL_FSDNAME);
      if (rc)
         {
         printf("DosFSCtl FAT32_SETPARMS, failed, rc = %d\n", rc);
         DosExit(EXIT_PROCESS, 1);
         }
      }

   ulDriveMap = GetFAT32Drives();
   if (!fActive)
      {
      if (!ulDriveMap)
         {
         printf("FAT32: No FAT32 partitions found, aborting...\n");
         DosExit(EXIT_PROCESS, 1);
         }
      }



   /*
      Query parms
   */

   if (fActive || !f32Parms.usCacheSize)
      {
      if (fActive)
         {
         printf("CACHEF32 is already running.\n");
         printf("Current priority is %s.\n", rgPriority[pOptions->bLWPrio]);
         }

      if (!f32Parms.fLW)
         printf("LAZY WRITING is NOT active!\n\n");
      else
         {
         printf("\n");
         printf("DISKIDLE  : %lu milliseconds.\n", f32Parms.ulDiskIdle * TIME_FACTOR);
         printf("BUFFERIDLE: %lu milliseconds.\n", f32Parms.ulBufferIdle * TIME_FACTOR);
         printf("MAXAGE    : %lu milliseconds.\n", f32Parms.ulMaxAge * TIME_FACTOR);
         }

      printf("\n");
      ShowRASectors();
      printf("\n");
      printf("CACHE has space for %u sectors\n", f32Parms.usCacheSize);
      printf("CACHE contains %u sectors\n", f32Parms.usCacheUsed);
      printf("There are %u dirty sectors in cache.\n", f32Parms.usDirtySectors);
      if (f32Parms.usPendingFlush > 0)
         printf("%u sectors are in pending flush state.\n", f32Parms.usPendingFlush);
      printf("The cache hits ratio is %3d%%.\n",
         f32Parms.ulTotalHits * 100 / f32Parms.ulTotalReads);
      if (f32Parms.fUseShortNames)
         {
         printf("Internally, short names are used.\n");
         printf("All files are visible in DOS sessions.\n");
         }
      else
         {
         printf("Internally, long names are used.\n");
         printf("Files and directories with long names are hidden for DOS.\n");
         }
      printf("FAT32.IFS has currently %u GDT segments allocated.\n",
         f32Parms.usSegmentsAllocated);
      }

   return;
}