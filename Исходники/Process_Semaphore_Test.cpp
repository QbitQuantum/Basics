int
run_main (int argc, ACE_TCHAR *argv[])
{
#if defined (ACE_LACKS_FORK)
  ACE_UNUSED_ARG (argc);
  ACE_UNUSED_ARG (argv);

  ACE_START_TEST (ACE_TEXT ("Process_Semaphore_Test"));
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("fork is not supported on this platform\n")));
  ACE_END_TEST;
#else

  parse_args (argc, argv);

  // Child process code.
  if (child_process)
    {
      ACE_START_TEST (ACE_TEXT ("Process_Semaphore_Test-child"));
      acquire_release ();
      ACE_END_LOG;
    }
  else
    {
      ACE_START_TEST (ACE_TEXT ("Process_Semaphore_Test"));

      ACE_TString exe_sub_dir;
      const char *subdir_env = ACE_OS::getenv ("ACE_EXE_SUB_DIR");
      if (subdir_env)
        {
          exe_sub_dir = ACE_TEXT_CHAR_TO_TCHAR (subdir_env);
          exe_sub_dir += ACE_DIRECTORY_SEPARATOR_STR;
        }

      ACE_Process_Options options;
      options.command_line (ACE_TEXT (".") ACE_DIRECTORY_SEPARATOR_STR
                            ACE_TEXT ("%sProcess_Semaphore_Test")
                            ACE_PLATFORM_EXE_SUFFIX
                            ACE_TEXT (" -c -i %d"),
                            exe_sub_dir.c_str(),
                            iterations);

      // Spawn a child process that will contend for the
      // lock.
      ACE_Process child;

      // Spawn the child process.
      int result = child.spawn (options);
      ACE_TEST_ASSERT (result != -1);
      ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("Parent spawned child process with pid = %d.\n"),
                child.getpid ()));

      // start test
      acquire_release ();

      ACE_exitcode child_status;
      // Wait for the child processes we created to exit.
      ACE_TEST_ASSERT (child.wait (&child_status) != -1);
      if (child_status == 0)
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("Child %d finished ok\n"),
                    child.getpid ()));
      else
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Child %d finished with status %d\n"),
                    child.getpid (), child_status));

      ACE_END_TEST;
    }
#endif /* ! ACE_LACKS_FORK */

  return 0;
}