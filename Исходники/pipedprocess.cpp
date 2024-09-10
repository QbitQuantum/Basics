	DWORD SpawnProcess(char *cmdline) {
		ProcBuffers *pb = new ProcBuffers(cmdline);
		pb->Start();
		ProcBuffers::putProcBuffer(pb->getPid(), pb);
		return pb->getPid();
	}