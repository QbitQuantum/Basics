void AudioInput::encodeAudioFrame() {
	int iArg;
	int i;
	float sum;
	short max;

	short *psSource;

	iFrameCounter++;

	if (! bRunning)
		return;

	sum=1.0f;
	max = 1;
	for (i=0;i<iFrameSize;i++) {
		sum += static_cast<float>(psMic[i] * psMic[i]);
		max = std::max(static_cast<short>(abs(psMic[i])), max);
	}
	dPeakMic = qMax(20.0f*log10f(sqrtf(sum / static_cast<float>(iFrameSize)) / 32768.0f), -96.0f);
	dMaxMic = max;

	if (psSpeaker && (iEchoChannels > 0)) {
		sum=1.0f;
		for (i=0;i<iFrameSize;i++)
			sum += static_cast<float>(psSpeaker[i] * psSpeaker[i]);
		dPeakSpeaker = qMax(20.0f*log10f(sqrtf(sum / static_cast<float>(iFrameSize)) / 32768.0f), -96.0f);
	} else {
		dPeakSpeaker = 0.0;
	}

	QMutexLocker l(&qmSpeex);
	resetAudioProcessor();

	speex_preprocess_ctl(sppPreprocess, SPEEX_PREPROCESS_GET_AGC_GAIN, &iArg);
	float gainValue = static_cast<float>(iArg);
	iArg = g.s.iNoiseSuppress - iArg;
	speex_preprocess_ctl(sppPreprocess, SPEEX_PREPROCESS_SET_NOISE_SUPPRESS, &iArg);

	if (sesEcho && psSpeaker) {
		speex_echo_cancellation(sesEcho, psMic, psSpeaker, psClean);
		speex_preprocess_run(sppPreprocess, psClean);
		psSource = psClean;
	} else {
		speex_preprocess_run(sppPreprocess, psMic);
		psSource = psMic;
	}

	sum=1.0f;
	for (i=0;i<iFrameSize;i++)
		sum += static_cast<float>(psSource[i] * psSource[i]);
	float micLevel = sqrtf(sum / static_cast<float>(iFrameSize));
	dPeakSignal = qMax(20.0f*log10f(micLevel / 32768.0f), -96.0f);

	spx_int32_t prob = 0;
	speex_preprocess_ctl(sppPreprocess, SPEEX_PREPROCESS_GET_PROB, &prob);
	fSpeechProb = static_cast<float>(prob) / 100.0f;

	// clean microphone level: peak of filtered signal attenuated by AGC gain
	dPeakCleanMic = qMax(dPeakSignal - gainValue, -96.0f);
	float level = (g.s.vsVAD == Settings::SignalToNoise) ? fSpeechProb : (1.0f + dPeakCleanMic / 96.0f);

	bool bIsSpeech = false;

	if (level > g.s.fVADmax)
		bIsSpeech = true;
	else if (level > g.s.fVADmin && bPreviousVoice)
		bIsSpeech = true;

	if (! bIsSpeech) {
		iHoldFrames++;
		if (iHoldFrames < g.s.iVoiceHold)
			bIsSpeech = true;
	} else {
		iHoldFrames = 0;
	}

	if (g.s.atTransmit == Settings::Continuous)
		bIsSpeech = true;
	else if (g.s.atTransmit == Settings::PushToTalk)
		bIsSpeech = g.s.uiDoublePush && ((g.uiDoublePush < g.s.uiDoublePush) || (g.tDoublePush.elapsed() < g.s.uiDoublePush));

	bIsSpeech = bIsSpeech || (g.iPushToTalk > 0);

	ClientUser *p = ClientUser::get(g.uiSession);
	if (g.s.bMute || ((g.s.lmLoopMode != Settings::Local) && p && (p->bMute || p->bSuppress)) || g.bPushToMute || (g.iTarget < 0)) {
		bIsSpeech = false;
	}

	if (bIsSpeech) {
		iSilentFrames = 0;
	} else {
		iSilentFrames++;
		if (iSilentFrames > 500)
			iFrameCounter = 0;
	}

	if (p) {
		if (! bIsSpeech)
			p->setTalking(Settings::Passive);
		else if (g.iTarget == 0)
			p->setTalking(Settings::Talking);
		else
			p->setTalking(Settings::Shouting);
	}

	if (g.s.bTxAudioCue && g.uiSession != 0) {
		AudioOutputPtr ao = g.ao;
		if (bIsSpeech && ! bPreviousVoice && ao)
			ao->playSample(g.s.qsTxAudioCueOn);
		else if (ao && !bIsSpeech && bPreviousVoice)
			ao->playSample(g.s.qsTxAudioCueOff);
	}

	if (! bIsSpeech && ! bPreviousVoice) {
		iBitrate = 0;

		if (g.s.iaeIdleAction != Settings::Nothing && ((tIdle.elapsed() / 1000000ULL) > g.s.iIdleTime)) {

			if (g.s.iaeIdleAction == Settings::Deafen && !g.s.bDeaf) {
				tIdle.restart();
				emit doDeaf();
			} else if (g.s.iaeIdleAction == Settings::Mute && !g.s.bMute) {
				tIdle.restart();
				emit doMute();
			}
		}

		spx_int32_t increment = 0;
		speex_preprocess_ctl(sppPreprocess, SPEEX_PREPROCESS_SET_AGC_INCREMENT, &increment);
		return;
	} else {
		spx_int32_t increment = 12;
		speex_preprocess_ctl(sppPreprocess, SPEEX_PREPROCESS_SET_AGC_INCREMENT, &increment);
	}

	if (bIsSpeech && !bPreviousVoice) {
		bResetEncoder = true;
	}

	tIdle.restart();

	EncodingOutputBuffer buffer;
	Q_ASSERT(buffer.size() >= static_cast<size_t>(iAudioQuality / 100 * iAudioFrames / 8));
	
	int len = 0;

	bool encoded = true;
	if (!selectCodec())
		return;

	if (umtType == MessageHandler::UDPVoiceCELTAlpha || umtType == MessageHandler::UDPVoiceCELTBeta) {
		len = encodeCELTFrame(psSource, buffer);
		if (len <= 0) {
			iBitrate = 0;
			qWarning() << "encodeCELTFrame failed" << iBufferedFrames << iFrameSize << len;
			return;
		}
		++iBufferedFrames;
	} else if (umtType == MessageHandler::UDPVoiceOpus) {
		encoded = false;
		opusBuffer.insert(opusBuffer.end(), psSource, psSource + iFrameSize);
		++iBufferedFrames;

		if (!bIsSpeech || iBufferedFrames >= iAudioFrames) {
			if (iBufferedFrames < iAudioFrames) {
				// Stuff frame to framesize if speech ends and we don't have enough audio
				// this way we are guaranteed to have a valid framecount and won't cause
				// a codec configuration switch by suddenly using a wildly different
				// framecount per packet.
				const int missingFrames = iAudioFrames - iBufferedFrames;
				opusBuffer.insert(opusBuffer.end(), iFrameSize * missingFrames, 0);
				iBufferedFrames += missingFrames;
				iFrameCounter += missingFrames;
			}
			
			Q_ASSERT(iBufferedFrames == iAudioFrames);

			len = encodeOpusFrame(&opusBuffer[0], iBufferedFrames * iFrameSize, buffer);
			opusBuffer.clear();
			if (len <= 0) {
				iBitrate = 0;
				qWarning() << "encodeOpusFrame failed" << iBufferedFrames << iFrameSize << len;
				iBufferedFrames = 0; // These are lost. Make sure not to mess up our sequence counter next flushCheck.
				return;
			}
			encoded = true;
		}
	}

	if (encoded) {
		flushCheck(QByteArray(reinterpret_cast<char *>(&buffer[0]), len), !bIsSpeech);
	}

	if (! bIsSpeech)
		iBitrate = 0;

	bPreviousVoice = bIsSpeech;
}