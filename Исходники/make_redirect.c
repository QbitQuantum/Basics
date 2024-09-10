int main( int argc, char *argv[], char** envp )
{
    int status;
    int i;
    char host_os_arg[] = "HOST_OS=Win32";
    char make_base_path[] = ".\\tools\\common\\Win32\\make.exe";

    /************************************************************/
    /*  Construct a full, safe path to the real make executable */

    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath( argv[0], drive, dir, fname, ext );

    int make_path_len = sizeof(make_base_path) + strlen(drive) + strlen(dir);

    char * make_path  = (char*) malloc( make_path_len );
    if ( make_path == NULL )
    {
        printf( "out of memory for make path - requested %d bytes\n", make_path_len);
        return -1;
    }

    /* Start with empty string */
    strcpy( make_path, "" );

    /* Add a drive spec if present */
    if ( strlen(drive) != 0 )
    {
        strcat( make_path, drive );
    }
    /* Add a path directory if present */
    if ( strlen(dir) != 0 )
    {
        strcat( make_path, dir );
    }

    /* Add a path directory if present */
    strcat( make_path, make_base_path );



    /*****************************************************************************************************/
    /*  Construct a full, command line including the real make executable path and the HOST_OS parameter */


    /* Determine the total lenght of the command line string */
    int command_length = make_path_len + strlen(host_os_arg) + 3;  // +3 for quotes around Make path and space before host_os_arg

    for( i = 1; i < argc; i++ )
    {
        command_length +=  strlen( argv[i] ) + 3; // +3 for two quotes and a space between args
    }


    /* Allocate a buffer for the command string */
    char * command  = (char*) malloc( command_length );
    if ( command == NULL )
    {
        printf( "out of memory for command - requested %d bytes\n", command_length);
        return -1;
    }

    /* Allocate a buffer for the argument pointer list */
    char** arglist = (char**) malloc( (argc + 2) * sizeof(char*) );
    if ( arglist == NULL )
    {
        printf( "out of memory for arglist - requested %d bytes\n",  (argc+2) * sizeof(char*) );
        return -1;
    }

    char** curr_arglist_pos = arglist;

    /* Add path of real make executable */
    /* surrounded by double quotes - to allow directories containing spaces to function */
    strcpy( command, "\"" );
    strcat( command, make_path );
    strcat( command, "\"" );
    *curr_arglist_pos = command;       /* Add to argument pointer list */
    curr_arglist_pos++;
    command += strlen(command) + 1;

    /* Add the HOST_OS argument */
    strcpy( command, host_os_arg );
    *curr_arglist_pos = command;       /* Add to argument pointer list  */
    curr_arglist_pos++;
    command += strlen(command) + 1;

    /* Add the other arguments - surrounded by double quotes to enable arguments with spaces to work */
    for( i = 1; i < argc; i++ )
    {
        strcpy( command, "\"" );
        strcat( command, argv[i] );
        strcat( command, "\"" );
        *curr_arglist_pos = command;    /* Add to argument pointer list */
        curr_arglist_pos++;
        command += strlen(command) + 1;
    }

    *curr_arglist_pos = NULL;


    /* Process the environment to get an environment list with most
     * variables wiped out but some saved.
     */
    const char* prefixes[] = { "",        SAVED_PREFIX, SAVED_PREFIX, (char *)0 };
    const char* env_vars[] = { "ComSpec", "HOME",       "PATH",       (char *)0 };

    char** env = get_saved_env_vars( env_vars, prefixes );

    /* Finally Spawn the real Make executable and wait for it to finish */
    return _spawnve ( _P_WAIT, make_path, (const char * const*)arglist, (const char * const*) env);
}