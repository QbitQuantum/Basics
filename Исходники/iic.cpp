EXPORT_C TInt DIicBusController::DeRegisterChannel(DIicBusChannel* aChannel)
	{
// To be used by Channel implementations to deregister a channel
    __KTRACE_OPT(KIIC, Kern::Printf("DIicBusController::DeRegisterChannel, aChannel=0x%x\n",aChannel));
	if(aChannel == NULL)
		return KErrArgument;

	RPointerArray<DIicBusChannel>* chanArray = TheController->ChannelArray();

#ifdef IIC_INSTRUMENTATION_MACRO
	IIC_DEREGISTERCHAN_START_PIL_TRACE;
#endif
	TInt r=KErrNone;
	// Get access to the channel pointer array - exit if it is currently unavailable
	// Gaining write access will prevent a client of a Master Channel from instigating a new QueueTransaction
	// (or CancelTransaction), and it will obstruct a client of a Slave Channel in CaptureChannel.
	if((r=TheController->GetChanWriteAccess())!=KErrNone)
		return r;

	// Check channel is registered
	TInt chanIndex = chanArray->FindInOrder(aChannel,EntryOrder);
	if(chanIndex<0)
		{
		TheController->FreeChanWriteAccess();
		return KErrNotFound;
		}

#ifdef _DEBUG
    __KTRACE_OPT(KIIC, Kern::Printf("DIicBusController::DeRegisterChannel - On entry, iChannelArray ...\n"));
	TheController->DumpChannelArray();
#endif

	// Remove the channel from the array
	// Note that this does not delete the channel object
	chanArray->Remove(chanIndex);

#ifdef _DEBUG
    __KTRACE_OPT(KIIC, Kern::Printf("DIicBusController::DeRegisterChannel - On exit, iChannelArray ...\n"));
	TheController->DumpChannelArray();
#endif
	TheController->FreeChanWriteAccess();

#ifdef IIC_INSTRUMENTATION_MACRO
	IIC_DEREGISTERCHAN_END_PIL_TRACE;
#endif
	return KErrNone;
	}