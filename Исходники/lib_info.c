/*
 * public static String GetGlobalConfigDir();
 */
extern ILString *_IL_InfoMethods_GetGlobalConfigDir(ILExecThread *_thread)
{
#if !defined(__palmos__)
	char *env;
	ILString *str;

	/* Try the "CLI_MACHINE_CONFIG_DIR" environment variable first */
	if((env = getenv("CLI_MACHINE_CONFIG_DIR")) != 0 && *env != '\0')
	{
		return ILStringCreate(_thread, env);
	}

	/* Return a standard path such as "/usr/local/share/cscc/config" */
	env = ILGetStandardDataPath("cscc/config");
	if(!env)
	{
		ILExecThreadThrowOutOfMemory(_thread);
		return 0;
	}
	str = ILStringCreate(_thread, env);
	ILFree(env);
	return str;
#else
	return 0;
#endif
}