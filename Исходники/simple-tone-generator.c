void
simpleaudio_tone(simpleaudio *sa_out, float tone_freq, size_t nsamples_dur)
{
    unsigned int framesize = simpleaudio_get_framesize(sa_out);

    void *buf = malloc(nsamples_dur * framesize);
    assert(buf);

    if ( tone_freq != 0 ) {

	float wave_nsamples = simpleaudio_get_rate(sa_out) / tone_freq;
	size_t i;

#define TURNS_TO_RADIANS(t)	( (float)M_PI*2 * (t) )

#define SINE_PHASE_TURNS	( (float)i/wave_nsamples + sa_tone_cphase )
#define SINE_PHASE_RADIANS	TURNS_TO_RADIANS(SINE_PHASE_TURNS)

	switch ( simpleaudio_get_format(sa_out) ) {

	    case SA_SAMPLE_FORMAT_FLOAT:
		{
		    float *float_buf = buf;
		    if ( sin_table_float ) {
			for ( i=0; i<nsamples_dur; i++ )
			    float_buf[i] = sin_lu_float(SINE_PHASE_TURNS);
		    } else {
			for ( i=0; i<nsamples_dur; i++ )
			    float_buf[i] = tone_mag * sinf(SINE_PHASE_RADIANS);
		    }
		}
		break;

	    case SA_SAMPLE_FORMAT_S16:
		{
		    short *short_buf = buf;
		    if ( sin_table_short ) {
			for ( i=0; i<nsamples_dur; i++ )
			    short_buf[i] = sin_lu_short(SINE_PHASE_TURNS);
		    } else {
			unsigned short mag_s = 32767.0f * tone_mag + 0.5f;
			if ( tone_mag > 1.0f ) // clamp to 1.0 to avoid overflow
			    mag_s = 32767;
			if ( mag_s < 1 ) // "short epsilon"
			    mag_s = 1;
			for ( i=0; i<nsamples_dur; i++ )
			    short_buf[i] = lroundf( mag_s * sinf(SINE_PHASE_RADIANS) );
		    }
		    break;
		}

	    default:
		assert(0);
		break;
	}

	sa_tone_cphase
	    = fmodf(sa_tone_cphase + (float)nsamples_dur/wave_nsamples, 1.0);

    } else {

	bzero(buf, nsamples_dur * framesize);
	sa_tone_cphase = 0.0;

    }

    assert ( simpleaudio_write(sa_out, buf, nsamples_dur) > 0 );

    free(buf);
}