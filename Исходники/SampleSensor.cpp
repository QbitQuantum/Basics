	void SampleSensor::Update(TimeValue dt)
	{
		//check to see if it is time to write an update to this sensor
		m_sampleTimeLeft -= dt;

		//if we still have time left, skip writing an update
		if (m_sampleTimeLeft > 0.0) 
			return;

		//Sending the image is dependent on the frame rate and if the user has closed the connection
		if((frame % (int) (100 / sendRate) == 0) && running) {
			// Get Video Data and Send as ZMQ Message
			std::vector<SensorPtr> sensors = SensorManager::GetSingleton().GetAllSensors();
			for (uint32 i = 0; i < sensors.size(); ++i)
			{
				if (sensors[i]->GetSensorType() != "CameraSensor")
					continue;

				CameraSensor* pCam = static_cast<CameraSensor*>(sensors[i].Get());
		
				const std::vector<LensData>& lens = pCam->GetLensData();
				if (lens.size() == 0)
					continue;

				const LensData& thisLens = lens[0];
				const LensParams & lensParams = pCam->GetLensParams()[0];

				if (thisLens.m_renderRequest.m_pOutputBuffer != NULL) {
					//Pull the dimensions of the camera
					int size, sizeX, sizeY;
					sizeX = lensParams.m_resolutionX;
					sizeY = lensParams.m_resolutionY;
					size = sizeX * sizeY * 3;
				
					//Make a buffer for the compressed jpeg
					void *buf = malloc(size);

					//Set the Quality Factor
					jpge::params params;
					params.m_quality = quality_factor;

					//Compress the image to improve transfer speed
					if(compress_image_to_jpeg_file_in_memory(buf, size, sizeX, sizeY, 3, thisLens.m_renderRequest.m_pOutputBuffer, params)) {
						//Put the compressed data into a ZMQ message and send it over the socket
						zmq::message_t image (size);
						memcpy((void *) image.data(), buf, size);
						socket_.send (image);
					}
					else {
						LogMessage("Failed to compress image", kLogMsgError);
					}
				}
			}
		}
		frame++;
		
		
		m_sampleTimeLeft += m_sampleStep;
	}