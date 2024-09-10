//hosts that have power-of-2 blocksizes
//ann aligned memory will allways end up doing
//sse processing...
void Multitap::process(float *inputs, float *outputs, unsigned long nSamples, bool replace)
{
	//no use in using SSE for less samples then 16!
	//host calling VST plugins with less than 16-sample buffers should be shot, tortured and shot again
	if(nSamples <= 16 || !sse)
	{
		processFPU(inputs,outputs,nSamples,replace);
		return;
	}

	//let's see if the current index is a multiple of 4
	//if it isn't, we need to process untill it *IS*
	unsigned long startSize = (4 - (indexfpu & 3)) & 3;
	unsigned long blockSize = 0;

	//stupid, but who cares ;-)
	while(startSize + blockSize + 4 <= nSamples)
		blockSize += 4;

	//we'll have to process a maximum of 4 samples at the end...
	unsigned long endSize = nSamples - (startSize + blockSize);

	if(startSize)
		processFPU(inputs,outputs,startSize,replace);

	inputs += startSize;
	outputs += startSize;

	if(blockSize)
	{
		nSamples = blockSize;

		unsigned long index = indexfpu >> 2;

#ifndef _WIN64
		_mm_empty(); // No MMX on x64
#endif

		_mm_prefetch(((char *)&delay[0]),0);
		_mm_prefetch(((char *)&amp[0]),0);

		//are the buffers 16-byte aligned??
		if ((((int)inputs & 15) == 0) && (((int)outputs & 15) == 0))
		{
			nSamples >>= 2;
			while(nSamples--)
			{
				float *x = inputs + 4;
				float *y = outputs + 4;

				_mm_prefetch((char *) x,0);
				_mm_prefetch((char *) y,0);

				buffer[index] = _mm_load_ps(inputs);

				__m128 out_sse = _mm_setzero_ps();

				for(long z=0;z<32;z+=4)
				{
					long tmp1 = (index - delay[z+0]) & mask;
					long tmp2 = (index - delay[z+1]) & mask;
					long tmp3 = (index - delay[z+2]) & mask;
					long tmp4 = (index - delay[z+3]) & mask;

					//out += amp[z] * buffer[tmp1]
					out_sse = _mm_add_ps(_mm_mul_ps(amp[z],buffer[tmp1]),out_sse);
					_mm_prefetch(((char *)&buffer[tmp1]) + 16,0);

					out_sse = _mm_add_ps(_mm_mul_ps(amp[z+1],buffer[tmp2]),out_sse);
					_mm_prefetch(((char *)&buffer[tmp2]) + 16,0);

					out_sse = _mm_add_ps(_mm_mul_ps(amp[z+2],buffer[tmp3]),out_sse);
					_mm_prefetch(((char *)&buffer[tmp3]) + 16,0);

					out_sse = _mm_add_ps(_mm_mul_ps(amp[z+3],buffer[tmp4]),out_sse);
					_mm_prefetch(((char *)&buffer[tmp4]) + 16,0);
				}

				if(replace)
					_mm_store_ps(outputs,out_sse);
				else
					_mm_store_ps(outputs,_mm_add_ps(out_sse,_mm_load_ps(outputs)));

				index++;
				index &= mask;

				inputs = x;
				outputs = y;
			}
		}
		else //non-aligned buffers!
		{