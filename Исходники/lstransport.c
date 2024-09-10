NTSTATUS
LstransIsInAddressList(
	IN PTA_LSTRANS_ADDRESS	AddrList,
	IN PTA_LSTRANS_ADDRESS	Address,
	IN BOOLEAN				InvalidateIfMatch
){
	NTSTATUS	status;
	ULONG		idx_addr;


	//
	//	Parameter check
	//

	if(!Address || Address->TAAddressCount != 1) {
		return STATUS_INVALID_PARAMETER;
	}
	if(!AddrList || AddrList->TAAddressCount < 1) {
		return STATUS_INVALID_PARAMETER;
	}


	//
	//	Match address
	//

	status = STATUS_OBJECT_NAME_NOT_FOUND;
	for(idx_addr = 0; idx_addr < (ULONG)AddrList->TAAddressCount; idx_addr++) {

		if( Address->Address[0].AddressType == AddrList->Address[idx_addr].AddressType &&
			Address->Address[0].AddressLength == AddrList->Address[idx_addr].AddressLength &&
			RtlCompareMemory(	&Address->Address[0].Address,
								&AddrList->Address[idx_addr].Address,
								Address->Address[0].AddressLength) == Address->Address[0].AddressLength) {

			if(InvalidateIfMatch) {
					AddrList->Address[idx_addr].AddressLength = 0;
			}

			status = STATUS_SUCCESS;
			break;
		}

	}

	return status;
}