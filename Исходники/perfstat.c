void	collect_perfstat()
{
	const char		*__function_name = "collect_perfstat";
	PERF_COUNTER_DATA	*cptr;
	PDH_STATUS		pdh_status;
	time_t			now;
	PDH_FMT_COUNTERVALUE	value;

	if (SUCCEED != perf_collector_started())
		return;

	if (NULL == ppsd.pPerfCounterList)	/* no counters */
		return;

	zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);

	now = time(NULL);

	/* refresh unsupported counters */
	if (ppsd.nextcheck <= now)
	{
		for (cptr = ppsd.pPerfCounterList; NULL != cptr; cptr = cptr->next)
 		{
			if (PERF_COUNTER_NOTSUPPORTED != cptr->status)
				continue;

			zbx_PdhAddCounter(__function_name, cptr, ppsd.pdh_query, cptr->counterpath, &cptr->handle);
		}

		ppsd.nextcheck = now + UNSUPPORTED_REFRESH_PERIOD;
	}

	/* query for new data */
	if (ERROR_SUCCESS != (pdh_status = PdhCollectQueryData(ppsd.pdh_query)))
	{
		for (cptr = ppsd.pPerfCounterList; NULL != cptr; cptr = cptr->next)
		{
			if (PERF_COUNTER_NOTSUPPORTED != cptr->status)
				deactivate_perf_counter(cptr);
		}

		zabbix_log(LOG_LEVEL_DEBUG, "%s() call to PdhCollectQueryData() failed: %s",
				__function_name, strerror_from_module(pdh_status, L"PDH.DLL"));

		goto out;
	}

	/* get the raw values */
	for (cptr = ppsd.pPerfCounterList; NULL != cptr; cptr = cptr->next)
	{
		if (PERF_COUNTER_NOTSUPPORTED == cptr->status)
			continue;

		if (ERROR_SUCCESS != zbx_PdhGetRawCounterValue(__function_name, cptr->counterpath,
				cptr->handle, &cptr->rawValues[cptr->olderRawValue]))
		{
			deactivate_perf_counter(cptr);
			continue;
		}

		if (PERF_COUNTER_INITIALIZED < cptr->status)
		{
			zabbix_log(LOG_LEVEL_DEBUG, "%s() counterpath:'%s' old first:%I64d second:%I64d",
					__function_name, cptr->counterpath,
					cptr->rawValues[(cptr->olderRawValue + 1) & 1].FirstValue,
					cptr->rawValues[(cptr->olderRawValue + 1) & 1].SecondValue);

			zabbix_log(LOG_LEVEL_DEBUG, "%s() counterpath:'%s' new first:%I64d second:%I64d",
					__function_name, cptr->counterpath,
					cptr->rawValues[cptr->olderRawValue].FirstValue,
					cptr->rawValues[cptr->olderRawValue].SecondValue);
		}

		cptr->olderRawValue = (cptr->olderRawValue + 1) & 1;

		pdh_status = PdhCalculateCounterFromRawValue(cptr->handle, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100,
				&cptr->rawValues[(cptr->olderRawValue + 1) & 1],
				(PERF_COUNTER_INITIALIZED < cptr->status ? &cptr->rawValues[cptr->olderRawValue] : NULL),
				&value);

		if (ERROR_SUCCESS == pdh_status && PDH_CSTATUS_VALID_DATA != value.CStatus &&
				PDH_CSTATUS_NEW_DATA != value.CStatus)
		{
			pdh_status = value.CStatus;
		}

		if (PDH_CSTATUS_INVALID_DATA == pdh_status)
		{
			/* some (e.g., rate) counters require two raw values, MSDN lacks documentation */
			/* about what happens but tests show that PDH_CSTATUS_INVALID_DATA is returned */

			cptr->status = PERF_COUNTER_GET_SECOND_VALUE;
			continue;
		}

		if (PDH_CALC_NEGATIVE_DENOMINATOR == pdh_status)
		{
			/* This counter type shows the average percentage of active time observed during the sample   */
			/* interval. This is an inverse counter. Inverse counters are calculated by monitoring the    */
			/* percentage of time that the service was inactive and then subtracting that value from 100  */
			/* percent. The formula used to calculate the counter value is:                               */
			/* (1 - (inactive time delta) / (total time delta)) x 100                                     */
			/* For some unknown reason sometimes the collected row values indicate that inactive delta is */
			/* greater than total time delta. There must be some kind of bug in how performance counters  */
			/* work. When this happens function PdhCalculateCounterFromRawValue() returns error           */
			/* PDH_CALC_NEGATIVE_DENOMINATOR. Basically this means that an item was inactive all the time */
			/* so we set the return value to 0.0 and change status to indicate success.                   */
			/* More info: technet.microsoft.com/en-us/library/cc757283(WS.10).aspx                        */

			zabbix_log(LOG_LEVEL_DEBUG, "%s() counterpath:'%s'"
					" negative denominator error is treated as 0.0",
					__function_name, cptr->counterpath);

			pdh_status = ERROR_SUCCESS;
			value.doubleValue = 0.0;	/* 100% inactive */
		}

		if (ERROR_SUCCESS == pdh_status)
		{
			zabbix_log(LOG_LEVEL_DEBUG, "%s() '%s' calculated value:" ZBX_FS_DBL, __function_name,
					cptr->counterpath, value.doubleValue);

			cptr->status = PERF_COUNTER_ACTIVE;
			cptr->value_current = (cptr->value_current + 1) % cptr->interval;
			if (cptr->value_count == cptr->interval)
				cptr->sum -= cptr->value_array[cptr->value_current];	/* remove the oldest value, value_count will not increase */
			cptr->value_array[cptr->value_current] = value.doubleValue;
			cptr->sum += cptr->value_array[cptr->value_current];
			if (cptr->value_count < cptr->interval)
				cptr->value_count++;
		}
		else
		{
			zabbix_log(LOG_LEVEL_WARNING, "cannot calculate performance counter value \"%s\": %s",
					cptr->counterpath, strerror_from_module(pdh_status, L"PDH.DLL"));

			deactivate_perf_counter(cptr);
		}
	}
out:
	zabbix_log(LOG_LEVEL_DEBUG, "End of %s()", __function_name);
}