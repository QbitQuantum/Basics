	void VideoCallback(void* raw, uint32_t frameTimestamp) {
		uint8_t* frame = static_cast<uint8_t*>(raw);
		uint64_t timestamp = Thread::getTimeStampMs();

		uint16_t rows = 0;
		uint16_t cols = 0;

		if (_frameCountVideo % 30 == 0)
			std::cout << "Video data @" << (1000/(timestamp-_lastTimestampVideo)) << "fps" << std::endl << std::flush;

		_frameCountVideo++;
		if(_frameCountVideo % _modulo)			//send every _frameCountDepth modulo _modulo frame
			return;

		switch (getVideoResolution()) {
		case FREENECT_RESOLUTION_LOW:
			cols = 320;
			rows = 240;
			break;
		case FREENECT_RESOLUTION_MEDIUM:
			cols = 640;
			rows = 480;
			break;
		case FREENECT_RESOLUTION_HIGH:
			cols = 1280;
			rows = 1024;
			break;
		default:
			break;
		}

		size_t frameSize = getVideoBufferSize();
		std::vector<uint8_t> scaled(frameSize / 4);

		/**
		 * naive rescaling for bayes
		 * Pixel arrangement:
		 *
		 * G R G R G R G R
		 * B G B G B G B G
		 * G R G R G R G R
		 * B G B G B G B G
		 * G R G R G R G R
		 * B G B G B G B G
		 */

		size_t blockRows = 240; // top to bottom 240 -> 120 blocks
		size_t blockCols = 320; // left to right 320 -> 160 blocks
		size_t hereRight = 1;
		size_t hereDown = 320;
		size_t thereRight = 1;
		size_t thereDown = 640;
		size_t maxHere = 0;

		for (int y = 0; y < blockRows; y += 2) {
			for (int x = 0; x < blockCols; x += 2) {
				// we need to allocate a 2x2 block each
				size_t here  = x + (y * blockCols);
				size_t there = 2 * x + (4 * y * blockCols);
				assert(here < 320*240 - 320);
				assert(there < 640*480 - 640);
				scaled[here]                        = frame[there];
				scaled[here + hereRight]            = frame[there + thereRight];
				scaled[here + hereDown]             = frame[there + thereDown];
				scaled[here + hereRight + hereDown] = frame[there + thereRight + thereDown];
				if (here > maxHere)
					maxHere = here;
			}
		}

		// publish complete frame per tcp, publisher will compress
		{
			Message tcpMsg;
			tcpMsg.putMeta("um.marker", toStr(true));
			tcpMsg.setData((const char*)&scaled[0], scaled.size());


#if 1
			// shave off last few bits to help compression
			char* msgData = const_cast<char*>(tcpMsg.data());
			for (int i = 0; i < tcpMsg.size(); i++) {
//				msgData[i] &= 0xFC;
				msgData[i] &= 0xE0;
//					msgData[i] &= 0xF0;
			}
#endif
#if 0
			std::cout << tcpMsg.size() << " -> ";
			tcpMsg.compress();
			std::cout << tcpMsg.size() << std::endl;
#endif
			pubVideoTCP.send(&tcpMsg);
		}


		{
			// chop into RTP packets
#if 1
			size_t interleaves = 6;
			size_t startSeg = _frameCountVideo % interleaves;
//			std::cout << startSeg << ": ";

			for (int i = 0; i < interleaves; i++) {
				uint16_t index = (startSeg + i) % interleaves;

				while (index * MAX_PAYLOAD_PACKET < scaled.size()) {
//					std::cout << index * MAX_PAYLOAD_PACKET << ", ";
					Message rtpMsg;
					if (index == startSeg) {
//						std::cout << "!";
						rtpMsg.putMeta("um.timestampIncrement", toStr(1));
						rtpMsg.putMeta("um.marker", toStr(true));
					} else {
						rtpMsg.putMeta("um.timestampIncrement", toStr(0));
						rtpMsg.putMeta("um.marker", toStr(false));
					}

					char* buffer = (char*)malloc(MAX_PAYLOAD_PACKET + 2);
					Message::write(buffer, (uint16_t)index);
					memcpy(&buffer[2], &scaled[index * MAX_PAYLOAD_PACKET], (index * MAX_PAYLOAD_PACKET) + MAX_PAYLOAD_PACKET > scaled.size() ? scaled.size() - (index * MAX_PAYLOAD_PACKET) : MAX_PAYLOAD_PACKET);
					rtpMsg.setData(buffer, MAX_PAYLOAD_PACKET + 2);
					free(buffer);

					pubVideoRTP.send(&rtpMsg);

					index += interleaves;
				}
			}
#else
			uint16_t index = 0;

			while (index < scaled.size()) {
				Message rtpMsg;
				if (index == 0) {
					rtpMsg.putMeta("um.timestampIncrement", toStr(1));
					rtpMsg.putMeta("um.marker", toStr(true));
				} else {
					rtpMsg.putMeta("um.timestampIncrement", toStr(0));
					rtpMsg.putMeta("um.marker", toStr(false));
				}

				char* buffer = (char*)malloc(MAX_PAYLOAD_PACKET + 2);
				Message::write((uint16_t)index, buffer);
				memcpy(&buffer[2], &scaled[index], index + MAX_PAYLOAD_PACKET > scaled.size() ? scaled.size() - index : MAX_PAYLOAD_PACKET);
				rtpMsg.setData(buffer, MAX_PAYLOAD_PACKET + 2);
				free(buffer);

				pubVideoRTP.send(&rtpMsg);

				index += MAX_PAYLOAD_PACKET;
			}
#endif
		}

		_lastTimestampVideo = timestamp;
	}