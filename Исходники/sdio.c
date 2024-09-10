/*----------------------------------------------------------------------------*/
VOID sdioINTerruptCallback(IN PVOID context, IN UINT_32 u4INTerruptType)
{
	P_GLUE_INFO_T prGlueInfo;
	PDEVICE_EXTENSION prDevExt;
	NTSTATUS rStatus;

	ASSERT(context);
	prGlueInfo = (P_GLUE_INFO_T) context;

	prDevExt = (PDEVICE_EXTENSION) &prGlueInfo->rHifInfo.dx;

	if (prGlueInfo->rHifInfo.u4ReqFlag & REQ_FLAG_HALT) {
		if (prDevExt->BusInterface.AcknowledgeInterrupt)
			rStatus = (prDevExt->BusInterface.AcknowledgeInterrupt) (prDevExt->BusInterface.Context);
		return;
	}

	wlanISR(prGlueInfo->prAdapter, TRUE);

	if (prDevExt->BusInterface.AcknowledgeInterrupt)
		rStatus = (prDevExt->BusInterface.AcknowledgeInterrupt) (prDevExt->BusInterface.Context);

	_InterlockedOr(&prGlueInfo->rHifInfo.u4ReqFlag, REQ_FLAG_INT);
/* KeSetEvent(&prGlueInfo->rHifInfo.rOidReqEvent, EVENT_INCREMENT, FALSE); */
	/* Set EVENT */
	NdisSetEvent(&prGlueInfo->rTxReqEvent);

	return;
}				/* end of sdioINTerruptCallback() */