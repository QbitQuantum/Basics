	// Upload the framebuffer for the current frame... should be called once a frame!
	void FrameBuffer(UInt64 timestamp, FrameBufferFormat format, UInt32 width, UInt32 height, const void *buffer)
	{
		if(TryLockConnection(Enable_FrameBuffer_Capture))
		{
			UInt32 pixelSize = 0;
			switch(format)
			{
				case FrameBuffer_RGB_565:   pixelSize=16; break;
				case FrameBuffer_RGBA_8888: pixelSize=32; break;
				case FrameBuffer_DXT1:      pixelSize=4;
					if(width&3 || height&3)
					{
						Logf(Log_Warning, "OVR::Capture::FrameBuffer(): requires DXT1 texture dimensions to be multiples of 4");
						return;
					}
					break;
			}
			if(!pixelSize)
			{
				Logf(Log_Warning, "OVR::Capture::FrameBuffer(): Format (%u) not supported!", (UInt32)format);
				return;
			}
			const UInt32 payloadSize = (pixelSize * width * height) >> 3; // pixelSize is in bits, divide by 8 to give us payload byte size
			FrameBufferPacket packet;
			packet.format     = format;
			packet.width      = width;
			packet.height     = height;
			packet.timestamp  = timestamp;
			// TODO: we should probably just send framebuffer packets directly over the network rather than
			//       caching them due to their size and to reduce latency.
			AsyncStream::Acquire()->WritePacket(packet, buffer, payloadSize);
			UnlockConnection();
		}
	}