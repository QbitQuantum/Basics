int spawnlpe(int mode, const char *file, const char *arg0, ...) {
	char	**argv;
	char	**envv;

	CVT_L2V_ENV(arg0, argv, envv);
	return spawnvpe(mode, file, argv, envv);
}