void MultiplyAudioBuffer(float *buffer, int totalFloats, float mulVal)
{
    float sum = 0.0f;
    int totalFloatsStore = totalFloats;

    if((UPARAM(buffer) & 0xF) == 0)
    {
        UINT alignedFloats = totalFloats & 0xFFFFFFFC;
        __m128 sseMulVal = _mm_set_ps1(mulVal);

        for(UINT i=0; i<alignedFloats; i += 4)
        {
            __m128 sseScaledVals = _mm_mul_ps(_mm_load_ps(buffer+i), sseMulVal);
            _mm_store_ps(buffer+i, sseScaledVals);
        }

        buffer      += alignedFloats;
        totalFloats -= alignedFloats;
    }

    for(int i=0; i<totalFloats; i++)
        buffer[i] *= mulVal;
}