void Float32ToNativeInt32( const float *src, int *dst, unsigned int numToConvert )
{
	const float *src0 = src;
	int *dst0 = dst;
	unsigned int count = numToConvert;
	
	if (count >= 4) {
		// vector -- requires 4+ samples
		ROUNDMODE_NEG_INF
		const __m128 vround = (const __m128) { 0.5f, 0.5f, 0.5f, 0.5f };
		const __m128 vmin = (const __m128) { -2147483648.0f, -2147483648.0f, -2147483648.0f, -2147483648.0f };
		const __m128 vmax = (const __m128) { kMaxFloat32, kMaxFloat32, kMaxFloat32, kMaxFloat32  };
		const __m128 vscale = (const __m128) { 2147483648.0f, 2147483648.0f, 2147483648.0f, 2147483648.0f  };
		__m128 vf0;
		__m128i vi0;
	
#define F32TOLE32(x) \
		vf##x = _mm_mul_ps(vf##x, vscale);			\
		vf##x = _mm_add_ps(vf##x, vround);			\
		vf##x = _mm_max_ps(vf##x, vmin);			\
		vf##x = _mm_min_ps(vf##x, vmax);			\
		vi##x = _mm_cvtps_epi32(vf##x);			\

		int falign = (uintptr_t)src & 0xF;
		int ialign = (uintptr_t)dst & 0xF;
	
		if (falign != 0 || ialign != 0) {
			// do one unaligned conversion
			vf0 = _mm_loadu_ps(src);
			F32TOLE32(0)
			_mm_storeu_si128((__m128i *)dst, vi0);
			
			// and advance such that the destination ints are aligned
			unsigned int n = (16 - ialign) / 4;
			src += n;
			dst += n;
			count -= n;

			falign = (uintptr_t)src & 0xF;
			if (falign != 0) {
				// unaligned loads, aligned stores
				while (count >= 4) {
					vf0 = _mm_loadu_ps(src);
					F32TOLE32(0)
					_mm_store_si128((__m128i *)dst, vi0);
					src += 4;
					dst += 4;
					count -= 4;
				}
				goto VectorCleanup;
			}
		}
	
		while (count >= 4) {
			vf0 = _mm_load_ps(src);
			F32TOLE32(0)
			_mm_store_si128((__m128i *)dst, vi0);
			
			src += 4;
			dst += 4;
			count -= 4;
		}
VectorCleanup:
		if (count > 0) {
			// unaligned cleanup -- just do one unaligned vector at the end
			src = src0 + numToConvert - 4;
			dst = dst0 + numToConvert - 4;
			vf0 = _mm_loadu_ps(src);
			F32TOLE32(0)
			_mm_storeu_si128((__m128i *)dst, vi0);
		}
		RESTORE_ROUNDMODE
		return;
	}
	
	// scalar for small numbers of samples
	if (count > 0) {
		double scale = 2147483648.0, round = 0.5, max32 = 2147483648.0 - 1.0 - 0.5, min32 = 0.;
		ROUNDMODE_NEG_INF
		
		while (count-- > 0) {
			double f0 = *src++;
			f0 = f0 * scale + round;
			int i0 = FloatToInt(f0, min32, max32);
			*dst++ = i0;
		}
		RESTORE_ROUNDMODE
	}
}


void NativeInt32ToFloat32( const int *src, float *dst, unsigned int numToConvert )
{
	const int *src0 = src;
	float *dst0 = dst;
	unsigned int count = numToConvert;

	if (count >= 4) {
		// vector -- requires 4+ samples
#define LEI32TOF32(x) \
	vf##x = _mm_cvtepi32_ps(vi##x); \
	vf##x = _mm_mul_ps(vf##x, vscale); \
		
		const __m128 vscale = (const __m128) { 1.0/2147483648.0f, 1.0/2147483648.0f, 1.0/2147483648.0f, 1.0/2147483648.0f  };
		__m128 vf0;
		__m128i vi0;

		int ialign = (uintptr_t)src & 0xF;
		int falign = (uintptr_t)dst & 0xF;
	
		if (falign != 0 || ialign != 0) {
			// do one unaligned conversion
			vi0 = _mm_loadu_si128((__m128i const *)src);
			LEI32TOF32(0)
			_mm_storeu_ps(dst, vf0);
			
			// and advance such that the destination floats are aligned
			unsigned int n = (16 - falign) / 4;
			src += n;
			dst += n;
			count -= n;

			ialign = (uintptr_t)src & 0xF;
			if (ialign != 0) {
				// unaligned loads, aligned stores
				while (count >= 4) {
					vi0 = _mm_loadu_si128((__m128i const *)src);
					LEI32TOF32(0)
					_mm_store_ps(dst, vf0);
					src += 4;
					dst += 4;
					count -= 4;
				}
				goto VectorCleanup;
			}
		}
	
		// aligned loads, aligned stores
		while (count >= 4) {
			vi0 = _mm_load_si128((__m128i const *)src);
			LEI32TOF32(0)
			_mm_store_ps(dst, vf0);
			src += 4;
			dst += 4;
			count -= 4;
		}
		
VectorCleanup:
		if (count > 0) {
			// unaligned cleanup -- just do one unaligned vector at the end
			src = src0 + numToConvert - 4;
			dst = dst0 + numToConvert - 4;
			vi0 = _mm_loadu_si128((__m128i const *)src);
			LEI32TOF32(0)
			_mm_storeu_ps(dst, vf0);
		}
		return;
	}
	// scalar for small numbers of samples
	if (count > 0) {
		double scale = 1./2147483648.0f;
		while (count-- > 0) {
			int i = *src++;
			double f = (double)i * scale;
			*dst++ = f;
		}
	}
}

