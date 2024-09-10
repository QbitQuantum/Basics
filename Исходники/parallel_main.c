static void parallel_irp_request(DEVICE* device, IRP* irp)
{
	PARALLEL_DEVICE* parallel = (PARALLEL_DEVICE*) device;

	InterlockedPushEntrySList(parallel->pIrpList, &(irp->ItemEntry));

	freerdp_thread_signal(parallel->thread);
}