status_t
BGopherRequest::_ProtocolLoop()
{
	if (fSocket == NULL)
		return B_NO_MEMORY;

	if (!_ResolveHostName()) {
		_EmitDebug(B_URL_PROTOCOL_DEBUG_ERROR,
			"Unable to resolve hostname (%s), aborting.",
				fUrl.Host().String());
		return B_SERVER_NOT_FOUND;
	}

	_EmitDebug(B_URL_PROTOCOL_DEBUG_TEXT, "Connection to %s on port %d.",
		fUrl.Authority().String(), fRemoteAddr.Port());
	status_t connectError = fSocket->Connect(fRemoteAddr);

	if (connectError != B_OK) {
		_EmitDebug(B_URL_PROTOCOL_DEBUG_ERROR, "Socket connection error %s",
			strerror(connectError));
		return connectError;
	}

	//! ProtocolHook:ConnectionOpened
	if (fListener != NULL)
		fListener->ConnectionOpened(this);

	_EmitDebug(B_URL_PROTOCOL_DEBUG_TEXT,
		"Connection opened, sending request.");

	_SendRequest();
	_EmitDebug(B_URL_PROTOCOL_DEBUG_TEXT, "Request sent.");

	// Receive loop
	bool receiveEnd = false;
	status_t readError = B_OK;
	ssize_t bytesRead = 0;
	//ssize_t bytesReceived = 0;
	//ssize_t bytesTotal = 0;
	bool dataValidated = false;
	BStackOrHeapArray<char, 4096> chunk(kGopherBufferSize);

	while (!fQuit && !receiveEnd) {
		fSocket->WaitForReadable();
		bytesRead = fSocket->Read(chunk, kGopherBufferSize);

		if (bytesRead < 0) {
			readError = bytesRead;
			break;
		} else if (bytesRead == 0)
			receiveEnd = true;

		fInputBuffer.AppendData(chunk, bytesRead);

		if (!dataValidated) {
			size_t i;
			// on error (file doesn't exist, ...) the server sends
			// a faked directory entry with an error message
			if (fInputBuffer.Size() && fInputBuffer.Data()[0] == '3') {
				int tabs = 0;
				bool crlf = false;

				// make sure the buffer only contains printable characters
				// and has at least 3 tabs before a CRLF
				for (i = 0; i < fInputBuffer.Size(); i++) {
					char c = fInputBuffer.Data()[i];
					if (c == '\t') {
						if (!crlf)
							tabs++;
					} else if (c == '\r' || c == '\n') {
						if (tabs < 3)
							break;
						crlf = true;
					} else if (!isprint(fInputBuffer.Data()[i])) {
						crlf = false;
						break;
					}
				}
				if (crlf && tabs > 2 && tabs < 5) {
					// TODO:
					//if enough data
					// else continue
					fItemType = GOPHER_TYPE_DIRECTORY;
					readError = B_RESOURCE_NOT_FOUND;
					// continue parsing the error text anyway
				}
			}
			// special case for buggy(?) Gophernicus/1.5
			static const char *buggy = "Error: File or directory not found!";
			if (fInputBuffer.Size() > strlen(buggy)
				&& !memcmp(fInputBuffer.Data(), buggy, strlen(buggy))) {
				fItemType = GOPHER_TYPE_DIRECTORY;
				readError = B_RESOURCE_NOT_FOUND;
				// continue parsing the error text anyway
				// but it won't look good
			}
			

			// now we probably have correct data
			dataValidated = true;

			//! ProtocolHook:ResponseStarted
			if (fListener != NULL)
				fListener->ResponseStarted(this);

			// we don't really have headers but well...
			//! ProtocolHook:HeadersReceived
			if (fListener != NULL)
				fListener->HeadersReceived(this);

			// now we can assign MIME type if we know it
			const char *mime = "application/octet-stream";
			for (i = 0; gopher_type_map[i].type != GOPHER_TYPE_NONE; i++) {
				if (gopher_type_map[i].type == fItemType) {
					mime = gopher_type_map[i].mime;
					break;
				}
			}
			fResult.SetContentType(mime);
		}

		if (_NeedsParsing())
			_ParseInput(receiveEnd);
		else if (fInputBuffer.Size()) {
			// send input directly
			fListener->DataReceived(this, (const char *)fInputBuffer.Data(),
								fPosition, fInputBuffer.Size());

			fPosition += fInputBuffer.Size();

			// XXX: this is plain stupid, we already copied the data
			// and just want to drop it...
			char *inputTempBuffer = new(std::nothrow) char[bytesRead];
			if (inputTempBuffer == NULL) {
				readError = B_NO_MEMORY;
				break;
			}
			fInputBuffer.RemoveData(inputTempBuffer, fInputBuffer.Size());
			delete[] inputTempBuffer;
		}
	}

	if (fPosition > 0) {
		fResult.SetLength(fPosition);
		fListener->DownloadProgress(this, fPosition, fPosition);
	}

	fSocket->Disconnect();

	if (readError != B_OK)
		return readError;

	return fQuit ? B_INTERRUPTED : B_OK;
}