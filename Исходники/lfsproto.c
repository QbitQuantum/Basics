//
//	compare addresses to see if the address is local.
//
BOOLEAN
LfsIsFromLocal(
		PLPX_ADDRESS	Addr
	) {
	NTSTATUS				ntStatus;

	SOCKETLPX_ADDRESS_LIST	socketLpxAddressList;
	LONG					idx_addr ;
	
	
	SPY_LOG_PRINT( LFS_DEBUG_TABLE_NOISE, ( "[LFS] LfsIsFromLocal: Entered with Addr:%02x:%02x:%02x:%02x:%02x:%02x\n",
				Addr->Node[0], Addr->Node[1], Addr->Node[2], 
				Addr->Node[3], Addr->Node[4], Addr->Node[5]
			));

	//
	//	get addresses from LPX
	//
	socketLpxAddressList.iAddressCount = 0 ;
	ntStatus = LpxTdiV2GetAddressList(
		&socketLpxAddressList
    ) ;
	if(!NT_SUCCESS(ntStatus)) {
		SPY_LOG_PRINT( LFS_DEBUG_LFS_TRACE, ( "[LFS] LfsIsFromLocal: LpxTdiV2GetAddressList() failed.\n")) ;
		return FALSE ;
	}
	if(0 == socketLpxAddressList.iAddressCount) {
		SPY_LOG_PRINT( LFS_DEBUG_LFS_TRACE, ( "[LFS] LfsIsFromLocal: No NICs in the host.\n")) ;
		return FALSE ;
	}

	for(idx_addr = 0 ; idx_addr < socketLpxAddressList.iAddressCount ; idx_addr ++ ) {
		//
		//	BUG FIX for LPX: skip SocketLpxDevice
		//
		if( (0 == socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node[0]) &&
			(0 == socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node[1]) &&
			(0 == socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node[2]) &&
			(0 == socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node[3]) &&
			(0 == socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node[4]) &&
			(0 == socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node[5]) ) {

			SPY_LOG_PRINT( LFS_DEBUG_LFS_TRACE, ( "[LFS] LfsIsFromLocal: We don't use SocketLpx device.\n") );
			continue ;

		}

		if( RtlCompareMemory(Addr->Node, socketLpxAddressList.SocketLpx[idx_addr].LpxAddress.Node, ETHER_ADDR_LENGTH)
			== ETHER_ADDR_LENGTH ) {
				SPY_LOG_PRINT( LFS_DEBUG_TABLE_NOISE, ( "[LFS] LfsIsFromLocal: found a address matching.\n")) ;
				return TRUE ;
		}
	}


	return FALSE ;
}