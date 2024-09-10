void UpResidual_GMRF_5() {
exchsolution_gmrfData_5(0);
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
/* Statements in this Scop: S141 */
for (int i0 = iterationOffsetBegin[0][1]; (i0<=(iterationOffsetEnd[0][1]+32)); i0 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i0*35)]);
double* fieldData_Residual_GMRF_5_p1 = (&fieldData_Residual_GMRF[5][(i0*35)]);
double* fieldData_Solution_GMRF_5_p1 = (&fieldData_Solution_GMRF[5][(i0*35)]);
double* fieldData_RHS_GMRF_5_p1 = (&fieldData_RHS_GMRF[5][(i0*33)]);
int i1 = (iterationOffsetBegin[0][0]+i0);
for (; (i1<(((iterationOffsetBegin[0][0]+i0)+1)&(~1))); i1 += 1) {
fieldData_Residual_GMRF_5_p1[(i1+38)] = (fieldData_RHS_GMRF_5_p1[i1]-(((((((((fieldData_LaplaceCoeff_GMRF_5_p1[(i1+38)]*fieldData_Solution_GMRF_5_p1[(i1+38)])+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+1298)]*fieldData_Solution_GMRF_5_p1[(i1+39)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+2558)]*fieldData_Solution_GMRF_5_p1[(i1+37)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+3818)]*fieldData_Solution_GMRF_5_p1[(i1+74)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+5078)]*fieldData_Solution_GMRF_5_p1[(i1+2)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+6338)]*fieldData_Solution_GMRF_5_p1[(i1+1)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+7598)]*fieldData_Solution_GMRF_5_p1[(i1+73)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+8858)]*fieldData_Solution_GMRF_5_p1[(i1+3)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+10118)]*fieldData_Solution_GMRF_5_p1[(i1+75)])));
}
for (; (i1<((iterationOffsetEnd[0][0]+i0)+30)); i1 += 4) {
/* fieldData_Residual_GMRF_5_p1[(i1+38)] = (fieldData_RHS_GMRF_5_p1[i1]-(((((((((fieldData_LaplaceCoeff_GMRF_5_p1[(i1+38)]*fieldData_Solution_GMRF_5_p1[(i1+38)])+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+1298)]*fieldData_Solution_GMRF_5_p1[(i1+39)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+2558)]*fieldData_Solution_GMRF_5_p1[(i1+37)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+3818)]*fieldData_Solution_GMRF_5_p1[(i1+74)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+5078)]*fieldData_Solution_GMRF_5_p1[(i1+2)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+6338)]*fieldData_Solution_GMRF_5_p1[(i1+1)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+7598)]*fieldData_Solution_GMRF_5_p1[(i1+73)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+8858)]*fieldData_Solution_GMRF_5_p1[(i1+3)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+10118)]*fieldData_Solution_GMRF_5_p1[(i1+75)]))); */
__m128d vec0 = _mm_loadu_pd((&fieldData_RHS_GMRF_5_p1[i1]));
__m128d vec0_2 = _mm_loadu_pd((&fieldData_RHS_GMRF_5_p1[(i1+2)]));
__m128d vec1 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+10118)]));
__m128d vec1_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+10120)]));
__m128d vec2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+75)]));
__m128d vec2_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+77)]));
__m128d vec3 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+8858)]));
__m128d vec3_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+8860)]));
__m128d vec4 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+3)]));
__m128d vec4_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+5)]));
__m128d vec5 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+7598)]));
__m128d vec5_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+7600)]));
__m128d vec6 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+73)]));
__m128d vec6_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+75)]));
__m128d vec7 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+6338)]));
__m128d vec7_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+6340)]));
__m128d vec8 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+1)]));
__m128d vec8_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+3)]));
__m128d vec9 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+5078)]));
__m128d vec9_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+5080)]));
__m128d vec10 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+2)]));
__m128d vec10_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+4)]));
__m128d vec11 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+3818)]));
__m128d vec11_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+3820)]));
__m128d vec12 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+74)]));
__m128d vec12_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+76)]));
__m128d vec13 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+2558)]));
__m128d vec13_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+2560)]));
__m128d vec14 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+37)]));
__m128d vec14_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+39)]));
__m128d vec15 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+38)]));
__m128d vec15_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+40)]));
__m128d vec16 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+38)]));
__m128d vec16_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+40)]));
__m128d vec17 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+1298)]));
__m128d vec17_2 = _mm_loadu_pd((&fieldData_LaplaceCoeff_GMRF_5_p1[(i1+1300)]));
__m128d vec18 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+39)]));
__m128d vec18_2 = _mm_loadu_pd((&fieldData_Solution_GMRF_5_p1[(i1+41)]));
__m128d vec19;
__m128d vec19_2;
vec19 = _mm_sub_pd(vec0, _mm_add_pd(_mm_mul_pd(vec1, vec2), _mm_add_pd(_mm_mul_pd(vec3, vec4), _mm_add_pd(_mm_mul_pd(vec5, vec6), _mm_add_pd(_mm_mul_pd(vec7, vec8), _mm_add_pd(_mm_mul_pd(vec9, vec10), _mm_add_pd(_mm_mul_pd(vec11, vec12), _mm_add_pd(_mm_mul_pd(vec13, vec14), _mm_add_pd(_mm_mul_pd(vec15, vec16), _mm_mul_pd(vec17, vec18))))))))));
vec19_2 = _mm_sub_pd(vec0_2, _mm_add_pd(_mm_mul_pd(vec1_2, vec2_2), _mm_add_pd(_mm_mul_pd(vec3_2, vec4_2), _mm_add_pd(_mm_mul_pd(vec5_2, vec6_2), _mm_add_pd(_mm_mul_pd(vec7_2, vec8_2), _mm_add_pd(_mm_mul_pd(vec9_2, vec10_2), _mm_add_pd(_mm_mul_pd(vec11_2, vec12_2), _mm_add_pd(_mm_mul_pd(vec13_2, vec14_2), _mm_add_pd(_mm_mul_pd(vec15_2, vec16_2), _mm_mul_pd(vec17_2, vec18_2))))))))));
_mm_storeu_pd((&fieldData_Residual_GMRF_5_p1[(i1+38)]), vec19);
_mm_storeu_pd((&fieldData_Residual_GMRF_5_p1[(i1+40)]), vec19_2);
}
for (; (i1<((iterationOffsetEnd[0][0]+i0)+33)); i1 += 1) {
fieldData_Residual_GMRF_5_p1[(i1+38)] = (fieldData_RHS_GMRF_5_p1[i1]-(((((((((fieldData_LaplaceCoeff_GMRF_5_p1[(i1+38)]*fieldData_Solution_GMRF_5_p1[(i1+38)])+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+1298)]*fieldData_Solution_GMRF_5_p1[(i1+39)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+2558)]*fieldData_Solution_GMRF_5_p1[(i1+37)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+3818)]*fieldData_Solution_GMRF_5_p1[(i1+74)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+5078)]*fieldData_Solution_GMRF_5_p1[(i1+2)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+6338)]*fieldData_Solution_GMRF_5_p1[(i1+1)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+7598)]*fieldData_Solution_GMRF_5_p1[(i1+73)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+8858)]*fieldData_Solution_GMRF_5_p1[(i1+3)]))+(fieldData_LaplaceCoeff_GMRF_5_p1[(i1+10118)]*fieldData_Solution_GMRF_5_p1[(i1+75)])));
}
}
}
}
}