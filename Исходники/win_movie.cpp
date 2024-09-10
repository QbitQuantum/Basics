	void update()
	{
		if(bPaused)
			return;

		int time = timeGetTime() - timestampBegin + timestamp;

		LONG currSample = AVIStreamTimeToSample(stream,time);

		if(currSample >= numSamples)
			currSample = numSamples-1;
		for(LONG l = lastSample+1; l<= currSample; l++)
		{
			nextFrame();
			decodeFrame();
			if(lastSample == numSamples-1)
			{
				pause();
				//err("movie finished playing");
				break;
			}
		}

		lastSample = currSample;

		//render();
	}