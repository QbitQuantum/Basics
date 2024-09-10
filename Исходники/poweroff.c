int poweroffInit()
{
	int res;
	static int _init_count = -1;

	if(_init_count == _iop_reboot_count)
		return 0;
	_init_count = _iop_reboot_count;

	while(((res = SifBindRpc(&cd0, PWROFF_IRX, 0)) >= 0) && (cd0.server == NULL))
		nopdelay();

	ee_thread_t thread;
	ee_thread_status_t thisThread;

	ee_sema_t sema;

	// Terminate and delete any previously created threads
	if (powerOffThreadId >= 0) {
		TerminateThread(powerOffThreadId);
		DeleteThread(powerOffThreadId);
		powerOffThreadId = -1;
	}

	// Delete any previously created semaphores
	if (PowerOffSema >= 0)
	{
		DeleteSema(PowerOffSema);
		PowerOffSema = -1;
	}

	sema.init_count = 0;
	sema.max_count = 1;
	sema.option = 0;
	PowerOffSema = CreateSema(&sema);

	ReferThreadStatus(GetThreadId(), &thisThread);

	if (thisThread.current_priority == 0) {
		ChangeThreadPriority(GetThreadId(), 51);
		thread.initial_priority = 50;
	} else
		thread.initial_priority = thisThread.current_priority - 1;

	thread.stack_size = 512 * 16;
	thread.gp_reg = &_gp;
	thread.func = PowerOffThread;
	thread.stack = (void *)poffThreadStack;
	powerOffThreadId = CreateThread(&thread);
	StartThread(powerOffThreadId, NULL);
	
	DIntr();
	SifAddCmdHandler(POFF_SIF_CMD, _poff_intr_callback, NULL);
	EIntr();

	int autoShutdown = 0;
	SifCallRpc(&cd0, PWROFF_ENABLE_AUTO_SHUTOFF, 0, NULL, 0, &autoShutdown, sizeof(autoShutdown), 0, 0);
	
	return res;
}