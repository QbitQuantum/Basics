  float Ashuffle[9][8], Ushuffle[9][8], Vshuffle[9][8], Sshuffle[3][8];
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      for (int k=0; k<8; k++)
      {
        Ashuffle[i + j*3][k] = A(i + 3*k, j);
      }
    }
  }

#include "Singular_Value_Decomposition_Kernel_Declarations.hpp"

  ENABLE_AVX_IMPLEMENTATION(Va11=_mm256_loadu_ps(Ashuffle[0]);)
  ENABLE_AVX_IMPLEMENTATION(Va21=_mm256_loadu_ps(Ashuffle[1]);)
  ENABLE_AVX_IMPLEMENTATION(Va31=_mm256_loadu_ps(Ashuffle[2]);)
  ENABLE_AVX_IMPLEMENTATION(Va12=_mm256_loadu_ps(Ashuffle[3]);)
  ENABLE_AVX_IMPLEMENTATION(Va22=_mm256_loadu_ps(Ashuffle[4]);)
  ENABLE_AVX_IMPLEMENTATION(Va32=_mm256_loadu_ps(Ashuffle[5]);)
  ENABLE_AVX_IMPLEMENTATION(Va13=_mm256_loadu_ps(Ashuffle[6]);)
  ENABLE_AVX_IMPLEMENTATION(Va23=_mm256_loadu_ps(Ashuffle[7]);)
  ENABLE_AVX_IMPLEMENTATION(Va33=_mm256_loadu_ps(Ashuffle[8]);)

#include "Singular_Value_Decomposition_Main_Kernel_Body.hpp"

  ENABLE_AVX_IMPLEMENTATION(_mm256_storeu_ps(Ushuffle[0],Vu11);)
  ENABLE_AVX_IMPLEMENTATION(_mm256_storeu_ps(Ushuffle[1],Vu21);)
  ENABLE_AVX_IMPLEMENTATION(_mm256_storeu_ps(Ushuffle[2],Vu31);)
  ENABLE_AVX_IMPLEMENTATION(_mm256_storeu_ps(Ushuffle[3],Vu12);)
  ENABLE_AVX_IMPLEMENTATION(_mm256_storeu_ps(Ushuffle[4],Vu22);)