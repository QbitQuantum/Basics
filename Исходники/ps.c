void list_processes(void)
{
	PSYSTEM_PROCESS_INFORMATION pspi;
	ULONG ofs = 0, sz, i, j;
	NTSTATUS r;

	sz = 0;
	r = NtQuerySystemInformation( SystemProcessInformation, buffer, sizeof buffer, &sz );
	ok( r == STATUS_SUCCESS, "NtQuerySystemInformation failed\n" );
	if (r != STATUS_SUCCESS)
		return;

	for (i=0, ofs=0; ofs<sz; i++)
	{
		pspi = (PSYSTEM_PROCESS_INFORMATION) (buffer + ofs);
		dprintf( "%ld %ld %ld %S\n", pspi->ThreadCount, pspi->ProcessId,
				 pspi->InheritedFromProcessId, pspi->ProcessName.Buffer);
		for (j=0; j<pspi->ThreadCount; j++)
		{
			 dprintf("%p %p %p %08lx %08lx\n",
					 pspi->Threads[j].StartAddress,
					 pspi->Threads[j].ClientId.UniqueProcess,
					 pspi->Threads[j].ClientId.UniqueThread,
					 pspi->Threads[j].State,
					 pspi->Threads[j].WaitReason);
		}
		if (!pspi->NextEntryDelta)
			break;
		ofs += pspi->NextEntryDelta;
	}
}