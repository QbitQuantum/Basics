const UInt8* HTTPPacket::build(Exception& ex,PoolBuffer& pBuffer,const UInt8* data,UInt32& size) {
	/// append data
	if (!_pBuffer.empty()) {
		UInt32 oldSize = _pBuffer->size();
		_pBuffer->resize(oldSize+size,true);
		memcpy(_pBuffer->data()+oldSize, data,size);
	} else
		_pBuffer.swap(pBuffer); // exchange the buffers

	/// read data
	UInt8				newLineCount(0);
	ReadingStep			step(CMD);
	UInt8*				current(_pBuffer->data());
	UInt8*				end(current+_pBuffer->size());
	const char*			signifiant(NULL);
	const char*			key(NULL);

	for (current; current < end;++current) {
		// http header
		UInt8 byte = *current;

		if (byte=='\r') {
			++newLineCount;
			step = LINE_RETURN;
		} else if (step==LINE_RETURN && byte=='\n')
			++newLineCount;
		else {
			newLineCount = 0;

			if ((step == LEFT || step == CMD || step == PATH) && isspace(byte)) {
				if (step == CMD) {
					// by default command == GET
					if ((command = HTTP::ParseCommand(ex, signifiant)) == HTTP::COMMAND_UNKNOWN) {
						_pBuffer.release();
						return NULL;
					}
					signifiant = NULL;
					step = PATH;
				} else if (step == PATH) {
					_buffer.assign(signifiant, (const char*)current - signifiant);
					// parse query
					filePos = Util::UnpackUrl(_buffer, path,query);
					signifiant = NULL;
					step = VERSION;
				} else
					++signifiant; // for trim begin of key or value
				continue;
			} else if (step != CMD && !key && byte == ':') {
				// KEY
				key = signifiant;
				step = LEFT;
				UInt8* prev = current;
				while (isblank(*--current));
				*(current+1) = '\0';
				current = prev;
				headers.emplace_back(signifiant);
				signifiant = (const char*)current + 1;
			} else if (step == CMD || step == PATH || step == VERSION) {
				if (!signifiant)
					signifiant = (const char*)current;
				if (step == CMD && (current-_pBuffer->data())>7) {
					// not a HTTP valid packet, consumes all
					_pBuffer.release();
					ex.set(Exception::PROTOCOL, "unvalid HTTP packet");
					return NULL;
				}
			} else
				step = RIGHT;
			continue;
		}
		
		if (newLineCount == 2) {
			if (signifiant) {
				// KEY = VALUE
				UInt8* prev = current--;
				while (isblank(*--current));
				*(current+1) = '\0';
				current = prev;
				if (!key) { // version case!
					String::ToNumber(signifiant+5, version);
				} else {
					headers.emplace_back(signifiant);
					parseHeader(ex,key,signifiant);
					key = NULL;
				}
			}
			step = LEFT;
			signifiant = (const char*)current+1;
		} else if (newLineCount == 4) {
			content = current + 1;
			current += contentLength;
			break;
		}
	}

	if (current >= end)
		return NULL;  // wait next data

	// exchange the buffers
	pBuffer.swap(_pBuffer);

	UInt32 rest = end-current-1;
	if (rest == 0) {
		_pBuffer.release(); // release buffer
		size = pBuffer->size();
		return pBuffer->data();
	}

	// prepare next iteration
	_pBuffer->resize(rest,false);
	memcpy(_pBuffer->data(), current + 1, rest);
	

	// shrink data
	size = size-rest;
	return pBuffer->data();
}