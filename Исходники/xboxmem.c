VOID
XboxMemInit(VOID)
{
  UCHAR ControlRegion[TEST_SIZE];
  PVOID MembaseTop = (PVOID)(64 * 1024 * 1024);
  PVOID MembaseLow = (PVOID)0;

  (*(PULONG)(0xfd000000 + 0x100200)) = 0x03070103 ;
  (*(PULONG)(0xfd000000 + 0x100204)) = 0x11448000 ;

  WRITE_PORT_ULONG((ULONG*) 0xcf8, CONFIG_CMD(0, 0, 0x84));
  WRITE_PORT_ULONG((ULONG*) 0xcfc, 0x7ffffff);             /* Prep hardware for 128 Mb */

  InstalledMemoryMb = 64;
  memset(ControlRegion, TEST_PATTERN1, TEST_SIZE);
  memset(MembaseTop, TEST_PATTERN1, TEST_SIZE);
  __wbinvd();

  if (0 == memcmp(MembaseTop, ControlRegion, TEST_SIZE))
    {
      /* Looks like there is memory .. maybe a 128MB box */
      memset(ControlRegion, TEST_PATTERN2, TEST_SIZE);
      memset(MembaseTop, TEST_PATTERN2, TEST_SIZE);
      __wbinvd();
      if (0 == memcmp(MembaseTop, ControlRegion, TEST_SIZE))
        {
          /* Definitely looks like there is memory */
          if (0 == memcmp(MembaseLow, ControlRegion, TEST_SIZE))
            {
              /* Hell, we find the Test-string at 0x0 too ! */
              InstalledMemoryMb = 64;
            }
          else
            {
              InstalledMemoryMb = 128;
            }
        }
    }

  /* Set hardware for amount of memory detected */
  WRITE_PORT_ULONG((ULONG*) 0xcf8, CONFIG_CMD(0, 0, 0x84));
  WRITE_PORT_ULONG((ULONG*) 0xcfc, InstalledMemoryMb * 1024 * 1024 - 1);

  AvailableMemoryMb = InstalledMemoryMb;
}