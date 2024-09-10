static void
TestSuite_PrintJsonHeader (TestSuite *suite, /* IN */
                           FILE *stream)     /* IN */
{
#ifdef _WIN32
#  define INFO_BUFFER_SIZE 32767

   SYSTEM_INFO si;
   DWORD version = 0;
   DWORD major_version = 0;
   DWORD minor_version = 0;
   DWORD build = 0;

   GetSystemInfo(&si);
   version = GetVersion();

   major_version = (DWORD)(LOBYTE(LOWORD(version)));
   minor_version = (DWORD)(HIBYTE(LOWORD(version)));

   if (version < 0x80000000) {
      build = (DWORD)(HIWORD(version));
   }

   fprintf (stream,
            "{\n"
            "  \"host\": {\n"
            "    \"sysname\": \"Windows\",\n"
            "    \"release\": \"%ld.%ld (%ld)\",\n"
            "    \"machine\": \"%ld\",\n"
            "    \"memory\": {\n"
            "      \"pagesize\": %ld,\n"
            "      \"npages\": %d\n"
            "    }\n"
            "  },\n"
            "  \"options\": {\n"
            "    \"parallel\": \"%s\",\n"
            "    \"fork\": \"%s\"\n"
            "  },\n"
            "  \"tests\": [\n",
            major_version, minor_version, build,
            si.dwProcessorType,
            si.dwPageSize,
            0,
            (suite->flags & TEST_NOTHREADS) ? "false" : "true",
            (suite->flags & TEST_NOFORK) ? "false" : "true");
#else
   struct utsname u;
   uint64_t pagesize;
   uint64_t npages = 0;

   ASSERT (suite);

   if (uname (&u) == -1) {
      perror ("uname()");
      return;
   }

   pagesize = sysconf (_SC_PAGE_SIZE);

#  if defined(_SC_PHYS_PAGES)
   npages = sysconf (_SC_PHYS_PAGES);
#  endif

   fprintf (stream,
            "{\n"
            "  \"host\": {\n"
            "    \"sysname\": \"%s\",\n"
            "    \"release\": \"%s\",\n"
            "    \"machine\": \"%s\",\n"
            "    \"memory\": {\n"
            "      \"pagesize\": %"PRIu64",\n"
            "      \"npages\": %"PRIu64"\n"
            "    }\n"
            "  },\n"
            "  \"options\": {\n"
            "    \"parallel\": \"%s\",\n"
            "    \"fork\": \"%s\"\n"
            "  },\n"
            "  \"tests\": [\n",
            u.sysname,
            u.release,
            u.machine,
            pagesize,
            npages,
            (suite->flags & TEST_NOTHREADS) ? "false" : "true",
            (suite->flags & TEST_NOFORK) ? "false" : "true");
#endif

   fflush (stream);
}