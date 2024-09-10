	IOCP::OperationDataPtr IOCP::CreateOperationData(IOCPStreamPtr stream, HANDLE completionPort) {
		// Begin to process I/O using overlapped I/O
		// Post one or many WSARecv or WSASend requests to the new socket
		// Worker thread will serve the I/O request after the I/O request finished.
		IOCP::OperationData* perIOData = new IOCP::OperationData();
		perIOData->stream = stream.get();

		// Relate the socket to CompletionPort
		CreateIoCompletionPort((HANDLE)(perIOData->stream->GetNativeSocket()),
            completionPort, (ULONG_PTR)perIOData->stream->GetNativeSocket(), 0);

		ZeroMemory(&(perIOData->overlapped), sizeof(OVERLAPPED));
		perIOData->databuff.len = BUFSIZ;
		perIOData->databuff.buf = perIOData->buffer;
		perIOData->operationType = IOCP::OperationType::Read;

		return IOCP::OperationDataPtr(perIOData);
	}