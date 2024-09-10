int main(INT iArgc, PSZ Argv[])
{
APIRET rc;
ULONG ulDiskSize, ulDiskFree;
INT iArg;
INT iPartType;
PSZ pEnd;
PSZ p;

   for (iArg = 1; iArg < iArgc; iArg++)
      {
      strupr(Argv[iArg]);
      if (Argv[iArg][0] == '/')
         {
         switch (Argv[iArg][1])
            {
            case 'V':
               fDetailed = 1;
               if (Argv[iArg][2] == ':' && Argv[iArg][3] == '2')
                  fDetailed = 2;
               if (Argv[iArg][2] == ':' && Argv[iArg][3] == '3')
                  fDetailed = 3;
               if (Argv[iArg][2] == ':' && Argv[iArg][3] == '4')
                  fDetailed = 4;
               break;
            case 'B':
               fShowBootSector = TRUE;
               break;
            case 'P':
               p = &Argv[iArg][2];
               for (;;)
                  {
                  while (*p)
                     {
                     while (isspace(*p))
                        p++;
                     if (!(*p))
                        {
                        printf("ERROR: Expected partition types not found!\n");
                        exit(1);
                        break;
                        }
                     iPartType = strtol(p, &pEnd, 16);
                     if (iPartType > 255)
                        {
                        printf("ERROR: Partition type %X is not valid\n", iPartType);
                        exit(1);
                        }
                     printf("Also including partition types %2.2X.\n", iPartType);
                     rgfFakePart[iPartType] = TRUE;
//                     if (iPartType & PARTITION_HIDDEN)
//                        {
//                        printf("Also including partition types %2.2X.\n", iPartType & ~PARTITION_HIDDEN);
//                        rgfFakePart[iPartType & ~PARTITION_HIDDEN] = TRUE;
//                        }

                     p = pEnd;
                     while (isspace(*p)) p++;
                     if (*p != ',')
                        break;
                     p++;
                     }
                  if (iArg + 1 < iArgc && Argv[iArg+1][0] != '/')
                     {
                     iArg++;
                     p = Argv[iArg];
                     }
                  else
                     break;
                  }
               break;
            default :
               printf("Unknown option %s ignored.\n",
                  Argv[iArg]);
               break;
            }
         }
      else
         printf("Invalid argument %s ignored.\n", Argv[iArg]);
      }


   rc = InitProg();
   if (rc)
      return rc;

   if (usDriveCount > 0 && fDetailed > 2)
      {
      PDRIVEINFO pDrive = rgDrives;
      USHORT usDrive;
      for (usDrive = 0; usDrive < usDriveCount; usDrive++)
         {
         pDrive = &rgDrives[usDrive];
         printf("\n=== Directory structure of FAT32 DRIVE #%d===\n", pDrive->DiskNum);

         rc = OpenDisk(pDrive->DiskNum, &pDrive->hDisk);
         DumpDirectory(pDrive,
            pDrive->bpb.RootDirStrtClus, "X:");
         CheckSpace(pDrive);
#ifdef HENK
         ulDiskSize = DiskSize('F');
         ulDiskFree = DiskFree('F');
#endif


         printf("\n");
         printf("Found:\n");
         printf("Disk size       = %13lu\n", pDrive->ulTotalClusters);
         printf("In use          = %13ld\n", ulTotalClusters);
         printf("Free            = %13ld\n", ulTotalFree);
#ifdef HENK
         printf("Reported by DOS:\n");
         printf("Disk size       = %13lu\n", ulDiskSize / 4096);
         printf("In Use          = %13lu\n", (ulDiskSize - ulDiskFree)/4096);
         printf("Free            = %13lu\n", ulDiskFree / 4096);
         printf("Difference      = %13ld\n", (ulDiskSize - ulDiskFree)/4096 - ulTotalClusters);
#endif

         CloseDisk(pDrive->hDisk);
         pDrive->hDisk = 0;
         }
      }


   return 0;
}