int
run_main (int argc, ACE_TCHAR *argv[])
{
#if defined (ACE_WIN32)
  get_base_addrs();
#endif

  if (argc == 1)
    {
      ACE_START_TEST (ACE_TEXT ("Malloc_Test"));
      ACE_INIT_LOG (ACE_TEXT ("Malloc_Test-child"));

      init_test (PARENT_BASE_ADDR);

      ACE_Control_Block::print_alignment_info ();
# if (ACE_HAS_POSITION_INDEPENDENT_POINTERS == 1)
      ACE_PI_Control_Block::print_alignment_info ();
# endif /* ACE_HAS_POSITION_INDEPENDENT_POINTERS == 1 */

      // No arguments means we're the parent process.
      ACE_Process_Options options (1);

#if !defined (ACE_WIN32) && defined (ACE_USES_WCHAR)
      static const ACE_TCHAR* format = ACE_TEXT ("%ls%ls%ls");
#else
      static const ACE_TCHAR* format = ACE_TEXT ("%s%s%s");
#endif /* !ACE_WIN32 && ACE_USES_WCHAR */
      options.command_line (format, EXE_LOCATION,
                            argc > 0 ? argv[0] : ACE_TEXT ("Malloc_Test"),
                            ACE_TEXT (" run_as_test"));

      MALLOC *myalloc = myallocator (PARENT_BASE_ADDR);

      Test_Data *data = initialize (myalloc);
      ACE_TEST_ASSERT (data != 0);

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%P) PARENT allocator at = %@, ")
                  ACE_TEXT ("data allocated at %@\n"),
                  myalloc,
                  data));
      myalloc->dump ();
      int result = myalloc->bind ("foo", data);
      ACE_TEST_ASSERT (result != -1);

      ACE_Process p;
      pid_t pid = p.spawn (options);
      if (pid == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%p\n"),
                           ACE_TEXT ("spawn")), 1);

      parent (data);

      // Synchronize on the exit of the child.
      result = p.wait ();
      if (result == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%p\n"),
                           ACE_TEXT ("wait")), 1);
      ACE_TEST_ASSERT (myalloc->ref_counter () == 1);
      myalloc->remove ();
      ACE_END_TEST;
      return 0;
    }
  else
    {
      // In this case we're the child process.
      ACE_APPEND_LOG (ACE_TEXT ("Malloc_Test-child"));

      void *data = 0;
      MALLOC *myalloc = myallocator (CHILD_BASE_ADDR);
      int result = myalloc->find ("foo", data);
      ACE_TEST_ASSERT (result != -1);

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%P) CHILD allocator at = %@, ")
                  ACE_TEXT ("data allocated at %@\n"),
                  myalloc,
                  data));
      myalloc->dump ();
      child ();
      myalloc->release ();
      ACE_END_LOG;
      return 0;
    }
}