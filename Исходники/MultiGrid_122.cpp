void InitRHS_GMRF() {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
/* Statements in this Scop: S279 */
for (int i0 = iterationOffsetBegin[0][1]; (i0<=(iterationOffsetEnd[0][1]+256)); i0 += 1) {
double* fieldData_RHS_GMRF_8_p1 = (&fieldData_RHS_GMRF[8][(i0*258)]);
int i1 = iterationOffsetBegin[0][0];
for (; (i1<((iterationOffsetBegin[0][0]+1)&(~1))); i1 += 1) {
fieldData_RHS_GMRF_8_p1[i1] = 0.000000e+00;
}
__m128d vec0 = _mm_set1_pd(0.000000e+00);
for (; (i1<(iterationOffsetEnd[0][0]+254)); i1 += 4) {
/* fieldData_RHS_GMRF_8_p1[i1] = 0.000000e+00; */
__m128d vec1;
__m128d vec1_2;
vec1 = vec0;
vec1_2 = vec0;
_mm_storeu_pd((&fieldData_RHS_GMRF_8_p1[i1]), vec1);
_mm_storeu_pd((&fieldData_RHS_GMRF_8_p1[(i1+2)]), vec1_2);
}
for (; (i1<(iterationOffsetEnd[0][0]+257)); i1 += 1) {
fieldData_RHS_GMRF_8_p1[i1] = 0.000000e+00;
}
}
}
}
}