IOReturn
IOSCSITape::Rewind(void)
{
	IOReturn			status		= kIOReturnError;
	SCSITaskIdentifier	task		= NULL;
	SCSITaskStatus		taskStatus	= kSCSITaskStatus_DeliveryFailure;
	
	task = GetSCSITask();
	
	require ((task != 0), ErrorExit);
	
	if (REWIND(task, 0, 0) == true)
		taskStatus = DoSCSICommand(task, SCSI_MOTION_TIMEOUT);
	
	if (taskStatus == kSCSITaskStatus_GOOD)
		status = kIOReturnSuccess;
	
	ReleaseSCSITask(task);
	
ErrorExit:
	
	return status;
}