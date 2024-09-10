// IDL compiler main program. Logic as explained in comment at head of file.
int driver_main(int argc, char **argv)
{
    int ret = 0;

#if defined (_WIN32)
    char * cmdstr = DRV_param_copy (argc, argv);
#endif

    // Open front-end library
    DRV_FE_open ();

    // Initialize driver and global variables
    {
        DRV_init ();
    }

    // Open back-end library
    DRV_BE_open ();

    // Parse arguments
    DRV_parse_args (argc, argv);

    // If a version message is requested, print it and exit
    if (idl_global->compile_flags () & IDL_CF_VERSION)
    {
        DRV_version ();
    }
    else
    {
        // If a usage message is requested, give it and exit
        if (idl_global->compile_flags () & IDL_CF_ONLY_USAGE)
        {
            DRV_usage ();
        }
        else
        {
            // Fork off a process for each file to process. Fork only if
            // there is more than one file to process
            if (DRV_nfiles > 1)
            {
                // DRV_fork never returns
#if !defined (_WIN32)
                DRV_fork ();
#else

                char tmp_command[1024];

                for (int tmpcounter = 0; tmpcounter < DRV_nfiles; tmpcounter++)
                {
                    os_sprintf(tmp_command, "%s %s\0", cmdstr, DRV_files[tmpcounter]);

                    _flushall ();

                    if (system (tmp_command))
                    {
                        cerr << "system() failed, errno: " << errno << endl;
                    }
                }
#endif
            }
            else
            {
                // Do the one file we have to parse
                // Check if stdin and handle file name appropriately
                if (DRV_nfiles == 0)
                {
                    DRV_files[0] = "standard input";
                }

                DRV_file_index = 0;
                ret = DRV_drive (DRV_files[DRV_file_index]);
            }
        }
    }

    return ret;
}