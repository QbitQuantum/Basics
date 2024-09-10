void
init_heap (void)
{
  if (using_dynamic_heap)
    {
      unsigned long enable_lfh = 2;

      /* After dumping, use a new private heap.  We explicitly enable
         the low fragmentation heap (LFH) here, for the sake of pre
         Vista versions.  Note: this will harmlessly fail on Vista and
         later, where the low-fragmentation heap is enabled by
         default.  It will also fail on pre-Vista versions when Emacs
         is run under a debugger; set _NO_DEBUG_HEAP=1 in the
         environment before starting GDB to get low fragmentation heap
         on XP and older systems, for the price of losing "certain
         heap debug options"; for the details see
         http://msdn.microsoft.com/en-us/library/windows/desktop/aa366705%28v=vs.85%29.aspx.  */
      data_region_end = data_region_base;

      /* Create the private heap.  */
      heap = HeapCreate (0, 0, 0);

#ifndef MINGW_W64
      /* Set the low-fragmentation heap for OS before Vista.  */
      HMODULE hm_kernel32dll = LoadLibrary ("kernel32.dll");
      HeapSetInformation_Proc s_pfn_Heap_Set_Information = (HeapSetInformation_Proc) GetProcAddress (hm_kernel32dll, "HeapSetInformation");
      if (s_pfn_Heap_Set_Information != NULL)
	{
	  if (s_pfn_Heap_Set_Information ((PVOID) heap,
					  HeapCompatibilityInformation,
					  &enable_lfh, sizeof(enable_lfh)) == 0)
	    DebPrint (("Enabling Low Fragmentation Heap failed: error %ld\n",
		       GetLastError ()));
	}
#endif

      if (os_subtype == OS_9X)
        {
          the_malloc_fn = malloc_after_dump_9x;
          the_realloc_fn = realloc_after_dump_9x;
          the_free_fn = free_after_dump_9x;
        }
      else
        {
          the_malloc_fn = malloc_after_dump;
          the_realloc_fn = realloc_after_dump;
          the_free_fn = free_after_dump;
        }
    }
  else
    {
      /* Find the RtlCreateHeap function.  Headers for this function
         are provided with the w32 DDK, but the function is available
         in ntdll.dll since XP.  */
      HMODULE hm_ntdll = LoadLibrary ("ntdll.dll");
      RtlCreateHeap_Proc s_pfn_Rtl_Create_Heap
	= (RtlCreateHeap_Proc) GetProcAddress (hm_ntdll, "RtlCreateHeap");
      /* Specific parameters for the private heap.  */
      RTL_HEAP_PARAMETERS params;
      ZeroMemory (&params, sizeof(params));
      params.Length = sizeof(RTL_HEAP_PARAMETERS);

      data_region_base = (unsigned char *)ROUND_UP (dumped_data, 0x1000);
      data_region_end = bc_limit = dumped_data + DUMPED_HEAP_SIZE;

      params.InitialCommit = committed = 0x1000;
      params.InitialReserve = sizeof(dumped_data);
      /* Use our own routine to commit memory from the dumped_data
         array.  */
      params.CommitRoutine = &dumped_data_commit;

      /* Create the private heap.  */
      if (s_pfn_Rtl_Create_Heap == NULL)
	{
	  fprintf (stderr, "Cannot build Emacs without RtlCreateHeap being available; exiting.\n");
	  exit (-1);
	}
      heap = s_pfn_Rtl_Create_Heap (0, data_region_base, 0, 0, NULL, &params);

      if (os_subtype == OS_9X)
        {
          fprintf (stderr, "Cannot dump Emacs on Windows 9X; exiting.\n");
          exit (-1);
        }
      else
        {
          the_malloc_fn = malloc_before_dump;
          the_realloc_fn = realloc_before_dump;
          the_free_fn = free_before_dump;
        }
    }

  /* Update system version information to match current system.  */
  cache_system_info ();
}