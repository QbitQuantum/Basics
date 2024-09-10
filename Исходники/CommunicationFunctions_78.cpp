void exchlaplacecoeff_gmrfData_0(unsigned int slot) {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((!neighbor_isValid[0][0])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1053, S1056, S1059, S1050, S1058, S1052, S1055, S1060, S1054, S1057, S1051 */
{
{
{
{
{
{
{
{
{
{
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+26)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+32)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+26)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+146)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+152)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+146)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+98)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+104)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+98)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+74)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+80)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+74)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posBegin[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<0); i1 += 4) {
/* xPos = posBegin[0]; */
__m128d vec0 = _mm_load1_pd((&posBegin[0]));
__m128d vec0_2 = _mm_load1_pd((&posBegin[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<3); i1 += 1) {
xPos = posBegin[0];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+122)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+128)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+122)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+170)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+176)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+170)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+194)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+200)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+194)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/1.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(1.000000e+00);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<0); i1 += 4) {
/* yPos = ((((i1-1)/1.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<3); i1 += 1) {
yPos = ((((i1-1)/1.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+2)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+8)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+2)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+50)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+56)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+50)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[0][1])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1071, S1065, S1068, S1062, S1070, S1064, S1067, S1061, S1069, S1063, S1066 */
{
{
{
{
{
{
{
{
{
{
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+195)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+201)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+195)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+51)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+57)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+51)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+75)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+81)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+75)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+3)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+9)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+3)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+171)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+177)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+171)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/1.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(1.000000e+00);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<0); i1 += 4) {
/* yPos = ((((i1-1)/1.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<3); i1 += 1) {
yPos = ((((i1-1)/1.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+99)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+105)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+99)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+123)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+129)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+123)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+147)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+153)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+147)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posEnd[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<0); i1 += 4) {
/* xPos = posEnd[0]; */
__m128d vec0 = _mm_load1_pd((&posEnd[0]));
__m128d vec0_2 = _mm_load1_pd((&posEnd[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<3); i1 += 1) {
xPos = posEnd[0];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+27)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+33)] = 0.000000e+00;
}
for (; (i1<=2); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+27)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[0][2])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1080, S1074, S1077, S1082, S1076, S1079, S1073, S1072, S1081, S1075, S1078 */
{
{
{
{
{
{
{
{
{
{
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+126)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+127)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+126)] = 0.000000e+00;
}
}
{
int i2 = 2;
for (; (i2<=2); i2 += 2) {
xPos = ((((i2-2)/1.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/1.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=3); i2 += 1) {
xPos = ((((i2-2)/1.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+198)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+199)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+198)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=2); i2 += 2) {
yPos = posBegin[1];
yPos = posBegin[1];
}
for (; (i2<=3); i2 += 1) {
yPos = posBegin[1];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+30)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+31)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+30)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+174)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+175)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+174)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+78)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+79)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+78)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+54)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+55)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+54)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+150)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+151)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+150)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+6)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+7)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+6)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+102)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+103)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+102)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[0][3])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1083, S1092, S1086, S1089, S1088, S1091, S1085, S1090, S1093, S1087, S1084 */
{
{
{
{
{
{
{
{
{
{
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+12)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+13)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+12)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+60)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+61)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+60)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+204)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+205)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+204)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+132)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+133)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+132)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+84)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+85)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+84)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=2); i2 += 2) {
yPos = posEnd[1];
yPos = posEnd[1];
}
for (; (i2<=3); i2 += 1) {
yPos = posEnd[1];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+36)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+37)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+36)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=2); i2 += 2) {
xPos = ((((i2-2)/1.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/1.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=3); i2 += 1) {
xPos = ((((i2-2)/1.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+180)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+181)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+180)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+156)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+157)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+156)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][0]);
int i2 = 2;
for (; (i2<=2); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+108)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+109)] = 0.000000e+00;
}
for (; (i2<=3); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[(i2+108)] = 0.000000e+00;
}
}
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
/* Statements in this Scop: S1094 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Send_1_p1 = (&buffer_Send[1][(i0*2)]);
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][(i0*24)]);
int i1 = 1;
for (; (i1<=1); i1 += 2) {
buffer_Send_1_p1[(i1-1)] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+3)];
buffer_Send_1_p1[i1] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+9)];
}
for (; (i1<=2); i1 += 1) {
buffer_Send_1_p1[(i1-1)] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+3)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
MPI_Isend(buffer_Send[1], 18, MPI_DOUBLE, neighbor_remoteRank[0][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
MPI_Irecv(buffer_Recv[0], 18, MPI_DOUBLE, neighbor_remoteRank[0][0], ((unsigned int)(neighbor_fragCommId[0][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Recv[0]) {
waitForMPIReq(&mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
/* Statements in this Scop: S1095 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i0*2)]);
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][(i0*24)]);
int i1 = 3;
for (; (i1<=3); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-10)] = buffer_Recv_0_p1[(i1-3)];
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-4)] = buffer_Recv_0_p1[(i1-2)];
}
for (; (i1<=4); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-10)] = buffer_Recv_0_p1[(i1-3)];
}
}
}
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Send[1]) {
waitForMPIReq(&mpiRequest_Send[1]);
reqOutstanding_Send[1] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
;
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][3]&&neighbor_isRemote[0][3])) {
MPI_Isend(&fieldData_LaplaceCoeff_GMRF[0][14], 1, mpiDatatype_9_2_24, neighbor_remoteRank[0][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][2]&&neighbor_isRemote[0][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff_GMRF[0][8], 1, mpiDatatype_9_2_24, neighbor_remoteRank[0][2], ((unsigned int)(neighbor_fragCommId[0][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Recv[2]) {
waitForMPIReq(&mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
;
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Send[3]) {
waitForMPIReq(&mpiRequest_Send[3]);
reqOutstanding_Send[3] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
/* Statements in this Scop: S1096 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][(i0*24)]);
double* buffer_Send_0_p1 = (&buffer_Send[0][(i0*4)]);
int i1 = 0;
for (; (i1<=2); i1 += 2) {
buffer_Send_0_p1[i1] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+3)];
buffer_Send_0_p1[(i1+1)] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+9)];
}
for (; (i1<=3); i1 += 1) {
buffer_Send_0_p1[i1] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+3)];
}
}
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
/* Statements in this Scop: S1097 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Send_1_p1 = (&buffer_Send[1][(i0*4)]);
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][(i0*24)]);
int i1 = 0;
for (; (i1<=2); i1 += 2) {
buffer_Send_1_p1[i1] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+2)];
buffer_Send_1_p1[(i1+1)] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+8)];
}
for (; (i1<=3); i1 += 1) {
buffer_Send_1_p1[i1] = fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+2)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
MPI_Isend(buffer_Send[0], 36, MPI_DOUBLE, neighbor_remoteRank[0][0], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][0]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[0]);
reqOutstanding_Send[0] = true;
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
MPI_Isend(buffer_Send[1], 36, MPI_DOUBLE, neighbor_remoteRank[0][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
MPI_Irecv(buffer_Recv[0], 36, MPI_DOUBLE, neighbor_remoteRank[0][0], ((unsigned int)(neighbor_fragCommId[0][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = true;
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
MPI_Irecv(buffer_Recv[1], 36, MPI_DOUBLE, neighbor_remoteRank[0][1], ((unsigned int)(neighbor_fragCommId[0][1]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[1]);
reqOutstanding_Recv[1] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Recv[0]) {
waitForMPIReq(&mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = false;
}
if (reqOutstanding_Recv[1]) {
waitForMPIReq(&mpiRequest_Recv[1]);
reqOutstanding_Recv[1] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
/* Statements in this Scop: S1098 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i0*4)]);
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][(i0*24)]);
int i1 = 1;
for (; (i1<=3); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-5)] = buffer_Recv_0_p1[(i1-1)];
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)+1)] = buffer_Recv_0_p1[i1];
}
for (; (i1<=4); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-5)] = buffer_Recv_0_p1[(i1-1)];
}
}
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
/* Statements in this Scop: S1099 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Recv_1_p1 = (&buffer_Recv[1][(i0*4)]);
double* fieldData_LaplaceCoeff_GMRF_0_p1 = (&fieldData_LaplaceCoeff_GMRF[0][(i0*24)]);
int i1 = 4;
for (; (i1<=6); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-20)] = buffer_Recv_1_p1[(i1-4)];
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-14)] = buffer_Recv_1_p1[(i1-3)];
}
for (; (i1<=7); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_0_p1[((i1*6)-20)] = buffer_Recv_1_p1[(i1-4)];
}
}
}
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Send[0]) {
waitForMPIReq(&mpiRequest_Send[0]);
reqOutstanding_Send[0] = false;
}
if (reqOutstanding_Send[1]) {
waitForMPIReq(&mpiRequest_Send[1]);
reqOutstanding_Send[1] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
;
;
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][2]&&neighbor_isRemote[0][2])) {
MPI_Isend(&fieldData_LaplaceCoeff_GMRF[0][13], 1, mpiDatatype_9_4_24, neighbor_remoteRank[0][2], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][2]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[2]);
reqOutstanding_Send[2] = true;
}
if ((neighbor_isValid[0][3]&&neighbor_isRemote[0][3])) {
MPI_Isend(&fieldData_LaplaceCoeff_GMRF[0][7], 1, mpiDatatype_9_4_24, neighbor_remoteRank[0][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][2]&&neighbor_isRemote[0][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff_GMRF[0][1], 1, mpiDatatype_9_4_24, neighbor_remoteRank[0][2], ((unsigned int)(neighbor_fragCommId[0][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = true;
}
if ((neighbor_isValid[0][3]&&neighbor_isRemote[0][3])) {
MPI_Irecv(&fieldData_LaplaceCoeff_GMRF[0][19], 1, mpiDatatype_9_4_24, neighbor_remoteRank[0][3], ((unsigned int)(neighbor_fragCommId[0][3]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[3]);
reqOutstanding_Recv[3] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Recv[2]) {
waitForMPIReq(&mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = false;
}
if (reqOutstanding_Recv[3]) {
waitForMPIReq(&mpiRequest_Recv[3]);
reqOutstanding_Recv[3] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
;
;
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if (reqOutstanding_Send[2]) {
waitForMPIReq(&mpiRequest_Send[2]);
reqOutstanding_Send[2] = false;
}
if (reqOutstanding_Send[3]) {
waitForMPIReq(&mpiRequest_Send[3]);
reqOutstanding_Send[3] = false;
}
}
}
}