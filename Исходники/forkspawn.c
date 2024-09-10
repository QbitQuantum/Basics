int Spawnvp(PCStr(what),PCStr(path),const char *const av[])
{   int pid;

    if( DontFork ) {
        return -1;
    }
    SpawnWhat = what;
    MyPID = 0;
    pid = spawnvp(SPAWN_P_NOWAIT,path,av);
    return pid;
}