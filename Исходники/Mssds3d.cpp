M3D_RESULT __stdcall M3D_activate(int enable)
{
	if(enable)
	{
		if(pXAudio2)
			return M3D_ALREADY_STARTED;

		char ReverbVolumeText[256];
		if(!GothicReadIniString("PARAMETERS", "ReverbVolume", "3.0", ReverbVolumeText, 256, "SystemPack.ini"))
			GothicWriteIniString("PARAMETERS", "ReverbVolume", "3.0", "SystemPack.ini");
		ReverbVolume = (float)atof(ReverbVolumeText);

		HRESULT hResult = S_OK;
		if(FAILED(hResult = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		{
#ifdef LOG
			fprintf(Log, "M3D_activate XAudio2Create failed %d\n", hResult);
#endif
			return M3D_NOT_INIT;
		}

		memset(&deviceDetails, 0, sizeof(XAUDIO2_DEVICE_DETAILS));
		if(FAILED(hResult = pXAudio2->GetDeviceDetails(0, &deviceDetails)))
		{
			pXAudio2->Release();
			pXAudio2 = NULL;
#ifdef LOG
			fprintf(Log, "M3D_activate GetDeviceDetails failed %d\n", hResult);
#endif
			return M3D_NOT_INIT;
		}

		UINT32 SampleRate = MIN(MAX(deviceDetails.OutputFormat.Format.nSamplesPerSec, XAUDIO2FX_REVERB_MIN_FRAMERATE), XAUDIO2FX_REVERB_MAX_FRAMERATE);
		if(FAILED(hResult = pXAudio2->CreateMasteringVoice(&pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, SampleRate)))
		{
			pXAudio2->Release();
			pXAudio2 = NULL;
#ifdef LOG
			fprintf(Log, "M3D_activate CreateMasteringVoice failed %d\n", hResult);
#endif
			return M3D_NOT_INIT;
		}

		X3DAudioInitialize(deviceDetails.OutputFormat.dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, X3DAudioInstance);
		
		memset(&Listener, 0, sizeof(M3D_Listener));
		Listener.pMasterVoice = pMasterVoice;
		Listener.Z_face = 1.0f;
		Listener.Y_up = 1.0f;
		UpdateAllSamples();

		X3DDSPSettings.SrcChannelCount = 1;
		X3DDSPSettings.DstChannelCount = deviceDetails.OutputFormat.Format.nChannels;
		X3DDSPSettings.pMatrixCoefficients = new FLOAT32[deviceDetails.OutputFormat.Format.nChannels];
		memset(X3DDSPSettings.pMatrixCoefficients, 0, sizeof(FLOAT32) * deviceDetails.OutputFormat.Format.nChannels);

		Samples = new M3D_Source[MAX_SAMPLES_COUNT];
		memset(Samples, 0, sizeof(M3D_Source) * MAX_SAMPLES_COUNT);
		for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
		{
			SetSampleDefaults(&Samples[i]);
			if(FAILED(hResult = XAudio2CreateReverb(&Samples[i].pReverbEffect)))
			{
				pMasterVoice->DestroyVoice();
				pMasterVoice = NULL;
				pXAudio2->Release();
				pXAudio2 = NULL;
#ifdef LOG
				fprintf(Log, "M3D_activate XAudio2CreateReverb failed %d\n", hResult);
#endif
				return M3D_NOT_INIT;
			}

			XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { Samples[i].pReverbEffect, TRUE, 1 } };
			XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

			if(FAILED(hResult = pXAudio2->CreateSubmixVoice(&Samples[i].pSubmixVoice, 1, SampleRate, 0, 0, NULL, Samples[i].pReverbEffect ? &effectChain : NULL)))
			{
				Samples[i].pReverbEffect->Release();
				Samples[i].pReverbEffect = NULL;
				pMasterVoice->DestroyVoice();
				pMasterVoice = NULL;
				pXAudio2->Release();
				pXAudio2 = NULL;
#ifdef LOG
				fprintf(Log, "M3D_activate CreateSubmixVoice(%d) failed %d\n", deviceDetails.OutputFormat.Format.nSamplesPerSec, hResult);
#endif
				return M3D_NOT_INIT;
			}

			XAUDIO2FX_REVERB_PARAMETERS native;
			ReverbConvertI3DL2ToNative( &ROOM_PRESET_PARAMS[Current_EAX_room_type], &native );
			Samples[i].pSubmixVoice->SetEffectParameters(0, &native, sizeof(native));
		}
	}
	else
	{
		if(!pXAudio2)
			return M3D_NOT_INIT;

		if(Samples)
		{
			for(int i = 0; i < MAX_SAMPLES_COUNT; i++)
			{
				M3D_end_3D_sample((M3D_SAMPLE)&Samples[i]);

				if(Samples[i].pSubmixVoice)
				{
					Samples[i].pSubmixVoice->DestroyVoice();
					Samples[i].pSubmixVoice = NULL;
				}

				if(Samples[i].pReverbEffect)
				{
					Samples[i].pReverbEffect->Release();
					Samples[i].pReverbEffect = NULL;
				}
			}

			delete[] Samples;
			Samples = NULL;
		}

		if(pMasterVoice)
		{
			pMasterVoice->DestroyVoice();
			pMasterVoice = NULL;
		}
		if(X3DDSPSettings.pMatrixCoefficients)
		{
			delete[] X3DDSPSettings.pMatrixCoefficients;
			X3DDSPSettings.pMatrixCoefficients = NULL;
		}
		if(pXAudio2)
		{
			pXAudio2->Release();
			pXAudio2 = NULL;
		}
	}
#ifdef LOG
	fprintf(Log, "M3D_activate(%d) ok\n", enable);
#endif
	return M3D_NOERR;
}