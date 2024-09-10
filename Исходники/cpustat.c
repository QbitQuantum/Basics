int	init_cpu_collector(ZBX_CPUS_STAT_DATA *pcpus)
{
	const char			*__function_name = "init_cpu_collector";
	int				cpu_num, ret = FAIL;
#ifdef _WINDOWS
	TCHAR				cpu[8];
	char				counterPath[PDH_MAX_COUNTER_PATH];
	PDH_COUNTER_PATH_ELEMENTS	cpe;
#endif
	zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);

#ifdef _WINDOWS
	cpe.szMachineName = NULL;
	cpe.szObjectName = get_counter_name(PCI_PROCESSOR);
	cpe.szInstanceName = cpu;
	cpe.szParentInstance = NULL;
	cpe.dwInstanceIndex = -1;
	cpe.szCounterName = get_counter_name(PCI_PROCESSOR_TIME);

	for (cpu_num = 0; cpu_num <= pcpus->count; cpu_num++)
	{
		if (0 == cpu_num)
			zbx_wsnprintf(cpu, sizeof(cpu) / sizeof(TCHAR), TEXT("_Total"));
		else
			_itow_s(cpu_num - 1, cpu, sizeof(cpu) / sizeof(TCHAR), 10);

		if (ERROR_SUCCESS != zbx_PdhMakeCounterPath(__function_name, &cpe, counterPath))
			goto clean;

		if (NULL == (pcpus->cpu_counter[cpu_num] = add_perf_counter(NULL, counterPath, MAX_CPU_HISTORY)))
			goto clean;
	}

	cpe.szObjectName = get_counter_name(PCI_SYSTEM);
	cpe.szInstanceName = NULL;
	cpe.szCounterName = get_counter_name(PCI_PROCESSOR_QUEUE_LENGTH);

	if (ERROR_SUCCESS != zbx_PdhMakeCounterPath(__function_name, &cpe, counterPath))
		goto clean;

	if (NULL == (pcpus->queue_counter = add_perf_counter(NULL, counterPath, MAX_CPU_HISTORY)))
		goto clean;

	ret = SUCCEED;
clean:
#else	/* not _WINDOWS */
	if (ZBX_MUTEX_ERROR == zbx_mutex_create_force(&cpustats_lock, ZBX_MUTEX_CPUSTATS))
	{
		zbx_error("unable to create mutex for cpu collector");
		exit(EXIT_FAILURE);
	}

#ifndef HAVE_KSTAT_H
	for (cpu_num = 0; cpu_num <= pcpus->count; cpu_num++)
		pcpus->cpu[cpu_num].cpu_num = cpu_num;
#else
	/* Solaris */

	/* CPU instance numbers on Solaris can be non-contiguous, we don't know them yet */
	pcpus->cpu[0].cpu_num = 0;
	for (cpu_num = 1; cpu_num <= pcpus->count; cpu_num++)
		pcpus->cpu[cpu_num].cpu_num = -1;

	if (NULL == (kc = kstat_open()))
	{
		zbx_error("kstat_open() failed");
		exit(EXIT_FAILURE);
	}

	kc_id = kc->kc_chain_id;

	if (NULL == ksp)
		ksp = zbx_malloc(ksp, sizeof(kstat_t *) * pcpus->count);

	if (SUCCEED != refresh_kstat(pcpus))
	{
		zbx_error("kstat_chain_update() failed");
		exit(EXIT_FAILURE);
	}
#endif	/* HAVE_KSTAT_H */

	ret = SUCCEED;
#endif	/* _WINDOWS */

	zabbix_log(LOG_LEVEL_DEBUG, "End of %s():%s", __function_name, zbx_result_string(ret));

	return ret;
}