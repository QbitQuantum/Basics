void sgi_mc_init(running_machine &machine)
{
	nMC_CPUControl0 = 0;
	nMC_CPUControl1 = 0;
	nMC_Watchdog = 0;
	nMC_SysID = 0;
	nMC_RPSSDiv = 0;
	nMC_RefCntPreload = 0;
	nMC_RefCnt = 0;
	nMC_GIO64ArbParam = 0;
	nMC_ArbCPUTime = 0;
	nMC_ArbBurstTime = 0;
	nMC_MemCfg0 = 0;
	nMC_MemCfg1 = 0;
	nMC_CPUMemAccCfg = 0;
	nMC_GIOMemAccCfg = 0;
	nMC_CPUErrorAddr = 0;
	nMC_CPUErrorStatus = 0;
	nMC_GIOErrorAddr = 0;
	nMC_GIOErrorStatus = 0;
	nMC_SysSemaphore = 0;
	nMC_GIOLock = 0;
	nMC_EISALock = 0;
	nMC_GIO64TransMask = 0;
	nMC_GIO64Subst = 0;
	nMC_DMAIntrCause = 0;
	nMC_DMAControl = 0;
	nMC_DMATLBEntry0Hi = 0;
	nMC_DMATLBEntry0Lo = 0;
	nMC_DMATLBEntry1Hi = 0;
	nMC_DMATLBEntry1Lo = 0;
	nMC_DMATLBEntry2Hi = 0;
	nMC_DMATLBEntry2Lo = 0;
	nMC_DMATLBEntry3Hi = 0;
	nMC_DMATLBEntry3Lo = 0;
	nMC_RPSSCounter = 0;
	nMC_DMAMemAddr = 0;
	nMC_DMAMemAddr = 0;
	nMC_DMALineCntWidth = 0;
	nMC_DMALineZoomStride = 0;
	nMC_DMAGIO64Addr = 0;
	nMC_DMAMode = 0;
	nMC_DMAZoomByteCnt = 0;

	// if Indigo2, ID appropriately
	if (!strcmp(machine.system().name, "ip244415"))
	{
		nMC_SysID = 0x11;	// rev. B MC, EISA bus present
	}
}