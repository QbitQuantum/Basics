/******************************************************************************
 *                                                                            *
 * Function: zbx_free_service_resources                                       *
 *                                                                            *
 * Purpose: free service resources allocated by main thread                   *
 *                                                                            *
 ******************************************************************************/
void	zbx_free_service_resources(void)
{
	if (NULL != threads)
	{
		int		i;
#if !defined(_WINDOWS)
		sigset_t	set;

		/* ignore SIGCHLD signals in order for zbx_sleep() to work */
		sigemptyset(&set);
		sigaddset(&set, SIGCHLD);
		sigprocmask(SIG_BLOCK, &set, NULL);
#else
		/* wait for threads to finish first. although listener threads will never end */
		WaitForMultipleObjectsEx(threads_num, threads, TRUE, 1000, FALSE);
#endif
		for (i = 0; i < threads_num; i++)
		{
			if (threads[i])
				zbx_thread_kill(threads[i]);
		}

		for (i = 0; i < threads_num; i++)
		{
			if (threads[i])
				zbx_thread_wait(threads[i]);

			threads[i] = ZBX_THREAD_HANDLE_NULL;
		}

		zbx_free(threads);
	}

	zabbix_log(LOG_LEVEL_INFORMATION, "Zabbix Agent stopped. Zabbix %s (revision %s).",
			ZABBIX_VERSION, ZABBIX_REVISION);

#ifndef _WINDOWS
	unload_modules();
#endif
	zabbix_close_log();

	free_metrics();
	alias_list_free();
	free_collector_data();
#ifdef _WINDOWS
	free_perf_collector();
	zbx_co_uninitialize();
#endif
}