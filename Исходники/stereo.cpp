//--------------------------------------------------------------------------------
OSStatus Stereo::ProcessBufferLists(AudioUnitRenderActionFlags & ioActionFlags,
	const AudioBufferList & inBuffer, AudioBufferList & outBuffer, UInt32 inFramesToProcess)
{
	// update internal parameters...
	float dphi = (float) (3.141 * GetParameter(kParam_Rate) / GetSampleRate());
	float mod = (float) ((double)GetParameter(kParam_Mod) * 0.001 * GetSampleRate());

	long widthMode = (long) GetParameter(kParam_Mode);
	if (widthMode >= kNumModes)
		widthMode = kNumModes - 1;
	else if (widthMode < 0)
		widthMode = 0;
	float widthValue = GetParameter(kParam_Width) * 0.01f;
	float fli, fld, fri, frd;
	if (widthMode == kMode_Haas)
	{
		fli = 1.0f - (widthValue * 0.75f);
		fld = 0.0f;
		fri = 1.0f - widthValue;
		frd = 1.0f - fri;
	}
	else
	{
		fli = ((1.0f - widthValue) * 0.5f) + 0.5f;
		fld = widthValue * 0.5f;
		fri = fli;
		frd = -fld;
	}
	float fdel = (float) ((double)GetParameter(kParam_Delay) * 0.001 * GetSampleRate());
	float balanceValue = GetParameter(kParam_Balance) * 0.01f;
	float balanceScalar = 1.0f - fabsf(balanceValue);
	if (balanceValue > 0.0f)
	{
		fli *= balanceScalar;
		fld *= balanceScalar;
	}
	else
	{
		fri *= balanceScalar;
		frd *= balanceScalar;
	}
	float widthValue_modified = (widthValue * 0.5f) + 0.5f;
	fri *= widthValue_modified;
	frd *= widthValue_modified;
	fli *= widthValue_modified;
	fld *= widthValue_modified;



	const float * in1 = (float*)(inBuffer.mBuffers[0].mData);
	float * in2 = NULL;
	if (inBuffer.mNumberBuffers > 1)
		in2 = (float*)(inBuffer.mBuffers[1].mData);
	float * out[kNumOutputs];
	for (SInt16 i=0; i < kNumOutputs; i++)
		out[i] = (float*)(outBuffer.mBuffers[i].mData);

	if (mod > 0.0f)	// modulated delay
	{
		for (UInt32 samp=0; samp < inFramesToProcess; samp++)
		{
			float a = in1[samp];	// mono input
			if (in2 != NULL)
				a = (a + in2[samp]) * 0.5f;	// summed stereo input

			buffer[bufpos] = a;	// write
			long tmp = (bufpos + (long)(fdel + fabsf(mod * sinf(phi)) ) ) % bufsize;
			float b = buffer[tmp];

			out[0][samp] = (a * fli) - (b * fld);	// output
			out[1][samp] = (a * fri) - (b * frd);

			// buffer position
			bufpos--;
			if (bufpos < 0)
				bufpos = bufsize - 1;

			phi = phi + dphi;
		}
	}
	else
	{
		for (UInt32 samp=0; samp < inFramesToProcess; samp++)
		{
			float a = in1[samp];	// mono input
			if (in2 != NULL)
				a = (a + in2[samp]) * 0.5f;	// summed stereo input

			buffer[bufpos] = a;	// write
			long tmp = (bufpos + (long)(fdel) ) % bufsize;
			float b = buffer[tmp];

			out[0][samp] = (a * fli) - (b * fld);	// output
			out[1][samp] = (a * fri) - (b * frd);

			// buffer position
			bufpos--;
			if (bufpos < 0)
				bufpos = bufsize - 1;
		}
	}
	phi = fmodf(phi, 6.2831853f);

	return noErr;
}