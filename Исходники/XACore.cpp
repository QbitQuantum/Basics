		//--- Calculate and apply 3D audio DSP settings to a voice.
		//--- handles output matrix, doppler effect and filter flags.
		//--- Only applies those settings compatible with the supplied flags and source voice creation flags.
		void XACore::Apply3D(IXAudio2SourceVoice *aVoice, const X3DAUDIO_EMITTER* anEmitter, const X3DAUDIO_LISTENER* aListener, const unsigned int flags) const
		{
			// Guard against invalid initialisation.
			if (mStatus != OK) return;

			// get relevant details from the source voice.
			XAUDIO2_VOICE_DETAILS voiceDetails;
			aVoice->GetVoiceDetails(&voiceDetails);
			// Set up DSP settings.
			X3DAUDIO_DSP_SETTINGS DSPSettings;
			SecureZeroMemory(&DSPSettings, sizeof(X3DAUDIO_DSP_SETTINGS));
			DSPSettings.SrcChannelCount = voiceDetails.InputChannels;
			DSPSettings.DstChannelCount = mChannelCount;
			if (flags & X3DAUDIO_CALCULATE_MATRIX) {
				// only allocate matrix space if calculate flag is set.
				DSPSettings.pMatrixCoefficients = new FLOAT32[DSPSettings.SrcChannelCount * DSPSettings.DstChannelCount];
			}

			X3DAudioCalculate(m3DHandle, aListener, anEmitter, flags, &DSPSettings);

			// Apply the DSP settings identified by the flags to the supplied voice.
			// check that the voice has the relevant capability through its creation flags.
			if (flags & X3DAUDIO_CALCULATE_MATRIX) {
				aVoice->SetOutputMatrix(NULL, DSPSettings.SrcChannelCount, DSPSettings.DstChannelCount, DSPSettings.pMatrixCoefficients);
				// Free output matrix space that was allocated.
				delete[] DSPSettings.pMatrixCoefficients;
			}
			if ((flags & X3DAUDIO_CALCULATE_DOPPLER) && !(voiceDetails.CreationFlags & XAUDIO2_VOICE_NOPITCH)) {
				aVoice->SetFrequencyRatio(DSPSettings.DopplerFactor);
			}
			if ((flags & X3DAUDIO_CALCULATE_LPF_DIRECT) && (voiceDetails.CreationFlags & XAUDIO2_VOICE_USEFILTER)) {
				XAUDIO2_FILTER_PARAMETERS FilterParameters = {
					LowPassFilter,
					2.0f * sinf(X3DAUDIO_PI / 6.0f * DSPSettings.LPFDirectCoefficient),
					1.0f
				};
				aVoice->SetFilterParameters(&FilterParameters);
			}
		} // end Apply3D function.