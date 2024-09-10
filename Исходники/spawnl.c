int spawnl(int mode, const char *path, const char *arg0, ...) {
    char		**argv;

    CVT_L2V(arg0, argv);
    return spawnve(mode, path, argv, 0);
}