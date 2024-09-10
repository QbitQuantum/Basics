void UpResidual_GMRF_3() {
exchsolution_gmrfData_3(0);
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
/* Statements in this Scop: S139 */
for (int i0 = iterationOffsetBegin[0][1]; (i0<=(iterationOffsetEnd[0][1]+8)); i0 += 1) {
double* fieldData_Solution_GMRF_3_p1 = (&fieldData_Solution_GMRF[3][(i0*11)]);
double* fieldData_RHS_GMRF_3_p1 = (&fieldData_RHS_GMRF[3][(i0*9)]);
double* fieldData_LaplaceCoeff_GMRF_3_p1 = (&fieldData_LaplaceCoeff_GMRF[3][(i0*11)]);
double* fieldData_Residual_GMRF_3_p1 = (&fieldData_Residual_GMRF[3][(i0*11)]);
int i1 = (iterationOffsetBegin[0][0]+i0);
for (; (i1<(((iterationOffsetBegin[0][0]+i0)+1)&(~1))); i1 += 1) {
fieldData_Residual_GMRF_3_p1[(i1+14)] = (fieldData_RHS_GMRF_3_p1[i1]-(((((((((fieldData_LaplaceCoeff_GMRF_3_p1[(i1+14)]*fieldData_Solution_GMRF_3_p1[(i1+14)])+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+146)]*fieldData_Solution_GMRF_3_p1[(i1+15)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+278)]*fieldData_Solution_GMRF_3_p1[(i1+13)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+410)]*fieldData_Solution_GMRF_3_p1[(i1+26)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+542)]*fieldData_Solution_GMRF_3_p1[(i1+2)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+674)]*fieldData_Solution_GMRF_3_p1[(i1+1)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+806)]*fieldData_Solution_GMRF_3_p1[(i1+25)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+938)]*fieldData_Solution_GMRF_3_p1[(i1+3)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+1070)]*fieldData_Solution_GMRF_3_p1[(i1+27)])));
}
for (; (i1<((iterationOffsetEnd[0][0]+i0)+6)); i1 += 4) {
/* fieldData_Residual_GMRF_3_p1[(i1+14)] = (fieldData_RHS_GMRF_3_p1[i1]-(((((((((fieldData_LaplaceCoeff_GMRF_3_p1[(i1+14)]*fieldData_Solution_GMRF_3_p1[(i1+14)])+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+146)]*fieldData_Solution_GMRF_3_p1[(i1+15)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+278)]*fieldData_Solution_GMRF_3_p1[(i1+13)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+410)]*fieldData_Solution_GMRF_3_p1[(i1+26)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+542)]*fieldData_Solution_GMRF_3_p1[(i1+2)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+674)]*fieldData_Solution_GMRF_3_p1[(i1+1)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+806)]*fieldData_Solution_GMRF_3_p1[(i1+25)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+938)]*fieldData_Solution_GMRF_3_p1[(i1+3)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+1070)]*fieldData_Solution_GMRF_3_p1[(i1+27)]))); */
__m128d vec0 = _mm_loadu_pd((&fieldData_RHS_GMRF_3_p1[i1]));
__m128d vec0_2 = _mm_loadu_pd((&fieldData_RHS_GMRF_3_p1[(i1+2)]));
__m128d vec1 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+1070)]));
__m128d vec1_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+1072)]));
__m128d vec2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+27)]));
__m128d vec2_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+29)]));
__m128d vec3 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+938)]));
__m128d vec3_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+940)]));
__m128d vec4 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+3)]));
__m128d vec4_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+5)]));
__m128d vec5 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+806)]));
__m128d vec5_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+808)]));
__m128d vec6 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+25)]));
__m128d vec6_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+27)]));
__m128d vec7 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+674)]));
__m128d vec7_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+676)]));
__m128d vec8 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+1)]));
__m128d vec8_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+3)]));
__m128d vec9 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+542)]));
__m128d vec9_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+544)]));
__m128d vec10 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+2)]));
__m128d vec10_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+4)]));
__m128d vec11 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+410)]));
__m128d vec11_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+412)]));
__m128d vec12 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+26)]));
__m128d vec12_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+28)]));
__m128d vec13 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+278)]));
__m128d vec13_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+280)]));
__m128d vec14 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+13)]));
__m128d vec14_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+15)]));
__m128d vec15 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+14)]));
__m128d vec15_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+16)]));
__m128d vec16 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+14)]));
__m128d vec16_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+16)]));
__m128d vec17 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+146)]));
__m128d vec17_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_3_p1[(i1+148)]));
__m128d vec18 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+15)]));
__m128d vec18_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_3_p1[(i1+17)]));
__m128d vec19;
__m128d vec19_2;
vec19 = _mm_sub_pd(vec0, _mm_add_pd(_mm_mul_pd(vec1, vec2), _mm_add_pd(_mm_mul_pd(vec3, vec4), _mm_add_pd(_mm_mul_pd(vec5, vec6), _mm_add_pd(_mm_mul_pd(vec7, vec8), _mm_add_pd(_mm_mul_pd(vec9, vec10), _mm_add_pd(_mm_mul_pd(vec11, vec12), _mm_add_pd(_mm_mul_pd(vec13, vec14), _mm_add_pd(_mm_mul_pd(vec15, vec16), _mm_mul_pd(vec17, vec18))))))))));
vec19_2 = _mm_sub_pd(vec0_2, _mm_add_pd(_mm_mul_pd(vec1_2, vec2_2), _mm_add_pd(_mm_mul_pd(vec3_2, vec4_2), _mm_add_pd(_mm_mul_pd(vec5_2, vec6_2), _mm_add_pd(_mm_mul_pd(vec7_2, vec8_2), _mm_add_pd(_mm_mul_pd(vec9_2, vec10_2), _mm_add_pd(_mm_mul_pd(vec11_2, vec12_2), _mm_add_pd(_mm_mul_pd(vec13_2, vec14_2), _mm_add_pd(_mm_mul_pd(vec15_2, vec16_2), _mm_mul_pd(vec17_2, vec18_2))))))))));
_mm_storeu_pd((&fieldData_Residual_GMRF_3_p1[(i1+14)]), vec19);
_mm_storeu_pd((&fieldData_Residual_GMRF_3_p1[(i1+16)]), vec19_2);
}
for (; (i1<((iterationOffsetEnd[0][0]+i0)+9)); i1 += 1) {
fieldData_Residual_GMRF_3_p1[(i1+14)] = (fieldData_RHS_GMRF_3_p1[i1]-(((((((((fieldData_LaplaceCoeff_GMRF_3_p1[(i1+14)]*fieldData_Solution_GMRF_3_p1[(i1+14)])+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+146)]*fieldData_Solution_GMRF_3_p1[(i1+15)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+278)]*fieldData_Solution_GMRF_3_p1[(i1+13)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+410)]*fieldData_Solution_GMRF_3_p1[(i1+26)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+542)]*fieldData_Solution_GMRF_3_p1[(i1+2)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+674)]*fieldData_Solution_GMRF_3_p1[(i1+1)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+806)]*fieldData_Solution_GMRF_3_p1[(i1+25)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+938)]*fieldData_Solution_GMRF_3_p1[(i1+3)]))+(fieldData_LaplaceCoeff_GMRF_3_p1[(i1+1070)]*fieldData_Solution_GMRF_3_p1[(i1+27)])));
}
}
}
}
}