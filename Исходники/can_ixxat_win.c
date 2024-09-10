/*************************************************************************
**
**    Function      : canClose_driver 
**
**    Description   : Close the message and control channel
**    Parameters    : CAN_HANDLE inst		- handle for CAN controller 
**    Returnvalue   : 
**   
*************************************************************************/
 int __stdcall canClose_driver(CAN_HANDLE inst)
   {
	printf("CAN close \n");
	canControlReset(hCanCtl);
	canChannelClose(hCanChn);
	canControlClose(hCanCtl);
	vciDeviceClose(hDevice);
	DeleteTimerQueueTimer(NULL,hTimerHandle,NULL); 
   return 1;
   }