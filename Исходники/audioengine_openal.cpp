void * LLAudioEngine_OpenAL::windDSP(void *newbuffer, int length)
{
	// *NOTE: This function gets called a *lot*.  
	// Keep performance in mind if you mess with this.
	// newbuffer = the buffer being constructed
	// length = length in samples of the buffer


	//clear the buffer 
	memset(newbuffer, 0, length*mBytesPerSample);

 	// This turns off wind synth if it is muted or very very low volume
 	if (mTargetGain < 0.0005f)
 	{
		llinfos << "Wind off" << llendl;
 		return newbuffer;
 	}
 
 	static const U8  SUBSAMPLES = 2;
 	static const F32 FILTER_SAMPLE_PERIOD = (F32)SUBSAMPLES / float(mSampleRate);
 	static const F32 BANDWIDTH = 50.0f;
 	static const F32 B2 = expf(-F_TWO_PI * BANDWIDTH * FILTER_SAMPLE_PERIOD);
 
 	static F32 pinking_buf0 = 0.0f;
 	static F32 pinking_buf1 = 0.0f;
 	static F32 pinking_buf2 = 0.0f;
 	static F32 Y0 = 0.0f;
 	static F32 Y1 = 0.0f;
 	static F32 last_sample = 0.0f;
 	static F32 current_freq = 0.0f;
 	static F32 current_gain = 0.0f;
 	static F32 current_pan_gain_r = 0.0f;
 
  	F32 a0 = 0.0f, b1 = 0.0f;
  
  	U8 *cursamplep = (U8*)newbuffer;

	//we assume 16-bit samples, because the ALUT specification maxes out there
 	U8 wordsize = 2;
  
 	bool interp_freq = false; 
 
 	//if the frequency isn't changing much, we don't need to interpolate in the inner loop
 	if (llabs(mTargetFreq - current_freq) > 200.0f)
 	{
 		interp_freq = true;
 	}
 	else
 	{
 		// calculate resonant filter coefficients
 		current_freq = mTargetFreq;
 		b1 = (-4.0f * B2) / (1.0f + B2) * cosf(F_TWO_PI * (current_freq * FILTER_SAMPLE_PERIOD));
 		a0 = (1.0f - B2) * sqrtf(1.0f - (b1 * b1) / (4.0f * B2));
 	}
 
 	while (length)
 	{
 		F32 next_sample;
  
 	    // Start with white noise [-16384, 16383]
 		next_sample = (F32)rand() * (1.0f / (F32)(RAND_MAX / (U16_MAX / 4))) + (S16_MIN / 4);
  									 
 		// Apply a pinking filter
 		// Magic numbers taken from PKE method at http://www.firstpr.com.au/dsp/pink-noise/
 		pinking_buf0 = pinking_buf0 * 0.99765f + next_sample * 0.0990460f;
 		pinking_buf1 = pinking_buf1 * 0.96300f + next_sample * 0.2965164f;
 		pinking_buf2 = pinking_buf2 * 0.57000f + next_sample * 1.0526913f;
 		
 		next_sample = pinking_buf0 + pinking_buf1 + pinking_buf2 + next_sample * 0.1848f;
  
 		if (interp_freq)
 		{
 			// calculate resonant filter coefficients
 			current_freq = (0.999f * current_freq) + (0.001f * mTargetFreq);
 			b1 = (-4.0f * B2) / (1.0f + B2) * cosf(F_TWO_PI * (current_freq * FILTER_SAMPLE_PERIOD));
 			a0 = (1.0f - B2) * sqrtf(1.0f - (b1 * b1) / (4.0f * B2));
 		}
 
 		// Apply a resonant low-pass filter on the pink noise
		next_sample = ( a0 * next_sample - b1 * Y0 - B2 * Y1 );
  
		Y1 = Y0;
		Y0 = next_sample;
 
 		current_gain = (0.999f * current_gain) + (0.001f * mTargetGain);
 		current_pan_gain_r = (0.999f * current_pan_gain_r) + (0.001f * mTargetPanGainR);
 		
 	    next_sample *= current_gain;
 		F32 delta = (next_sample - last_sample) / (F32)SUBSAMPLES;
  		
 		S32	sample_left;
 		S32	sample_right;
 
 		// Mix into the audio buffer, clipping if necessary for 16-bit mix buffers.
 		// *TODO: Should do something more intelligent like reducing wind gain to avoid clipping
 		for (int i=SUBSAMPLES; i && length; --i, --length) 
 		{
 			last_sample = last_sample + delta;
 			sample_right = (S32)(last_sample * current_pan_gain_r);
 			sample_left = (S32)(last_sample - sample_right);
 
			*(S16*)cursamplep = llclamp(sample_left, S16_MIN, S16_MAX);
 			cursamplep += wordsize;
 
 			*(S16*)cursamplep = llclamp(sample_right, S16_MIN, S16_MAX);
 			cursamplep += wordsize;
 		}
 	}		  
  	return newbuffer;

}