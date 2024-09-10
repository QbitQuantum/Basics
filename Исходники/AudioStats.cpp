void AudioStats::on_Tick_timeout() {
	AudioInputPtr ai = g.ai;

	if (ai.get() == NULL || ! ai->sppPreprocess)
		return;

	bool nTalking = ai->isTransmitting();

	QString txt;

	txt.sprintf("%06.2f dB",ai->dPeakMic);
	qlMicLevel->setText(txt);

	txt.sprintf("%06.2f dB",ai->dPeakSpeaker);
	qlSpeakerLevel->setText(txt);

	txt.sprintf("%06.2f dB",ai->dPeakSignal);
	qlSignalLevel->setText(txt);

	spx_int32_t ps_size = 0;
	speex_preprocess_ctl(ai->sppPreprocess, SPEEX_PREPROCESS_GET_PSD_SIZE, &ps_size);

	STACKVAR(spx_int32_t, noise, ps_size);
	STACKVAR(spx_int32_t, ps, ps_size);

	speex_preprocess_ctl(ai->sppPreprocess, SPEEX_PREPROCESS_GET_PSD, ps);
	speex_preprocess_ctl(ai->sppPreprocess, SPEEX_PREPROCESS_GET_NOISE_PSD, noise);

	float s = 0.0f;
	float n = 0.0001f;

	int start = (ps_size * 300) / SAMPLE_RATE;
	int stop = (ps_size * 2000) / SAMPLE_RATE;

	for (int i=start;i<stop;i++) {
		s += sqrtf(static_cast<float>(ps[i]));
		n += sqrtf(static_cast<float>(noise[i]));
	}

	txt.sprintf("%06.3f",s / n);
	qlMicSNR->setText(txt);

	spx_int32_t v;
	speex_preprocess_ctl(ai->sppPreprocess, SPEEX_PREPROCESS_GET_AGC_GAIN, &v);
	float fv = powf(10.0f, (static_cast<float>(v) / 20.0f));
	txt.sprintf("%03.0f%%",100.0f / fv);
	qlMicVolume->setText(txt);

	txt.sprintf("%03.0f%%",ai->fSpeechProb * 100.0f);
	qlSpeechProb->setText(txt);

	txt.sprintf("%04.1f kbit/s",static_cast<float>(ai->iBitrate) / 1000.0f);
	qlBitrate->setText(txt);

	if (nTalking != bTalking) {
		bTalking = nTalking;
		QFont f = qlSpeechProb->font();
		f.setBold(bTalking);
		qlSpeechProb->setFont(f);
	}

	if (g.uiDoublePush > 1000000)
		txt = tr(">1000 ms");
	else
		txt.sprintf("%04llu ms",g.uiDoublePush / 1000);
	qlDoublePush->setText(txt);

	abSpeech->iBelow = iroundf(g.s.fVADmin * 32767.0f + 0.5f);
	abSpeech->iAbove = iroundf(g.s.fVADmax * 32767.0f + 0.5f);

	if (g.s.vsVAD == Settings::Amplitude) {
		abSpeech->iValue = iroundf((32767.f/96.0f) * (96.0f + ai->dPeakCleanMic) + 0.5f);
	} else {
		abSpeech->iValue = iroundf(ai->fSpeechProb * 32767.0f + 0.5f);
	}

	abSpeech->update();

	anwNoise->update();
	if (aewEcho)
		aewEcho->update();
}