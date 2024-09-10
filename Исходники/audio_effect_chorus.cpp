void AudioEffectChorusInstance::_process_chunk(const AudioFrame *p_src_frames, AudioFrame *p_dst_frames, int p_frame_count) {

	//fill ringbuffer
	for (int i = 0; i < p_frame_count; i++) {
		audio_buffer.write[(buffer_pos + i) & buffer_mask] = p_src_frames[i];
		p_dst_frames[i] = p_src_frames[i] * base->dry;
	}

	float mix_rate = AudioServer::get_singleton()->get_mix_rate();

	/* process voices */
	for (int vc = 0; vc < base->voice_count; vc++) {

		AudioEffectChorus::Voice &v = base->voice[vc];

		double time_to_mix = (float)p_frame_count / mix_rate;
		double cycles_to_mix = time_to_mix * v.rate;

		unsigned int local_rb_pos = buffer_pos;
		AudioFrame *dst_buff = p_dst_frames;
		AudioFrame *rb_buff = audio_buffer.ptrw();

		double delay_msec = v.delay;
		unsigned int delay_frames = Math::fast_ftoi((delay_msec / 1000.0) * mix_rate);
		float max_depth_frames = (v.depth / 1000.0) * mix_rate;

		uint64_t local_cycles = cycles[vc];
		uint64_t increment = llrint(cycles_to_mix / (double)p_frame_count * (double)(1 << AudioEffectChorus::CYCLES_FRAC));

		//check the LFO doesn't read ahead of the write pos
		if ((((unsigned int)max_depth_frames) + 10) > delay_frames) { //10 as some threshold to avoid precision stuff
			delay_frames += (int)max_depth_frames - delay_frames;
			delay_frames += 10; //threshold to avoid precision stuff
		}

		//low pass filter
		if (v.cutoff == 0)
			continue;
		float auxlp = expf(-2.0 * Math_PI * v.cutoff / mix_rate);
		float c1 = 1.0 - auxlp;
		float c2 = auxlp;
		AudioFrame h = filter_h[vc];
		if (v.cutoff >= AudioEffectChorus::MS_CUTOFF_MAX) {
			c1 = 1.0;
			c2 = 0.0;
		}

		//vol modifier

		AudioFrame vol_modifier = AudioFrame(base->wet, base->wet) * Math::db2linear(v.level);
		vol_modifier.l *= CLAMP(1.0 - v.pan, 0, 1);
		vol_modifier.r *= CLAMP(1.0 + v.pan, 0, 1);

		for (int i = 0; i < p_frame_count; i++) {

			/** COMPUTE WAVEFORM **/

			float phase = (float)(local_cycles & AudioEffectChorus::CYCLES_MASK) / (float)(1 << AudioEffectChorus::CYCLES_FRAC);

			float wave_delay = sinf(phase * 2.0 * Math_PI) * max_depth_frames;

			int wave_delay_frames = lrint(floor(wave_delay));
			float wave_delay_frac = wave_delay - (float)wave_delay_frames;

			/** COMPUTE RINGBUFFER POS**/

			unsigned int rb_source = local_rb_pos;
			rb_source -= delay_frames;

			rb_source -= wave_delay_frames;

			/** READ FROM RINGBUFFER, LINEARLY INTERPOLATE */

			AudioFrame val = rb_buff[rb_source & buffer_mask];
			AudioFrame val_next = rb_buff[(rb_source - 1) & buffer_mask];

			val += (val_next - val) * wave_delay_frac;

			val = val * c1 + h * c2;
			h = val;

			/** MIX VALUE TO OUTPUT **/

			dst_buff[i] += val * vol_modifier;

			local_cycles += increment;
			local_rb_pos++;
		}

		filter_h[vc] = h;
		cycles[vc] += Math::fast_ftoi(cycles_to_mix * (double)(1 << AudioEffectChorus::CYCLES_FRAC));
	}

	buffer_pos += p_frame_count;
}