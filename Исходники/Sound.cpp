void Sound::playSoundEffect(SoundEffect effect, X3DAUDIO_EMITTER* emit)
{
	IXAudio2SourceVoice* voice = getSFXVoice();

	voice->FlushSourceBuffers();
	
	switch (effect) {
	case SFX_LASER:
		{
			voice->SubmitSourceBuffer(laserBufferDetails, laserWMABuffer);
			break;
		}
	case SFX_CRASH:
		{
			voice->SubmitSourceBuffer(crashBufferDetails, crashWMABuffer);
			break;
		}
	case SFX_BOOST:
		{
			voice->SubmitSourceBuffer(boostBufferDetails, boostWMABuffer);
			break;
		}
	case SFX_DROPMINE:
		{
			voice->SubmitSourceBuffer(dropmineBufferDetails, dropmineWMABuffer);
			break;
		}
	case SFX_SCREAM:
		{
			// Now pick one of the three screams randomly
			int choice = std::rand() % 3;


			voice->SetVolume(2.0f);
			switch (choice) {
				case 0:	voice->SubmitSourceBuffer(scream1BufferDetails, scream1WMABuffer);
					break;
				case 1:	voice->SubmitSourceBuffer(scream2BufferDetails, scream2WMABuffer);
					break;
				case 2:	voice->SubmitSourceBuffer(scream3BufferDetails, scream3WMABuffer);
					break;
				default:
					voice->SubmitSourceBuffer(scream1BufferDetails, scream1WMABuffer);
			}

			break;
		}
	case SFX_CAREXPLODE:
		{
			voice->SetVolume(2.0f);
			voice->SubmitSourceBuffer(carexplodeBufferDetails, carexplodeWMABuffer);
			break;
		}
	case SFX_EXPLOSION:
		{
			voice->SubmitSourceBuffer(explosionBufferDetails, explosionWMABuffer);
			break;
		}
	case SFX_BEEP:
		{
			voice->SubmitSourceBuffer(beepBufferDetails, beepWMABuffer);
			break;
		}
	case SFX_ROCKETLAUNCH:
		{
			voice->SubmitSourceBuffer(rocketlaunchBufferDetails, rocketlaunchWMABuffer);
			break;
		}
	case SFX_PICKUP:
		{
			voice->SetVolume(2.0f);
			voice->SubmitSourceBuffer(pickupBufferDetails, pickupWMABuffer);
			break;
		}
	case SFX_SELECT:
		{
			voice->SubmitSourceBuffer(selectBufferDetails, selectWMABuffer);
			break;
		}
	case SFX_SHOTGUN:
		{
			voice->SetVolume(2.5f);
			voice->SubmitSourceBuffer(shotgunBufferDetails, shotgunWMABuffer);
			break;
		}
	case SFX_TAKENLEAD:
		{
			voice->SubmitSourceBuffer(takenleadBufferDetails, takenleadWMABuffer);
			break;
		}
	case SFX_LOSTLEAD:
		{
			voice->SubmitSourceBuffer(lostleadBufferDetails, lostleadWMABuffer);
			break;
		}
	case SFX_NOAMMO:
		{
			voice->SubmitSourceBuffer(noammoBufferDetails, noammoWMABuffer);
			break;
		}
	case SFX_ONE:
		{
			voice->SubmitSourceBuffer(oneBufferDetails, oneWMABuffer);
			break;
		}
	case SFX_TWO:
		{
			voice->SubmitSourceBuffer(twoBufferDetails, twoWMABuffer);
			break;
		}
	case SFX_THREE:
		{
			voice->SubmitSourceBuffer(threeBufferDetails, threeWMABuffer);
			break;
		}
	default:
		break;
	}




	X3DAudioCalculate(audio3DHandle, &listener, emit,
		X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT,
		&dspSettings);
	
	voice->SetOutputMatrix(smSFX, 1, details.OutputFormat.Format.nChannels, dspSettings.pMatrixCoefficients);
	voice->SetFrequencyRatio(dspSettings.DopplerFactor);

	XAUDIO2_FILTER_PARAMETERS filterParameters = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI/6.0f * dspSettings.LPFDirectCoefficient), 1.0f };
	voice->SetFilterParameters(&filterParameters);
	
	voice->Start();
}