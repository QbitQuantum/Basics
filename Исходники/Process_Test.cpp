void
run_parent (bool inherit_files)
{
  ACE_TCHAR t[] = ACE_TEXT ("ace_testXXXXXX");

  // Create tempfile. This will be tested for inheritance.
  ACE_TCHAR tempfile[MAXPATHLEN + 1];

  if (ACE::get_temp_dir (tempfile, MAXPATHLEN - sizeof (t)) == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("Could not get temp dir\n")));

  ACE_OS::strcat (tempfile, t);

  ACE_HANDLE file_handle = ACE_OS::mkstemp (tempfile);
  if (file_handle == ACE_INVALID_HANDLE)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("Could not get temp filename\n")));

  // Build child options
  ACE_TString exe_sub_dir;
  const char *subdir_env = ACE_OS::getenv ("ACE_EXE_SUB_DIR");
  if (subdir_env)
    {
      exe_sub_dir = ACE_TEXT_CHAR_TO_TCHAR (subdir_env);
      exe_sub_dir += ACE_DIRECTORY_SEPARATOR_STR;
    }

  ACE_Process_Options options;
  options.command_line (ACE_TEXT (".") ACE_DIRECTORY_SEPARATOR_STR
                        ACE_TEXT ("%sProcess_Test")
                        ACE_PLATFORM_EXE_SUFFIX
                        ACE_TEXT (" -c -h %d -f %s"),
                        exe_sub_dir.c_str(),
                        (int)inherit_files,
                        tempfile);
  options.handle_inheritance (inherit_files); /* ! */

  // Spawn child
  ACE_Process child;

  pid_t result = child.spawn (options);
  if (result == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("Parent could NOT spawn child process\n")));
  else
    ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Parent spawned child process with pid = %d.\n"),
              child.getpid ()));

  ACE_exitcode child_status;
  result = child.wait (&child_status);
  if (result == -1)
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("Could NOT wait on child process\n")));
  else if (child_status == 0)
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("Child %d finished ok\n"),
                child.getpid ()));
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("Child %d finished with status %d\n"),
                child.getpid (), child_status));
}