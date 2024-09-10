void HighPassFilter::setFlaggedValuesToZeroAndMakeWeightsSSE(const Image2DCPtr &inputImage, const Image2DPtr &outputImage, const Mask2DCPtr &inputMask, const Image2DPtr &weightsOutput)
{
	const size_t width = inputImage->Width();
	const __m128i zero4i = _mm_set_epi32(0, 0, 0, 0);
	const __m128 zero4 = _mm_set_ps(0.0, 0.0, 0.0, 0.0);
	const __m128 one4 = _mm_set_ps(1.0, 1.0, 1.0, 1.0);
	for(size_t y=0;y<inputImage->Height();++y)
	{
		const bool *rowPtr = inputMask->ValuePtr(0, y);
		const float *inputPtr = inputImage->ValuePtr(0, y);
		float *outputPtr = outputImage->ValuePtr(0, y);
		float *weightsPtr = weightsOutput->ValuePtr(0, y);
		const float *end = inputPtr + width;
		while(inputPtr < end)
		{
			
			// Assign each integer to one bool in the mask
			// Convert false to 0xFFFFFFFF and true to 0
			__m128 conditionMask = _mm_castsi128_ps(
				_mm_cmpeq_epi32(_mm_set_epi32(rowPtr[3] || !isfinite(inputPtr[3]), rowPtr[2] || !isfinite(inputPtr[2]),
																			rowPtr[1] || !isfinite(inputPtr[1]), rowPtr[0] || !isfinite(inputPtr[0])),
												zero4i));
			
			_mm_store_ps(weightsPtr, _mm_or_ps(
				_mm_and_ps(conditionMask, one4),
				_mm_andnot_ps(conditionMask, zero4)
			));
			_mm_store_ps(outputPtr, _mm_or_ps(
				_mm_and_ps(conditionMask, _mm_load_ps(inputPtr)),
				_mm_andnot_ps(conditionMask, zero4)
			));
			
			rowPtr += 4;
			outputPtr += 4;
			inputPtr += 4;
			weightsPtr += 4;
		}
	}
}