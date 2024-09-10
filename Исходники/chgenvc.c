int chgEnvCase(const int keepCase, char var[], const char value[])
{
	assert(var);

	if(!keepCase && (env_matchVar(0, var) & 7) != 0)
	/* no match --> upcase variable */
		StrUpr(var);

	return chgEnv(var, value);
}