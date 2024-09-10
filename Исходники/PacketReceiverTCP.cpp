void PacketReceiverTCP::process()
{
	FSocket *socket = pNetworkInterface_->socket();
	uint32 DataSize = 0;

	while (socket->HasPendingData(DataSize))
	{
		pBuffer_->resize(FMath::Min(DataSize, 65507u));

		int32 BytesRead = 0;
		if (socket->Recv(pBuffer_->data(), pBuffer_->size(), BytesRead))
		{
			pBuffer_->wpos(BytesRead);

			if (pNetworkInterface_->filter())
			{
				pNetworkInterface_->filter()->recv(pMessageReader_, pBuffer_);
			}
			else
			{
				pMessageReader_->process(pBuffer_->data(), 0, BytesRead);
			}
		}
	}
}