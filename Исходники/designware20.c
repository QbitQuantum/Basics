Result HcdSumbitControlMessage(struct UsbDevice *device, 
	struct UsbPipeAddress pipe, void* buffer, u32 bufferLength,
	struct UsbDeviceRequest *request) {
	Result result;
	struct UsbPipeAddress tempPipe;
	if (pipe.Device == RootHubDeviceNumber) {
		return HcdProcessRootHubMessage(device, pipe, buffer, bufferLength, request);
	}

	device->Error = Processing;
	device->LastTransfer = 0;
			
	// Setup
	tempPipe.Speed = pipe.Speed;
	tempPipe.Device = pipe.Device;
	tempPipe.EndPoint = pipe.EndPoint;
	tempPipe.MaxSize = pipe.MaxSize;
	tempPipe.Type = Control;
	tempPipe.Direction = Out;
	
	if ((result = HcdChannelSendWait(device, &tempPipe, 0, request, 8, request, Setup)) != OK) {		
		LOGF("HCD: Could not send SETUP to %s.\n", UsbGetDescription(device));
		return OK;
	}

	// Data
	if (buffer != NULL) {
		if (pipe.Direction == Out) {
			MemoryCopy(databuffer, buffer, bufferLength);
		}
		tempPipe.Speed = pipe.Speed;
		tempPipe.Device = pipe.Device;
		tempPipe.EndPoint = pipe.EndPoint;
		tempPipe.MaxSize = pipe.MaxSize;
		tempPipe.Type = Control;
		tempPipe.Direction = pipe.Direction;
		
		if ((result = HcdChannelSendWait(device, &tempPipe, 0, databuffer, bufferLength, request, Data1)) != OK) {		
			LOGF("HCD: Could not send DATA to %s.\n", UsbGetDescription(device));
			return OK;
		}
						
		ReadBackReg(&Host->Channel[0].TransferSize);
		if (pipe.Direction == In) {
			if (Host->Channel[0].TransferSize.TransferSize <= bufferLength)
				device->LastTransfer = bufferLength - Host->Channel[0].TransferSize.TransferSize;
			else{
				LOG_DEBUGF("HCD: Weird transfer.. %d/%d bytes received.\n", Host->Channel[0].TransferSize.TransferSize, bufferLength);
				LOG_DEBUGF("HCD: Message %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x ...\n", 
					((u8*)databuffer)[0x0],((u8*)databuffer)[0x1],((u8*)databuffer)[0x2],((u8*)databuffer)[0x3],
					((u8*)databuffer)[0x4],((u8*)databuffer)[0x5],((u8*)databuffer)[0x6],((u8*)databuffer)[0x7],
					((u8*)databuffer)[0x8],((u8*)databuffer)[0x9],((u8*)databuffer)[0xa],((u8*)databuffer)[0xb],
					((u8*)databuffer)[0xc],((u8*)databuffer)[0xd],((u8*)databuffer)[0xe],((u8*)databuffer)[0xf]);
				device->LastTransfer = bufferLength;
			}
			MemoryCopy(buffer, databuffer, device->LastTransfer);
		}
		else {
			device->LastTransfer = bufferLength;
		}
	}

	// Status
	tempPipe.Speed = pipe.Speed;
	tempPipe.Device = pipe.Device;
	tempPipe.EndPoint = pipe.EndPoint;
	tempPipe.MaxSize = pipe.MaxSize;
	tempPipe.Type = Control;
	tempPipe.Direction = ((bufferLength == 0) || pipe.Direction == Out) ? In : Out;
	
	if ((result = HcdChannelSendWait(device, &tempPipe, 0, databuffer, 0, request, Data1)) != OK) {		
		LOGF("HCD: Could not send STATUS to %s.\n", UsbGetDescription(device));
		return OK;
	}

	ReadBackReg(&Host->Channel[0].TransferSize);
	if (Host->Channel[0].TransferSize.TransferSize != 0)
		LOG_DEBUGF("HCD: Warning non zero status transfer! %d.\n", Host->Channel[0].TransferSize.TransferSize);

	device->Error = NoError;

	return OK;
}