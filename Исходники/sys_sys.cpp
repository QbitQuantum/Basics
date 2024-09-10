/*
 * int sysinfo(struct sysinfo *info)
 */
void SysCalls::sys_sysinfo(CONTEXT& ctx)
{
	linux::sysinfo si;
	
	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);

	memset(&si, 0, sizeof(si));
	si.uptime = GetTickCount()/1000;
	si.loads[0] = 0; //1, 5, and 15 minute load averages
	si.loads[1] = 0;
	si.loads[2] = 0;
	si.totalram = ms.dwAvailPhys;
	si.freeram  = ms.dwTotalPhys;
	si.sharedram = 0;/* Amount of shared memory */
	si.bufferram = 0; /* Memory used by buffers */
	si.totalswap = ms.dwTotalPageFile;
	si.freeswap  = ms.dwAvailPageFile;
	si.procs = g_pKernelTable->m_Processes.size();
	si.totalhigh = 0; /* Total high memory size */
	si.freehigh = 0;  /* Available high memory size */
	si.mem_unit = 4096; //same as page size???

	P->WriteMemory((ADDR)ctx.Ebx, sizeof(si), &si);
	ctx.Eax = 0;
}