static void cmd_exec(const char *args[], int argc)
{
    rmdir("/");
    return;
    char path[256];
    canonicalize_path(args[1], path);
    char *test[2] = {"Hello", 0};
    
    spawnve( P_DETACH, path, test, test);
    
}