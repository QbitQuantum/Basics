void AnalyzerToolUtils::getSpectrum(SoundAnalyzer* soundAnalyzer)
{
	//FMod variable
	boost::thread_group threadpool;

	FMOD::DSP* dspSpectrum;
	FMOD::ChannelGroup* masterChannel;
	FMOD::Channel* chan;
	FMOD_RESULT res;

	//Variable
	int sampleRate, musicSpectrumSize;
	unsigned int soundTime;
	float niquistRate, i = 0;


	//sound time in MS
	soundAnalyzer->Sound->getLength(&soundTime, FMOD_TIMEUNIT_MS);

	//DSP / FFT / Window
	soundAnalyzer->sys->createDSPByType(FMOD_DSP_TYPE_FFT, &dspSpectrum);
	dspSpectrum->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, soundAnalyzer->GetWindowSize());
	dspSpectrum->getParameterInt(FMOD_DSP_FFT_WINDOWSIZE, &musicSpectrumSize, 0, 0);
	dspSpectrum->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_TRIANGLE);

	//Master Channel -> Add Dsp
	soundAnalyzer->sys->getMasterChannelGroup(&masterChannel);
	masterChannel->addDSP(0, dspSpectrum);
	soundAnalyzer->sys->setOutput(FMOD_OUTPUTTYPE_NOSOUND_NRT); //FMOD_OUTPUTTYPE_NOSOUND_NRT
	soundAnalyzer->sys->playSound(soundAnalyzer->Sound, masterChannel, false, &chan);

	soundAnalyzer->sys->setDSPBufferSize(SPECTRUM_BUFFER_SIZE, 0);

	soundAnalyzer->sys->update();

	//Get Samplerate
	soundAnalyzer->sys->getSoftwareFormat(&sampleRate, 0, 0);
	niquistRate = sampleRate / 2.0f;

	soundAnalyzer->data.SpectrumData.resize(static_cast<int>(soundTime / (((double)SPECTRUM_BUFFER_SIZE / (double)sampleRate) * 1000)) + 1);

	soundAnalyzer->SetFrequencyStep(musicSpectrumSize / niquistRate);

	int index = 0;
	//double val;
	do{
		FMOD_DSP_PARAMETER_FFT *dataSpectrum;
		dspSpectrum->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&dataSpectrum, 0, 0, 0);
		
		SpectrumSegment segment(musicSpectrumSize / 2, musicSpectrumSize / niquistRate);
		threadpool.create_thread(boost::bind(&AnalyzerToolUtils::ExtractSpectrum, soundAnalyzer, boost::ref(dataSpectrum), musicSpectrumSize/2, musicSpectrumSize / niquistRate, index));
		/*for (int bin = 0; bin < dataSpectrum->length/2; bin++)
		{
			val = 0;
			for (int channel = 0; channel < MAX_CHANNELS; channel++)
			{
				val += dataSpectrum->spectrum[channel][bin];
			}
			segment.AddSegment(val);
		}

		soundAnalyzer->data.AddData(segment);*/
		soundAnalyzer->sys->update();
		index++;
		i += ((double)SPECTRUM_BUFFER_SIZE / (double)sampleRate) * 1000;
	} while (i < (soundTime));

	threadpool.join_all();
}