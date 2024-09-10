void SetSolution_GMRF_7(double value) {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
/* Statements in this Scop: S193 */
for (int i0 = (iterationOffsetBegin[0][1]-1); (i0<=(iterationOffsetEnd[0][1]+129)); i0 += 1) {
double* fieldData_Solution_GMRF_7_p1 = (&fieldData_Solution_GMRF[7][(i0*132)]);
int i1 = (iterationOffsetBegin[0][0]-1);
for (; (i1<(iterationOffsetBegin[0][0]&(~1))); i1 += 1) {
fieldData_Solution_GMRF_7_p1[(i1+134)] = value;
}
__m128d vec0 = _mm_set1_pd(value);
for (; (i1<(iterationOffsetEnd[0][0]+127)); i1 += 4) {
/* fieldData_Solution_GMRF_7_p1[(i1+134)] = value; */
__m128d vec1;
__m128d vec1_2;
vec1 = vec0;
vec1_2 = vec0;
_mm_storeu_pd((&fieldData_Solution_GMRF_7_p1[(i1+134)]), vec1);
_mm_storeu_pd((&fieldData_Solution_GMRF_7_p1[(i1+136)]), vec1_2);
}
for (; (i1<(iterationOffsetEnd[0][0]+130)); i1 += 1) {
fieldData_Solution_GMRF_7_p1[(i1+134)] = value;
}
}
}
}
}