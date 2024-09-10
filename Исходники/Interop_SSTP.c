// Process the SSTP control packet reception
void SstpProcessControlPacket(SSTP_SERVER *s, SSTP_PACKET *p)
{
	// Validate arguments
	if (s == NULL || p == NULL || p->IsControl == false)
	{
		return;
	}

	Debug("SSTP Control Packet Recv: Msg = %u, Num = %u\n", p->MessageType, LIST_NUM(p->AttibuteList));

	switch (p->MessageType)
	{
	case SSTP_MSG_CALL_CONNECT_REQUEST:		// Receive a connection request from a client
		if (s->Aborting == false && s->Disconnecting == false)
		{
			if (s->Status == SSTP_SERVER_STATUS_REQUEST_PENGING)
			{
				SSTP_ATTRIBUTE *protocol_id = SstpFindAttribute(p, SSTP_ATTRIB_ENCAPSULATED_PROTOCOL_ID);
				if (protocol_id != NULL && protocol_id->DataSize == 2 &&
					READ_USHORT(protocol_id->Data) == SSTP_ENCAPSULATED_PROTOCOL_PPP)
				{
					// Accept the connection request by the PPP protocol
					SSTP_PACKET *ret;

					// Generation of random numbers
					Rand(s->SentNonce, SSTP_NONCE_SIZE);

					ret = SstpNewControlPacketWithAnAttribute(SSTP_MSG_CALL_CONNECT_ACK,
						SstpNewCryptoBindingRequestAttribute(CERT_HASH_PROTOCOL_SHA256, s->SentNonce));

					SstpSendPacket(s, ret);

					SstpFreePacket(ret);

					s->Status = SSTP_SERVER_STATUS_CONNECTED_PENDING;

					s->EstablishedCount++;
				}
				else
				{
					// Refuse to accept for a connection request other than the PPP protocol
					SSTP_PACKET *ret = SstpNewControlPacketWithAnAttribute(SSTP_MSG_CALL_CONNECT_NAK,
						SstpNewStatusInfoAttribute(SSTP_ATTRIB_ENCAPSULATED_PROTOCOL_ID, ATTRIB_STATUS_VALUE_NOT_SUPPORTED));

					SstpSendPacket(s, ret);

					SstpFreePacket(ret);
				}
			}
		}
		break;

	case SSTP_MSG_CALL_CONNECTED:			// Connection from the client complete
		if (s->Aborting == false && s->Disconnecting == false)
		{
			if (s->Status == SSTP_SERVER_STATUS_CONNECTED_PENDING)
			{
				s->Status = SSTP_SERVER_STATUS_ESTABLISHED;

				Debug("SSTP Connected.\n");
			}
		}
		break;

	case SSTP_MSG_CALL_DISCONNECT:			// Receive a disconnect request from the client
	case SSTP_MSG_CALL_DISCONNECT_ACK:
		s->DisconnectRecved = true;
		SstpDisconnect(s);
		break;

	case SSTP_MSG_CALL_ABORT:				// Receive a disconnect request from the client
		s->AbortReceived = true;
		SstpAbort(s);
		break;
	}
}