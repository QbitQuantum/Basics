void AudioEffectDistortionInstance::process(const AudioFrame *p_src_frames, AudioFrame *p_dst_frames, int p_frame_count) {

	const float *src = (const float *)p_src_frames;
	float *dst = (float *)p_dst_frames;

	//float lpf_c=expf(-2.0*Math_PI*keep_hf_hz.get()/(mix_rate*(float)OVERSAMPLE));
	float lpf_c = expf(-2.0 * Math_PI * base->keep_hf_hz / (AudioServer::get_singleton()->get_mix_rate()));
	float lpf_ic = 1.0 - lpf_c;

	float drive_f = base->drive;
	float pregain_f = Math::db2linear(base->pre_gain);
	float postgain_f = Math::db2linear(base->post_gain);

	float atan_mult = pow(10, drive_f * drive_f * 3.0) - 1.0 + 0.001;
	float atan_div = 1.0 / (atanf(atan_mult) * (1.0 + drive_f * 8));

	float lofi_mult = powf(2.0, 2.0 + (1.0 - drive_f) * 14); //goes from 16 to 2 bits

	for (int i = 0; i < p_frame_count * 2; i++) {

		float out = undenormalise(src[i] * lpf_ic + lpf_c * h[i & 1]);
		h[i & 1] = out;
		float a = out;
		float ha = src[i] - out; //high freqs
		a *= pregain_f;

		switch (base->mode) {

			case AudioEffectDistortion::MODE_CLIP: {

				a = powf(a, 1.0001 - drive_f);
				if (a > 1.0)
					a = 1.0;
				else if (a < (-1.0))
					a = -1.0;

			} break;
			case AudioEffectDistortion::MODE_ATAN: {

				a = atanf(a * atan_mult) * atan_div;

			} break;
			case AudioEffectDistortion::MODE_LOFI: {

				a = floorf(a * lofi_mult + 0.5) / lofi_mult;

			} break;
			case AudioEffectDistortion::MODE_OVERDRIVE: {

				const double x = a * 0.686306;
				const double z = 1 + exp(sqrt(fabs(x)) * -0.75);
				a = (expf(x) - expf(-x * z)) / (expf(x) + expf(-x));
			} break;
			case AudioEffectDistortion::MODE_WAVESHAPE: {
				float x = a;
				float k = 2 * drive_f / (1.00001 - drive_f);

				a = (1.0 + k) * x / (1.0 + k * fabsf(x));

			} break;
		}

		dst[i] = a * postgain_f + ha;
	}
}