int TestDelete::Run(UINT32 (__stdcall * func_DeleteFileByID)(const BYTE *pbyFileID))
{
	int result;
	int i;
	int file_type;
	SYSTEMTIME tStart;
	SYSTEMTIME tEnd;
	int time_used;
	char storage_ip[IP_ADDRESS_SIZE];
	memset(storage_ip, 0, sizeof(storage_ip));

	if ((result = load_file_ids()) != 0)
	{
		return result;
	}

	if ((result=test_init()) != 0)
	{
		return result;
	}

	start_time = time(NULL);
	result = 0;
	total_count = 0;
	success_count = 0;
	for (i=0; i<file_count; i++)
	{
		file_type = file_entries[i].file_type;
		files[file_type].delete_count++;
		total_count++;

		GetLocalTime(&tStart);
		result = func_DeleteFileByID((const BYTE*)file_entries[i].file_id);
		GetLocalTime(&tEnd);
		time_used = TIME_SUB_MS(tEnd, tStart);
		files[file_type].time_used += time_used;

		if (result == 0) //success
		{
			success_count++;
			files[file_type].success_count++;
		}
		else //fail
		{
			fprintf(fpFail, "%d %d %s %s %d %d\n", (int)tEnd.wSecond, 
				files[file_type].bytes, file_entries[i].file_id, 
				storage_ip, result, time_used);
			fflush(fpFail);
		}

		if (total_count % 10000 == 0)
		{
			if ((result=save_stats_by_overall()) != 0)
			{
				break;
			}
			if ((result=save_stats_by_file_type()) != 0)
			{
				break;
			}
		}
	}

	save_stats_by_overall();
	save_stats_by_file_type();

	fclose(fpFail);
	
	for(int i = 0; i < file_count; i++)
	{
		free(file_entries[i].file_id);
	}
	free(file_entries);
	file_entries = NULL;
	
	char debugBuf[256];
	sprintf(debugBuf, "proccess %d, time used: %ds\n", proccess_index, (int)(time(NULL) - start_time));
	OutputDebugString(debugBuf);
	return result;
}