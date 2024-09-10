void exchlaplacecoeff_gmrfData_5(unsigned int slot) {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((!neighbor_isValid[0][0])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1306, S1309, S1300, S1308, S1302, S1305, S1310, S1304, S1307, S1301, S1303 */
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
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+6302)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+6338)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+6302)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+3782)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+3818)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+3782)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+7562)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+7598)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+7562)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+38)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2522)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2558)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2522)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posBegin[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<31); i1 += 4) {
/* xPos = posBegin[0]; */
__m128d vec0 = _mm_load1_pd((&posBegin[0]));
__m128d vec0_2 = _mm_load1_pd((&posBegin[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<34); i1 += 1) {
xPos = posBegin[0];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+8822)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+8858)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+8822)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+1262)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+1298)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+1262)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/3.200000e+01)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(3.200000e+01);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<31); i1 += 4) {
/* yPos = ((((i1-1)/3.200000e+01)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<34); i1 += 1) {
yPos = ((((i1-1)/3.200000e+01)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+5042)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+5078)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+5042)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+10082)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+10118)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+10082)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[0][1])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1312, S1320, S1314, S1317, S1311, S1319, S1313, S1316, S1321, S1315, S1318 */
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
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+1294)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+1330)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+1294)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+5074)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+5110)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+5074)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+8854)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+8890)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+8854)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2554)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2590)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+2554)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/3.200000e+01)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(3.200000e+01);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<31); i1 += 4) {
/* yPos = ((((i1-1)/3.200000e+01)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<34); i1 += 1) {
yPos = ((((i1-1)/3.200000e+01)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+34)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+70)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+34)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+3814)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+3850)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+3814)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+7594)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+7630)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+7594)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+6334)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+6370)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+6334)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posEnd[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<31); i1 += 4) {
/* xPos = posEnd[0]; */
__m128d vec0 = _mm_load1_pd((&posEnd[0]));
__m128d vec0_2 = _mm_load1_pd((&posEnd[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<34); i1 += 1) {
xPos = posEnd[0];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i1 = 1;
for (; (i1<=32); i1 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+10114)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+10150)] = 0.000000e+00;
}
for (; (i1<=33); i1 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i1*36)+10114)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[0][2])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1327, S1332, S1326, S1329, S1323, S1322, S1331, S1325, S1328, S1330, S1324 */
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
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+5076)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+5077)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+5076)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+8856)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+8857)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+8856)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+6336)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+6337)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+6336)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+7596)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+7597)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+7596)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=33); i2 += 2) {
xPos = ((((i2-2)/3.200000e+01)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/3.200000e+01)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=34); i2 += 1) {
xPos = ((((i2-2)/3.200000e+01)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+36)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+37)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+36)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+2556)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+2557)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+2556)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+10116)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+10117)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+10116)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+3816)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+3817)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+3816)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+1296)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+1297)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+1296)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=33); i2 += 2) {
yPos = posBegin[1];
yPos = posBegin[1];
}
for (; (i2<=34); i2 += 1) {
yPos = posBegin[1];
}
}
}
}
}
if ((!neighbor_isValid[0][3])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S1338, S1341, S1335, S1340, S1343, S1337, S1334, S1333, S1342, S1336, S1339 */
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
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+7488)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+7489)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+7488)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+2448)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+2449)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+2448)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+11268)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+11269)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+11268)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=33); i2 += 2) {
yPos = posEnd[1];
yPos = posEnd[1];
}
for (; (i2<=34); i2 += 1) {
yPos = posEnd[1];
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+10008)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+10009)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+10008)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+6228)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+6229)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+6228)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+8748)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+8749)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+8748)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=33); i2 += 2) {
xPos = ((((i2-2)/3.200000e+01)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/3.200000e+01)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=34); i2 += 1) {
xPos = ((((i2-2)/3.200000e+01)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+3708)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+3709)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+3708)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+1188)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+1189)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+1188)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][0]);
int i2 = 2;
for (; (i2<=33); i2 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+4968)] = 0.000000e+00;
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+4969)] = 0.000000e+00;
}
for (; (i2<=34); i2 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[(i2+4968)] = 0.000000e+00;
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
/* Statements in this Scop: S1344 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i3*1260)]);
double* buffer_Send_1_p1 = (&buffer_Send[1][(i3*33)]);
int i4 = 1;
for (; (i4<=32); i4 += 2) {
buffer_Send_1_p1[(i4-1)] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+34)];
buffer_Send_1_p1[i4] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+70)];
}
for (; (i4<=33); i4 += 1) {
buffer_Send_1_p1[(i4-1)] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+34)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
MPI_Isend(buffer_Send[1], 297, MPI_DOUBLE, neighbor_remoteRank[0][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
MPI_Irecv(buffer_Recv[0], 297, MPI_DOUBLE, neighbor_remoteRank[0][0], ((unsigned int)(neighbor_fragCommId[0][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
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
/* Statements in this Scop: S1345 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i3*1260)]);
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i3*33)]);
int i4 = 3;
for (; (i4<=34); i4 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-70)] = buffer_Recv_0_p1[(i4-3)];
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-34)] = buffer_Recv_0_p1[(i4-2)];
}
for (; (i4<=35); i4 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-70)] = buffer_Recv_0_p1[(i4-3)];
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
MPI_Isend(&fieldData_LaplaceCoeff_GMRF[5][1190], 1, mpiDatatype_9_33_1260, neighbor_remoteRank[0][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][2]&&neighbor_isRemote[0][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff_GMRF[5][38], 1, mpiDatatype_9_33_1260, neighbor_remoteRank[0][2], ((unsigned int)(neighbor_fragCommId[0][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
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
/* Statements in this Scop: S1346 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i3*1260)]);
double* buffer_Send_0_p1 = (&buffer_Send[0][(i3*35)]);
int i4 = 0;
for (; (i4<=33); i4 += 2) {
buffer_Send_0_p1[i4] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+3)];
buffer_Send_0_p1[(i4+1)] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+39)];
}
for (; (i4<=34); i4 += 1) {
buffer_Send_0_p1[i4] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+3)];
}
}
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
/* Statements in this Scop: S1347 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i3*1260)]);
double* buffer_Send_1_p1 = (&buffer_Send[1][(i3*35)]);
int i4 = 0;
for (; (i4<=33); i4 += 2) {
buffer_Send_1_p1[i4] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+33)];
buffer_Send_1_p1[(i4+1)] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+69)];
}
for (; (i4<=34); i4 += 1) {
buffer_Send_1_p1[i4] = fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+33)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
MPI_Isend(buffer_Send[0], 315, MPI_DOUBLE, neighbor_remoteRank[0][0], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][0]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[0]);
reqOutstanding_Send[0] = true;
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
MPI_Isend(buffer_Send[1], 315, MPI_DOUBLE, neighbor_remoteRank[0][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][0]&&neighbor_isRemote[0][0])) {
MPI_Irecv(buffer_Recv[0], 315, MPI_DOUBLE, neighbor_remoteRank[0][0], ((unsigned int)(neighbor_fragCommId[0][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = true;
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
MPI_Irecv(buffer_Recv[1], 315, MPI_DOUBLE, neighbor_remoteRank[0][1], ((unsigned int)(neighbor_fragCommId[0][1]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[1]);
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
/* Statements in this Scop: S1348 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i3*1260)]);
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i3*35)]);
int i4 = 1;
for (; (i4<=34); i4 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-35)] = buffer_Recv_0_p1[(i4-1)];
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)+1)] = buffer_Recv_0_p1[i4];
}
for (; (i4<=35); i4 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-35)] = buffer_Recv_0_p1[(i4-1)];
}
}
}
if ((neighbor_isValid[0][1]&&neighbor_isRemote[0][1])) {
/* Statements in this Scop: S1349 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_GMRF_5_p1 = (&fieldData_LaplaceCoeff_GMRF[5][(i3*1260)]);
double* buffer_Recv_1_p1 = (&buffer_Recv[1][(i3*35)]);
int i4 = 35;
for (; (i4<=68); i4 += 2) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-1225)] = buffer_Recv_1_p1[(i4-35)];
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-1189)] = buffer_Recv_1_p1[(i4-34)];
}
for (; (i4<=69); i4 += 1) {
fieldData_LaplaceCoeff_GMRF_5_p1[((i4*36)-1225)] = buffer_Recv_1_p1[(i4-35)];
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
MPI_Isend(&fieldData_LaplaceCoeff_GMRF[5][73], 1, mpiDatatype_9_35_1260, neighbor_remoteRank[0][2], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][2]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[2]);
reqOutstanding_Send[2] = true;
}
if ((neighbor_isValid[0][3]&&neighbor_isRemote[0][3])) {
MPI_Isend(&fieldData_LaplaceCoeff_GMRF[5][1153], 1, mpiDatatype_9_35_1260, neighbor_remoteRank[0][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[0][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((neighbor_isValid[0][2]&&neighbor_isRemote[0][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff_GMRF[5][1], 1, mpiDatatype_9_35_1260, neighbor_remoteRank[0][2], ((unsigned int)(neighbor_fragCommId[0][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = true;
}
if ((neighbor_isValid[0][3]&&neighbor_isRemote[0][3])) {
MPI_Irecv(&fieldData_LaplaceCoeff_GMRF[5][1225], 1, mpiDatatype_9_35_1260, neighbor_remoteRank[0][3], ((unsigned int)(neighbor_fragCommId[0][3]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[3]);
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