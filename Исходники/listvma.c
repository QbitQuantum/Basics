int
main (int argc, char** argv)
{
  MEMORY_BASIC_INFORMATION mbi;
  char* region = 0;
  const char* type;
  wchar_t namebuf[4096];
  DWORD winpid = (argv[1] ? atoi (argv[1]) : GetCurrentProcessId ());
  HANDLE proc = OpenProcess (PROCESS_ALL_ACCESS, FALSE, winpid);

  if (!proc)
    {
      fprintf (stderr, "OpenProcess(%lu): 0x%lx\n",
               winpid, GetLastError ());
      return 1;
    }
               

  var_in_data = 43;
    
  for (;; region += mbi.RegionSize)
    {
      if (!VirtualQueryEx (proc, region, &mbi, sizeof (mbi)))
        {
          if (GetLastError () != ERROR_INVALID_PARAMETER)
            fprintf (stderr, "VirtualQuery: 0x%lx\n", GetLastError ());
          
          break;
        }

      if (mbi.State == MEM_FREE)
        continue;

#if 0
      if (mbi.Type == MEM_IMAGE)
        continue;
#endif

      if (mbi.State == MEM_FREE)
        type = "free";
      else if (mbi.Type == MEM_IMAGE)
        type = "image";
      else if (mbi.Type == MEM_MAPPED)
        type = "mapped";
      else if (mbi.Type == MEM_PRIVATE)
        type = "private";
      else
        type = "unknown";

      printf ("0x%08lx %-9s %010lu %-8s %s\n",
              (unsigned long) region,
              mbi.State == MEM_COMMIT ? "commit" : "reserved",
              mbi.RegionSize,
              type,
              describe_protection (mbi.Protect)
              );

      if (winpid == GetCurrentProcessId ())
        {
          if (region <= (char*) &var_in_bss &&
              (char*) &var_in_bss < (region + mbi.RegionSize))
            {
              printf (" ^^^^ BSS\n");
            }

          if (region <= (char*) &var_in_data &&
              (char*) &var_in_data < (region + mbi.RegionSize))
            {
              printf (" ^^^^ DATA\n");
            }

          if (mbi.Type == MEM_MAPPED)
            {
              namebuf[0] = L'\0';
              wcscpy (namebuf, L"[unknown]");
              GetMappedFileNameW (GetCurrentProcess (),
                                  region,
                                  &namebuf[0],
                                  countof (namebuf));
              printf (" ^^^^ - %S\n", namebuf);
            }
        }
    }
}