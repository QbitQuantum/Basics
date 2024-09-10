intptr_t SystemCall(char *command)
{
    intptr_t rc;
    char    *argv[6];

    argv[0] = getenv("COMSPEC");
    argv[1] = "/q";
    argv[2] = "/c";
    argv[3] = (char *)command;
    argv[4] = NULL;

    rc = spawnve(_P_WAIT,argv[0],argv,NULL);
// != -1 || (errno != ENOENT && errno != EACCES))
    return(rc);
}