int alsa_set_hwparams(alsa_dev_t *dev, snd_pcm_t *handle, snd_pcm_hw_params_t *params, snd_pcm_access_t access)
{
  unsigned int rrate;
  snd_pcm_uframes_t size;
  int err, dir;
  
  /* choose all parameters */
  err = snd_pcm_hw_params_any(handle, params);
  if (err < 0) {
    printf("Broken configuration for playback: no configurations available: %s\n", snd_strerror(err));
    return err;
  }
  
  /* set the interleaved read/write format */
  err = snd_pcm_hw_params_set_access(handle, params, access);
  if (err < 0) {
    printf("Access type not available for playback: %s\n", snd_strerror(err));
    return err;
  }
  /* set the sample format */
  err = snd_pcm_hw_params_set_format(handle, params, dev->format);
  if (err < 0) {
    printf("Sample format not available for playback: %s\n", snd_strerror(err));
    return err;
  }
  /* set the count of channels */
  err = snd_pcm_hw_params_set_channels(handle, params, dev->channels);
  if (err < 0) {
    printf("Channels count (%d) not available for playbacks: %s\n", dev->channels, snd_strerror(err));
    return err;
  }
  /* set the stream rate */
  rrate = dev->rate;
  err = snd_pcm_hw_params_set_rate_near(handle, params, &rrate, 0);
  if (err < 0) {
    printf("Rate %d Hz not available for playback: %s\n", dev->rate, snd_strerror(err));
    return err;
  }
  if (rrate != dev->rate) {
    printf("Rate doesn't match (requested %dHz, get %dHz)\n", dev->rate, rrate);
    return -EINVAL;
  }
  
  /* set the period size */
  err = snd_pcm_hw_params_set_period_size(handle, params, dev->period_size, 0);
  if (err < 0) {
    printf("Unable to set period size %d for playback: %s\n", (int)dev->period_size, snd_strerror(err));
    return err;
  }
  
  err = snd_pcm_hw_params_get_period_size(params, &size, &dir);
  if (err < 0) {
    printf("Unable to get period size for playback: %s\n", snd_strerror(err));
    return err;
  }
  
  if (dev->period_size != size) {
    printf("Period size doesn't match (requested %d, got %d)\n", (int)dev->period_size, (int)size);
    return -EINVAL;
  }
  
    /* set the buffer size */
  err = snd_pcm_hw_params_set_buffer_size(handle, params, dev->buffer_size);
  if (err < 0) {
    printf("Unable to set buffer size %d for playback: %s\n", (int)dev->buffer_size, snd_strerror(err));
    return err;
  }
  err = snd_pcm_hw_params_get_buffer_size(params, &size);
  if (err < 0) {
    printf("Unable to get buffer size for playback: %s\n", snd_strerror(err));
    return err;
  }
  
  if (size != (snd_pcm_uframes_t)dev->buffer_size) {
    printf("Buffer size doesn't match (requested %d, got %d)\n", (int)dev->buffer_size, (int)size);
    return -EINVAL;
  }

  /* write the parameters to device */
  err = snd_pcm_hw_params(handle, params);
  if (err < 0) {
    printf("Unable to set hw params for playback: %s\n", snd_strerror(err));
    return err;
  }
  return 0;
}

int alsa_set_swparams(alsa_dev_t *dev, snd_pcm_t *handle, snd_pcm_sw_params_t *swparams)
{
  int err;
  
  /* get the current swparams */
  err = snd_pcm_sw_params_current(handle, swparams);
  if (err < 0) {
    printf("Unable to determine current swparams for playback: %s\n", snd_strerror(err));
    return err;
  }
  /* allow the transfer when at least period_size samples can be processed */
  /* or disable this mechanism when period event is enabled (aka interrupt like style processing) */
  err = snd_pcm_sw_params_set_avail_min(handle, swparams, dev->period_size);
  if (err < 0) {
    printf("Unable to set avail min for playback: %s\n", snd_strerror(err));
    return err;
  }
  /* enable period events */
  err = snd_pcm_sw_params_set_period_event(handle, swparams, 1);
  if (err < 0) {
    printf("Unable to set period event: %s\n", snd_strerror(err));
    return err;
  }

  /* write the parameters to the playback device */
  err = snd_pcm_sw_params(handle, swparams);
  if (err < 0) {
    printf("Unable to set sw params for playback: %s\n", snd_strerror(err));
    return err;
  }
  return 0;
}