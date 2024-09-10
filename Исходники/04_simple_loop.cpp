    { 1.1f, 1.1f, 1.1f, 1.1f, 1.1f, 1.1f, 1.1f, 1.1f },   // RCX + 352
    { 1.2f, 1.2f, 1.2f, 1.2f, 1.2f, 1.2f, 1.2f, 1.2f },   // RCX + 384
    { 1.3f, 1.3f, 1.3f, 1.3f, 1.3f, 1.3f, 1.3f, 1.3f },   // RCX + 416
    { 1.4f, 1.4f, 1.4f, 1.4f, 1.4f, 1.4f, 1.4f, 1.4f },   // RCX + 480
    { 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f },   // RCX + 512
  }
  VPU_ALIGN_SUFFIX(32);

  // our assembler
  vpu::IAssembler* a = g_lib->createAssembler();

  // This example demonstrates a simple loop. The equivalent C++ code would look like:

#if 0

  __m256 YMM0 = _mm256_setzero_ps();
  __m256* R9 = (__m256*)(argument_data + 1);
  for (int i = 0; i < 10; ++i)
  {
    YMM0 = _mm256_add_ps(YMM0, R9[i]);
  }
  _mm256_store_ps(argument_data[0], YMM0);

#endif

  // start assembling
  a->begin();

    // we'll accumulate the sum of the array in YMM0
    a->setzero(vpu::YMM0);
