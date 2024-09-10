int
main(int argc, char **argv) 
{
    char **new_argv;
    int k, code;
    new_argv = xmalloc( (argc+2) * sizeof (char *) );
    new_argv[0] = add_to_file_dir("","\\@PROG@");
    new_argv[1] = "@ARGV1@";
    for (k=1; k < argc; k++) new_argv[k+1] = argv[k];
    new_argv[argc+1] = NULL;
    new_argv = prepare_spawn (new_argv);
    code = _spawnv(_P_WAIT, new_argv[0] , (const char **) new_argv );
    if (code == -1) {
        perror("@ARGV1@: Cannot exec @PROG@");
        exit(127);
    }
    else exit(code);
}