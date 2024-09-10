static int 					init_VChan_type 					(VChan_type* 					vchan, 
																char 							name[], 
										 						VChanDataFlows 					flowType, 
														 		void* 							VChanOwner, 	
										 				 		DiscardVChanFptr_type 			DiscardFptr,
										 				 		DisconnectVChanFptr_type		DisconnectFptr,
																VChanStateChangeCBFptr_type		VChanStateChangeCBFptr,
																VChanIsConnectedFptr_type		VChanIsConnectedFptr)
{
	// Data
	vchan->name   					= StrDup(name); 
	if (!vchan->name) return -1;
	vchan->dataFlow					= flowType;
	vchan->isActive					= TRUE;
	vchan->isOpen					= FALSE;
	
	vchan->VChanOwner				= VChanOwner;
	
	// Callbacks
	vchan->VChanStateChangeCBFptr	= VChanStateChangeCBFptr;
	
	// Methods
	vchan->DiscardFptr				= DiscardFptr;
	vchan->DisconnectFptr			= DisconnectFptr;
	vchan->VChanIsConnectedFptr		= VChanIsConnectedFptr;
	
	return 0;
}