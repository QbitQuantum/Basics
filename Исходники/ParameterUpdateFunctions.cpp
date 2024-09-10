void sgdUpdateAvx(float learningRate,
                  float momentum,
                  float decayRate,
                  size_t size,
                  float* value,
                  const float* _grad,
                  float* momentumVec) {
#ifdef __AVX__
  float* grad = const_cast<float*>(_grad);  // the gradient is not modified
                                            // but when invoke simd functions
                                            // need non-const pointer.
  size_t gradientAlign = 0;
  size_t gradientAlignHeader = (size_t)grad % sizeof(__m256);
  CHECK_EQ(gradientAlignHeader, (size_t)momentumVec % sizeof(__m256))
      << "Gradent buffer didn't align with momentum buffer";
  CHECK_EQ(gradientAlignHeader, (size_t)value % sizeof(__m256))
      << "Gradent buffer didn't align with value buffer";
  if (0 != gradientAlignHeader) {
    gradientAlignHeader = sizeof(__m256) - gradientAlignHeader;
    gradientAlign = gradientAlignHeader / sizeof(real);

    // handle the unalign buffer
    for (size_t i = 0; i < gradientAlign; i++) {
      momentumVec[i] = momentum * momentumVec[i] - (learningRate * grad[i]) -
                       (decayRate * learningRate * value[i]);
      value[i] += momentumVec[i];
    }
    grad += gradientAlign;
    momentumVec += gradientAlign;
    value += gradientAlign;
  }

  constexpr size_t kParallelNum = 8;
  constexpr size_t nStepSize = (sizeof(__m256) / sizeof(real)) * kParallelNum;
  size_t cntLoop = (size - gradientAlign) / nStepSize;
  size_t cntRem = (size - gradientAlign) % nStepSize;
  __m256 gradientTmp[kParallelNum];
  __m256 valueTmp[kParallelNum];
  __m256 lr, mom, dr;
  std::function<void(void)> loopFun;

  learningRate *= -1;
  lr = _mm256_set_ps(learningRate,
                     learningRate,
                     learningRate,
                     learningRate,
                     learningRate,
                     learningRate,
                     learningRate,
                     learningRate);

  if (0 != momentum) {
    mom = _mm256_set_ps(momentum,
                        momentum,
                        momentum,
                        momentum,
                        momentum,
                        momentum,
                        momentum,
                        momentum);
  }

  decayRate *= learningRate;
  if (0 != decayRate) {
    dr = _mm256_set_ps(decayRate,
                       decayRate,
                       decayRate,
                       decayRate,
                       decayRate,
                       decayRate,
                       decayRate,
                       decayRate);
  }

  auto gradMulFun = [&](void) {
    gradientTmp[0] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad), lr);
    gradientTmp[1] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 8), lr);
    gradientTmp[2] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 16), lr);
    gradientTmp[3] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 24), lr);
    gradientTmp[4] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 32), lr);
    gradientTmp[5] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 40), lr);
    gradientTmp[6] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 48), lr);
    gradientTmp[7] = _mm256_mul_ps(*reinterpret_cast<__m256*>(grad + 56), lr);
  };

  auto valueMulFun = [&](void) {
    valueTmp[0] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value), dr);
    valueTmp[1] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 8), dr);
    valueTmp[2] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 16), dr);
    valueTmp[3] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 24), dr);
    valueTmp[4] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 32), dr);
    valueTmp[5] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 40), dr);
    valueTmp[6] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 48), dr);
    valueTmp[7] = _mm256_mul_ps(*reinterpret_cast<__m256*>(value + 56), dr);
  };

  auto momentumMulFun = [&](void) {
    *reinterpret_cast<__m256*>(momentumVec) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec), mom);
    *reinterpret_cast<__m256*>(momentumVec + 8) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 8), mom);
    *reinterpret_cast<__m256*>(momentumVec + 16) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 16), mom);
    *reinterpret_cast<__m256*>(momentumVec + 24) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 24), mom);
    *reinterpret_cast<__m256*>(momentumVec + 32) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 32), mom);
    *reinterpret_cast<__m256*>(momentumVec + 40) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 40), mom);
    *reinterpret_cast<__m256*>(momentumVec + 48) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 48), mom);
    *reinterpret_cast<__m256*>(momentumVec + 56) =
        _mm256_mul_ps(*reinterpret_cast<__m256*>(momentumVec + 56), mom);
  };

  auto momentumAddGradFun = [&](void) {
    *reinterpret_cast<__m256*>(momentumVec) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(momentumVec), gradientTmp[0]);
    *reinterpret_cast<__m256*>(momentumVec + 8) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 8), gradientTmp[1]);
    *reinterpret_cast<__m256*>(momentumVec + 16) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 16), gradientTmp[2]);
    *reinterpret_cast<__m256*>(momentumVec + 24) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 24), gradientTmp[3]);
    *reinterpret_cast<__m256*>(momentumVec + 32) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 32), gradientTmp[4]);
    *reinterpret_cast<__m256*>(momentumVec + 40) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 40), gradientTmp[5]);
    *reinterpret_cast<__m256*>(momentumVec + 48) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 48), gradientTmp[6]);
    *reinterpret_cast<__m256*>(momentumVec + 56) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 56), gradientTmp[7]);
  };

  auto momentumZeroFun = [&](void) {
    *reinterpret_cast<__m256*>(momentumVec) = gradientTmp[0];
    *reinterpret_cast<__m256*>(momentumVec + 8) = gradientTmp[1];
    *reinterpret_cast<__m256*>(momentumVec + 16) = gradientTmp[2];
    *reinterpret_cast<__m256*>(momentumVec + 24) = gradientTmp[3];
    *reinterpret_cast<__m256*>(momentumVec + 32) = gradientTmp[4];
    *reinterpret_cast<__m256*>(momentumVec + 40) = gradientTmp[5];
    *reinterpret_cast<__m256*>(momentumVec + 48) = gradientTmp[6];
    *reinterpret_cast<__m256*>(momentumVec + 56) = gradientTmp[7];
  };

  auto momentumAddValueFun = [&](void) {
    *reinterpret_cast<__m256*>(momentumVec) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(momentumVec), valueTmp[0]);
    *reinterpret_cast<__m256*>(momentumVec + 8) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(momentumVec + 8), valueTmp[1]);
    *reinterpret_cast<__m256*>(momentumVec + 16) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 16), valueTmp[2]);
    *reinterpret_cast<__m256*>(momentumVec + 24) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 24), valueTmp[3]);
    *reinterpret_cast<__m256*>(momentumVec + 32) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 32), valueTmp[4]);
    *reinterpret_cast<__m256*>(momentumVec + 40) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 40), valueTmp[5]);
    *reinterpret_cast<__m256*>(momentumVec + 48) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 48), valueTmp[6]);
    *reinterpret_cast<__m256*>(momentumVec + 56) = _mm256_add_ps(
        *reinterpret_cast<__m256*>(momentumVec + 56), valueTmp[7]);
  };

  auto valueAddMomentumFun = [&](void) {
    *reinterpret_cast<__m256*>(value) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value),
                      *reinterpret_cast<__m256*>(momentumVec));
    *reinterpret_cast<__m256*>(value + 8) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 8),
                      *reinterpret_cast<__m256*>(momentumVec + 8));
    *reinterpret_cast<__m256*>(value + 16) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 16),
                      *reinterpret_cast<__m256*>(momentumVec + 16));
    *reinterpret_cast<__m256*>(value + 24) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 24),
                      *reinterpret_cast<__m256*>(momentumVec + 24));
    *reinterpret_cast<__m256*>(value + 32) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 32),
                      *reinterpret_cast<__m256*>(momentumVec + 32));
    *reinterpret_cast<__m256*>(value + 40) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 40),
                      *reinterpret_cast<__m256*>(momentumVec + 40));
    *reinterpret_cast<__m256*>(value + 48) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 48),
                      *reinterpret_cast<__m256*>(momentumVec + 48));
    *reinterpret_cast<__m256*>(value + 56) =
        _mm256_add_ps(*reinterpret_cast<__m256*>(value + 56),
                      *reinterpret_cast<__m256*>(momentumVec + 56));
  };

  if (0 == decayRate && 0 == momentum) {
    loopFun = [&](void) {
      gradMulFun();
      momentumZeroFun();
      valueAddMomentumFun();
    };
  } else if (0 == decayRate && 0 != momentum) {
    loopFun = [&](void) {
      gradMulFun();
      momentumMulFun();
      momentumAddGradFun();
      valueAddMomentumFun();
    };
  } else if (0 != decayRate && 0 == momentum) {
    loopFun = [&](void) {
      gradMulFun();
      valueMulFun();
      momentumZeroFun();
      momentumAddValueFun();
      valueAddMomentumFun();
    };
  } else if (0 != decayRate && 0 != momentum) {
    loopFun = [&](void) {
      gradMulFun();
      valueMulFun();
      momentumMulFun();
      momentumAddGradFun();
      momentumAddValueFun();
      valueAddMomentumFun();
    };
  }

  for (size_t i = 0; i < cntLoop; i++) {
    loopFun();
    grad += nStepSize;
    momentumVec += nStepSize;
    value += nStepSize;
  }

  for (size_t i = 0; i < cntRem; i++) {
    momentumVec[i] = momentum * momentumVec[i] + (learningRate * grad[i]) +
                     (decayRate * value[i]);
    value[i] += momentumVec[i];
  }
#endif
}