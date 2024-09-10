int execute(const char *filename, char * argv[], char *env[])
{
    intptr_t i;
	i=_spawnvpe(_P_WAIT, filename, argv, env);

	return i;
}