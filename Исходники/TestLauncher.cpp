// ============================================================================================
void	TestLauncher::run()
{
	bool res = false;
	int bsize = audioDeviceSettings->getBufferSize();
	unsigned int deviceChan = audioDeviceSettings->getOutputChannels();
	int nbuff;
	int remsamples;
	double progressMax;

	releaseAudioData();

	for (int i = 0; i<stimCount; i++)
	{
                if (threadShouldExit())
                    break;
		
			/* Create input stream for the audio file */
			File af(getCurrentTest()->soundFiles[i]);
			wavReader = audioFormatManager.createReaderFor( af );

			dbgOut( L"Loading file " + af.getFullPathName() ); 	

			if (wavReader == NULL)
			{
				lastError = L"Unable to create reader for  " + getCurrentTest()->soundFiles[i];
				return ;
	
			}

			/* get length and number of channels */
			if (wavReader->numChannels > deviceChan)
			{
				lastError = L"The number of audio channels in stimuli files exceeds available device outputs.";
				return ;
			}

			chanCount = wavReader->numChannels;
			samplesCount = static_cast<unsigned int> ( wavReader->lengthInSamples );
			
			/* adjust to the integer number of audio buffers */
			nbuff = div(samplesCount,bsize).quot;
			remsamples = div(samplesCount,bsize).rem;
			
			if (remsamples > 0)
			{
				samplesCount = bsize*(nbuff+1);
				progressMax = stimCount*(nbuff+1);
			}
			else
			{
				progressMax = stimCount*nbuff;
			}
				

			/* create audio data buffers */
			currentData = new int* [chanCount];
			if (currentData == NULL)
			{
				lastError = L"Unable to allocate " + String(2*chanCount*sizeof(float*) + L"b of memory." );
				return ;
			}

			/* create an array of pointers to data buffers */
			for (int ch = 0; ch < chanCount; ch++)
			{
				currentData[ch] = new int[samplesCount];
				if (currentData[ch] == NULL)
				{
					lastError = L"Unable to allocate " + String(samplesCount*sizeof(float*) + L"b of memory." );
					/* clean up (data is massive) */
					for (int k = 0; k<ch; k++)
					{
						delete [] currentData[k];
					}
					delete [] currentData;
					releaseAudioData();
					return ;
				}
				/* clear memory */
				//zeromem(currentData[ch], sizeof(int)*samplesCount);
			}
			/* add array to audioStimData */
			audioStimData.add(currentData);

			/* read file in memory */			
			for (int k=0; k<nbuff; k++)
			{
				res = wavReader->readSamples( currentData, chanCount, bsize*k, bsize*k, bsize);
				if (!res)
				{
					releaseAudioData();
					lastError = L"Unable to read data from file " + getCurrentTest()->soundFiles[i];
					return ;
				}

				/* update progress bar */
				setProgress((i*nbuff + k)/progressMax);
			}
			/* read the last buffer and zero pad */
			if (remsamples > 0)
			{
				/* zero-padding is done by AudioFormatReader */
				res = wavReader->readSamples( currentData, chanCount, bsize*nbuff, bsize*nbuff, bsize);
				if (!res)
				{
					releaseAudioData();
					lastError = L"Unable to read data from file " + getCurrentTest()->soundFiles[i];
					return ;
				}
			}

			/* clean up */
			delete wavReader;
	}

	/*for (int k = 0; k<chanCount; k++)
	{		
		debugBuffer(getAudioData(0,k,48000), bsize*5, L"audio") + String(k));
	}*/

	setProgress(1.0);
	wait(500);
}