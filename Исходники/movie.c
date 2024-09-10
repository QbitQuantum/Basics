void executeCommand(const char* cmd)
{
    if(!cmd || !*cmd)
        return;

    const char *argv[4];
    argv[0] = getenv("COMSPEC");
    argv[1] = "/c";
    argv[2] = cmd;
    argv[3] = NULL;
    if(*argv && *(*argv))
        _spawnve(_P_WAIT, argv[0], argv, NULL);
}