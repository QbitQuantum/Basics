NTSTATUS
LspNoOperation(
	   IN PLANSCSI_SESSION	LSS,
		IN UINT32			TargetId,
	   OUT PBYTE			PduResponse
	)
{
	_int8								PduBuffer[MAX_REQUEST_SIZE];
	PLANSCSI_H2R_PDU_HEADER				pRequestHeader;
	LANSCSI_PDU_POINTERS				pdu;
	NTSTATUS							ntStatus;

	//
	// Check Parameters.
	//
	if(PduResponse == NULL) {
		KDPrintM(DBG_PROTO_ERROR, ("pResult is NULL!!!\n"));
		return STATUS_INVALID_PARAMETER;
	}

	//
	// Make Request.
	//
	memset(PduBuffer, 0, MAX_REQUEST_SIZE);
	
	pRequestHeader = (PLANSCSI_H2R_PDU_HEADER)PduBuffer;
	pRequestHeader->Opcode = NOP_H2R;
	pRequestHeader->HPID = HTONL(LSS->HPID);
	pRequestHeader->RPID = HTONS(LSS->RPID);
	pRequestHeader->PathCommandTag = HTONL(++LSS->CommandTag);
	pRequestHeader->TargetID = TargetId;

	//
	// Send Request.
	//
	pdu.pH2RHeader = (PLANSCSI_H2R_PDU_HEADER)pRequestHeader;

	ntStatus = LspSendRequest(LSS, &pdu, NULL);
	if(!NT_SUCCESS(ntStatus)) {
		KDPrintM(DBG_PROTO_ERROR, ("Error when Send Request.\n"));
		return ntStatus;
	}

	if (LSS->HWVersion == LANSCSIIDE_VERSION_2_5) {
		// NDAS 2.5 replies to NOP
		// Read Reply.
		ntStatus = LspReadReply(LSS, (PCHAR)PduBuffer, &pdu, NULL);
		if(!NT_SUCCESS(ntStatus)) {
			KDPrintM(DBG_PROTO_ERROR, ("Error when read request.\n"));
			return ntStatus;
		}
		if (NOP_R2H != pdu.pR2HHeader->Opcode) {
			KDPrintM(DBG_PROTO_ERROR, ("Invalid opcode %x replied to NOP.\n", pdu.pR2HHeader->Opcode));
			return ntStatus;
		}
	} else {

	}
	*PduResponse = LANSCSI_RESPONSE_SUCCESS;

	return STATUS_SUCCESS;
}