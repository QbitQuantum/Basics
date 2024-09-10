static void restart_revolution(void)
{
#if defined(TARGET_PLATFORM_WINDOWS)
	_spawnl(_P_NOWAIT, s_command_path, s_command_path, NULL);
#elif defined(TARGET_PLATFORM_MACOS_X)
	if (fork() == 0)
	{
		usleep(250000);
		execl(MCcmd, MCcmd, NULL);
	}
#elif defined(TARGET_PLATFORM_LINUX)
	if (fork() == 0)
	{
		usleep(250000);
		execl(MCcmd, MCcmd, NULL);
	}
#else
#error restart not defined
#endif
}