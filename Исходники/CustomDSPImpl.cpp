	//----------------------------------------------------------------------
	FMOD_RESULT F_CALLBACK dspRead( FMOD_DSP_STATE * dsp_state, float * inBuffer, float* outBuffer, unsigned int length, int inChannels, int outChannels )
	{
		CustomDSPImpl* customDSP = nullptr;
		
		FMOD::DSP* thisDSP = (FMOD::DSP*)dsp_state->instance;

		thisDSP->getUserData( (void**)&customDSP );
		

		return customDSP->read( dsp_state, inBuffer, outBuffer, length, inChannels, outChannels );
	}