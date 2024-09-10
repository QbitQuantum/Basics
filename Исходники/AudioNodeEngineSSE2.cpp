void AudioBufferAddWithScale_SSE(const float* aInput, float aScale,
                                 float* aOutput, uint32_t aSize) {
  __m128 vin0, vin1, vin2, vin3, vscaled0, vscaled1, vscaled2, vscaled3, vout0,
      vout1, vout2, vout3, vgain;

  ASSERT_ALIGNED16(aInput);
  ASSERT_ALIGNED16(aOutput);
  ASSERT_MULTIPLE16(aSize);

  vgain = _mm_load1_ps(&aScale);

  for (unsigned i = 0; i < aSize; i += 16) {
    vin0 = _mm_load_ps(&aInput[i]);
    vin1 = _mm_load_ps(&aInput[i + 4]);
    vin2 = _mm_load_ps(&aInput[i + 8]);
    vin3 = _mm_load_ps(&aInput[i + 12]);

    vscaled0 = _mm_mul_ps(vin0, vgain);
    vscaled1 = _mm_mul_ps(vin1, vgain);
    vscaled2 = _mm_mul_ps(vin2, vgain);
    vscaled3 = _mm_mul_ps(vin3, vgain);

    vin0 = _mm_load_ps(&aOutput[i]);
    vin1 = _mm_load_ps(&aOutput[i + 4]);
    vin2 = _mm_load_ps(&aOutput[i + 8]);
    vin3 = _mm_load_ps(&aOutput[i + 12]);

    vout0 = _mm_add_ps(vin0, vscaled0);
    vout1 = _mm_add_ps(vin1, vscaled1);
    vout2 = _mm_add_ps(vin2, vscaled2);
    vout3 = _mm_add_ps(vin3, vscaled3);

    _mm_store_ps(&aOutput[i], vout0);
    _mm_store_ps(&aOutput[i + 4], vout1);
    _mm_store_ps(&aOutput[i + 8], vout2);
    _mm_store_ps(&aOutput[i + 12], vout3);
  }
}