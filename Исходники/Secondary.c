VOID
INITIALIZE_NDFS_REQUEST_HEADER (
	PNDFS_REQUEST_HEADER	NdfsRequestHeader,
	UINT8					Command,
	PSECONDARY				Secondary,
	UINT8					IrpMajorFunction,
	UINT32					DataSize
	)
{
	ExAcquireFastMutex( &Secondary->FastMutex );		

	RtlCopyMemory(NdfsRequestHeader->Protocol, NDFS_PROTOCOL, sizeof(NdfsRequestHeader->Protocol));
	NdfsRequestHeader->Command	= Command;				
	NdfsRequestHeader->Flags	= Secondary->Thread.SessionContext.Flags;							    
	NdfsRequestHeader->Uid2		= NTOHS(Secondary->Thread.SessionContext.Uid);									
	NdfsRequestHeader->Tid2		= NTOHS(Secondary->Thread.SessionContext.Tid);									
	NdfsRequestHeader->Mid2		= 0;																	    

	NdfsRequestHeader->MessageSize4																			
		= sizeof(NDFS_REQUEST_HEADER)																			
			+ (																									
				(Secondary->Thread.SessionContext.MessageSecurity == 0)										
	 			 ? sizeof(NDFS_WINXP_REQUEST_HEADER) + DataSize											
				 : (																							
					 ((IrpMajorFunction == IRP_MJ_WRITE														
						&& Secondary->Thread.SessionContext.RwDataSecurity == 0								
						&& DataSize <= Secondary->Thread.SessionContext.PrimaryMaxDataSize)				
					 ||																							
					 IrpMajorFunction == IRP_MJ_READ																
						&& Secondary->Thread.SessionContext.RwDataSecurity == 0								
						&& DataSize <= Secondary->Thread.SessionContext.SecondaryMaxDataSize)

					? ADD_ALIGN8(sizeof(NDFS_WINXP_REQUEST_HEADER) + DataSize)							
					: ADD_ALIGN8(sizeof(NDFS_WINXP_REQUEST_HEADER) + DataSize)				
				   )																							
				);																								
	
	NdfsRequestHeader->MessageSize4 = NTOHL(NdfsRequestHeader->MessageSize4);

	ExReleaseFastMutex( &Secondary->FastMutex );

	return;
}																										