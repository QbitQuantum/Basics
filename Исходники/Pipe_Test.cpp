int
run_main (int argc, ACE_TCHAR *argv[])
{
    parse_args (argc, argv);

    if (child_process)
    {
        ACE_APPEND_LOG (ACE_TEXT("Pipe_Test-children"));
        ACE_Pipe a, b, c, d, e;

        open_pipe (a, "a");
        open_pipe (b, "b");
        open_pipe (c, "c");
        open_pipe (d, "d");
        open_pipe (e, "e");

        ACE_END_LOG;
    }
    else
    {
        ACE_START_TEST (ACE_TEXT("Pipe_Test"));
        ACE_INIT_LOG (ACE_TEXT("Pipe_Test-children"));

#  if defined (ACE_WIN32) || !defined (ACE_USES_WCHAR)
        const ACE_TCHAR *cmdline_fmt = ACE_TEXT ("%s -c%s");
#  else
        const ACE_TCHAR *cmdline_fmt = ACE_TEXT ("%ls -c%ls");
#  endif /* ACE_WIN32 || !ACE_USES_WCHAR */
        ACE_Process_Options options;
        options.command_line (cmdline_fmt,
                              argc > 0 ? argv[0] : ACE_TEXT ("Pipe_Test"),
                              close_pipe == 0 ? ACE_TEXT (" -d") : ACE_TEXT (""));

        ACE_exitcode status = 0;

        for (int i = 0; i < ::iterations; i++)
        {
            ACE_Process server;

            if (server.spawn (options) == -1)
            {
                ACE_ERROR_RETURN ((LM_ERROR,
                                   ACE_TEXT ("%p\n"),
                                   ACE_TEXT ("spawn failed")),
                                  -1);
            }
            else
            {
                ACE_DEBUG ((LM_DEBUG,
                            ACE_TEXT ("Server forked with pid = %d.\n"),
                            server.getpid ()));
            }

            // Wait for the process we just created to exit.
            server.wait (&status);

            // Check if child exited without error.
            if (WIFEXITED (status) != 0
                    && WEXITSTATUS (status) != 0)
            {
                ACE_ERROR ((LM_ERROR,
                            ACE_TEXT ("Child of server %d finished with error ")
                            ACE_TEXT ("exit status %d\n"),
                            server.getpid (),
                            WEXITSTATUS (status)));

                ACE_END_TEST;

                ACE_OS::exit (WEXITSTATUS (status));
            }

            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Server %d finished\n"),
                        server.getpid ()));
        }
        ACE_END_TEST;
    }

    return 0;
}