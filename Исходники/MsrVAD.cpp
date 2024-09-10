	void MsrVAD::process(float* fft_ptr){
		const float a00 = 1.0f - m_VAD_A01;
		const float a11 = 1.0f - m_VAD_A10;
		const float a00f = 1.0f - m_VAD_A01f;
		const float a11f = 1.0f - m_VAD_A10f;
		// per bin and per frame soft VAD
		float likemean = 0.0f;
		float likelogmean = 0.0f;
		for (unsigned int u = m_MecBegBin; u <= m_MecEndBin; u++) { // optimized for non-zero frequency bins
			// calculate signal power
			float MicRe = fft_ptr[u];
			float MicIm = fft_ptr[TWO_FRAME_SIZE - u];
			SignalPower[u] = MicRe * MicRe + MicIm * MicIm;

			// update the prior and posterios SNRs
			posteriorSNR_NS[u] = SignalPower[u] / (NoiseModel[u] + DIV_BY_ZERO_PREVENTION);
			float MLPriorSNR = SpeechModel[u] / (NoiseModel[u] + DIV_BY_ZERO_PREVENTION) - 1.0f;
			if (MLPriorSNR < 0.0f) MLPriorSNR = 0.0f;
			priorSNR[u] = m_VAD_SNR_SMOOTHER * priorSNR[u] + (1.0f - m_VAD_SNR_SMOOTHER) * MLPriorSNR;

			// Speech presence likelihood ratio
			float vRatio = posteriorSNR_NS[u] * priorSNR[u] / (priorSNR[u] + 1.0f);
			if (vRatio > 700.0f) vRatio = 700.0f;
			float likelihoodratio = 1.0f / (priorSNR[u] + 1.0f) * expf(vRatio);
			if (likelihoodratio > 1000.0f) likelihoodratio = 1000.0f;
			else if (likelihoodratio < LOG_LIKELIHOOD_MINVAL) likelihoodratio = LOG_LIKELIHOOD_MINVAL;

			// Smooth speech presence probability per bin
			speechPresenceLR[u] = likelihoodratio * (m_VAD_A01 + a11 * speechPresenceLR[u]) / (a00 + m_VAD_A10 * speechPresenceLR[u]); // HMM for changing the state
			speechPresenceProb[u] = speechPresenceLR[u] / (1.0f + speechPresenceLR[u]);
			if (speechPresenceProb[u] < 0.0f) speechPresenceProb[u] = 0.0f;
			else if (speechPresenceProb[u] > 1.0f) speechPresenceProb[u] = 1.0f;

			// Note that likelogmean is only calculated on a subset of the frequency bins
			if (u >= m_LogLikelihoodBegBin && u <= m_LogLikelihoodEndBin) {
				likemean += likelihoodratio;
				likelogmean += logf(likelihoodratio);
			}
		}
		likemean /= (m_LogLikelihoodEndBin - m_LogLikelihoodBegBin + 1);
		likelogmean /= (m_LogLikelihoodEndBin - m_LogLikelihoodBegBin + 1);

		// Speech presence likelihood ratio for the frame
		float curFrameLR = expf(likelogmean);
		curFrameLR = 0.8f * curFrameLR + (1 - 0.8f) * likemean;
		if (curFrameLR > 1000.0f) curFrameLR = 1000.0f;

		// Smooth speech presence probability per frame
		FrameLR = curFrameLR * (m_VAD_A01f + a11f * FrameLR) / (a00f + m_VAD_A10f * FrameLR); // HMM for changing the state
		float framePresProb = FrameLR / (1.0f + FrameLR);
		if (framePresProb < 0.0f) framePresProb = 0.0f;
		else if (framePresProb > 1.0f) framePresProb = 1.0f;
		m_fFramePresProb = framePresProb;

		// precise noise model
		if (nFrame > 1) {
			if (nFrame < m_VAD_TAUN / m_MecFrameDuration) {
				for (unsigned int u = m_MecBegBin; u <= m_MecEndBin; u++) {
					float alphaN = 1.0f / nFrame;
					NoiseModel[u] = (1.0f - alphaN) * NoiseModel[u] + alphaN * SignalPower[u];
				}
			}
			else {
				for (unsigned int u = m_MecBegBin; u <= m_MecEndBin; u++) {
					float alphaN = (1.0f - speechPresenceProb[u]) * (1.0f - framePresProb) * m_MecFrameDuration / m_VAD_TAUN;
					NoiseModel[u] = (1.0f - alphaN) * NoiseModel[u] + alphaN * SignalPower[u];
				}
			}

			// update the speech model
			for (unsigned int u = m_MecBegBin; u <= m_MecEndBin; u++) {
				float alphaS = speechPresenceProb[u] * framePresProb * m_MecFrameDuration / m_VAD_TAUS;
				SpeechModel[u] = (1.0f - alphaS) * SpeechModel[u] + alphaS * SignalPower[u];
			}
		}
		nFrame++;

		// Update the prior SNR
		m_fEnergy = 0.0f;
		float fSNRam = 0.0f;
		float fSNR = 0.0f;
		for (unsigned int u = m_MecBegBin; u <= m_MecEndBin; u++) {
			if (u >= m_LogLikelihoodBegBin && u <= m_LogLikelihoodEndBin) {
				fSNR = SignalPower[u] / (NoiseModel[u] + 1e-10f);
				fSNR = std::max(1.0f, std::min(20000.0f, fSNR));
				fSNRam += fSNR;
			}

			// Compute the suppression rule - simple Wiener
			float Gain = priorSNR[u] / (priorSNR[u] + 1.0f);
			// update the prior SNR
			MasterSignalPowerOverNoiseModel[u] = SignalPower[u] / (NoiseModel[u] + DIV_BY_ZERO_PREVENTION);
			float alphaS = speechPresenceProb[u] * framePresProb * m_MecFrameDuration / m_VAD_TAUS;
			priorSNR[u] = (1.0f - alphaS) * priorSNR[u] + alphaS *  Gain * Gain * MasterSignalPowerOverNoiseModel[u];
			m_fEnergy += SignalPower[u];
			q30MasterSpeechPresenceProb[u] = (int)((float)(1u << 30) * framePresProb * speechPresenceProb[u]);
		}
		m_fEnergy /= (m_MecEndBin - m_MecBegBin + 1);
		fSNRam /= (m_MecEndBin - m_MecBegBin + 1);
		float beta = m_MecFrameDuration*framePresProb / 10.0f;  // time constant in seconds
		m_fSNR = (1.0f - beta) * m_fSNR + beta * fSNRam;
	}