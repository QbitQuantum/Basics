void exchlaplacecoeffData_7(unsigned int slot) {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((!neighbor_isValid[1][0])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S956, S958, S952, S955, S960, S954, S957, S951, S959, S950, S953 */
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
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+138338)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+138470)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+138338)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+34586)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+34718)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+34586)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+103754)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+103886)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+103754)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+2)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+134)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+2)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+69170)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+69302)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+69170)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+121046)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+121178)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+121046)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+51878)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+52010)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+51878)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posBegin[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<127); i1 += 4) {
/* xPos = posBegin[0]; */
__m128d vec0 = _mm_load1_pd((&posBegin[0]));
__m128d vec0_2 = _mm_load1_pd((&posBegin[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<130); i1 += 1) {
xPos = posBegin[0];
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+86462)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+86594)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+86462)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+17294)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+17426)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+17294)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/1.280000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(1.280000e+02);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<127); i1 += 4) {
/* yPos = ((((i1-1)/1.280000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<130); i1 += 1) {
yPos = ((((i1-1)/1.280000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
}
}
if ((!neighbor_isValid[1][1])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S962, S961, S970, S964, S967, S966, S969, S963, S971, S965, S968 */
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
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+121174)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+121306)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+121174)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+138466)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+138598)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+138466)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/1.280000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(1.280000e+02);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<127); i1 += 4) {
/* yPos = ((((i1-1)/1.280000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<130); i1 += 1) {
yPos = ((((i1-1)/1.280000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+103882)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+104014)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+103882)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posEnd[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<127); i1 += 4) {
/* xPos = posEnd[0]; */
__m128d vec0 = _mm_load1_pd((&posEnd[0]));
__m128d vec0_2 = _mm_load1_pd((&posEnd[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<130); i1 += 1) {
xPos = posEnd[0];
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+130)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+262)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+130)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+69298)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+69430)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+69298)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+52006)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+52138)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+52006)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+86590)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+86722)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+86590)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+34714)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+34846)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+34714)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i1 = 1;
for (; (i1<=128); i1 += 2) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+17422)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[((i1*132)+17554)] = 0.000000e+00;
}
for (; (i1<=129); i1 += 1) {
fieldData_LaplaceCoeff_7_p1[((i1*132)+17422)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[1][2])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S982, S976, S979, S973, S972, S981, S975, S978, S977, S980, S974 */
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
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+138468)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+138469)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+138468)] = 0.000000e+00;
}
}
{
int i2 = 2;
for (; (i2<=129); i2 += 2) {
xPos = ((((i2-2)/1.280000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/1.280000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=130); i2 += 1) {
xPos = ((((i2-2)/1.280000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+34716)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+34717)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+34716)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+17424)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+17425)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+17424)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+132)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+133)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+132)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+86592)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+86593)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+86592)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+52008)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+52009)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+52008)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+103884)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+103885)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+103884)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+121176)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+121177)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+121176)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=129); i2 += 2) {
yPos = posBegin[1];
yPos = posBegin[1];
}
for (; (i2<=130); i2 += 1) {
yPos = posBegin[1];
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+69300)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+69301)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+69300)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[1][3])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S988, S991, S985, S990, S984, S993, S987, S983, S992, S986, S989 */
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
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+138072)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+138073)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+138072)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+34320)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+34321)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+34320)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+155364)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+155365)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+155364)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+51612)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+51613)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+51612)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=129); i2 += 2) {
yPos = posEnd[1];
yPos = posEnd[1];
}
for (; (i2<=130); i2 += 1) {
yPos = posEnd[1];
}
}
}
{
int i2 = 2;
for (; (i2<=129); i2 += 2) {
xPos = ((((i2-2)/1.280000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/1.280000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=130); i2 += 1) {
xPos = ((((i2-2)/1.280000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+103488)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+103489)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+103488)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+68904)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+68905)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+68904)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+17028)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+17029)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+17028)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+120780)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+120781)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+120780)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][0]);
int i2 = 2;
for (; (i2<=129); i2 += 2) {
fieldData_LaplaceCoeff_7_p1[(i2+86196)] = 0.000000e+00;
fieldData_LaplaceCoeff_7_p1[(i2+86197)] = 0.000000e+00;
}
for (; (i2<=130); i2 += 1) {
fieldData_LaplaceCoeff_7_p1[(i2+86196)] = 0.000000e+00;
}
}
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
/* Statements in this Scop: S994 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* buffer_Send_1_p1 = (&buffer_Send[1][(i3*129)]);
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][(i3*17292)]);
int i4 = 1;
for (; (i4<=128); i4 += 2) {
buffer_Send_1_p1[(i4-1)] = fieldData_LaplaceCoeff_7_p1[((i4*132)+130)];
buffer_Send_1_p1[i4] = fieldData_LaplaceCoeff_7_p1[((i4*132)+262)];
}
for (; (i4<=129); i4 += 1) {
buffer_Send_1_p1[(i4-1)] = fieldData_LaplaceCoeff_7_p1[((i4*132)+130)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
MPI_Isend(buffer_Send[1], 1161, MPI_DOUBLE, neighbor_remoteRank[1][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
MPI_Irecv(buffer_Recv[0], 1161, MPI_DOUBLE, neighbor_remoteRank[1][0], ((unsigned int)(neighbor_fragCommId[1][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if (reqOutstanding_Recv[0]) {
waitForMPIReq(&mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
/* Statements in this Scop: S995 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i3*129)]);
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][(i3*17292)]);
int i4 = 3;
for (; (i4<=130); i4 += 2) {
fieldData_LaplaceCoeff_7_p1[((i4*132)-262)] = buffer_Recv_0_p1[(i4-3)];
fieldData_LaplaceCoeff_7_p1[((i4*132)-130)] = buffer_Recv_0_p1[(i4-2)];
}
for (; (i4<=131); i4 += 1) {
fieldData_LaplaceCoeff_7_p1[((i4*132)-262)] = buffer_Recv_0_p1[(i4-3)];
}
}
}
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if (reqOutstanding_Send[1]) {
waitForMPIReq(&mpiRequest_Send[1]);
reqOutstanding_Send[1] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
;
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][3]&&neighbor_isRemote[1][3])) {
MPI_Isend(&fieldData_LaplaceCoeff[7][17030], 1, mpiDatatype_9_129_17292, neighbor_remoteRank[1][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][2]&&neighbor_isRemote[1][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff[7][134], 1, mpiDatatype_9_129_17292, neighbor_remoteRank[1][2], ((unsigned int)(neighbor_fragCommId[1][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if (reqOutstanding_Recv[2]) {
waitForMPIReq(&mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
;
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if (reqOutstanding_Send[3]) {
waitForMPIReq(&mpiRequest_Send[3]);
reqOutstanding_Send[3] = false;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
/* Statements in this Scop: S996 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][(i3*17292)]);
double* buffer_Send_0_p1 = (&buffer_Send[0][(i3*131)]);
int i4 = 0;
for (; (i4<=129); i4 += 2) {
buffer_Send_0_p1[i4] = fieldData_LaplaceCoeff_7_p1[((i4*132)+3)];
buffer_Send_0_p1[(i4+1)] = fieldData_LaplaceCoeff_7_p1[((i4*132)+135)];
}
for (; (i4<=130); i4 += 1) {
buffer_Send_0_p1[i4] = fieldData_LaplaceCoeff_7_p1[((i4*132)+3)];
}
}
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
/* Statements in this Scop: S997 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* buffer_Send_1_p1 = (&buffer_Send[1][(i3*131)]);
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][(i3*17292)]);
int i4 = 0;
for (; (i4<=129); i4 += 2) {
buffer_Send_1_p1[i4] = fieldData_LaplaceCoeff_7_p1[((i4*132)+129)];
buffer_Send_1_p1[(i4+1)] = fieldData_LaplaceCoeff_7_p1[((i4*132)+261)];
}
for (; (i4<=130); i4 += 1) {
buffer_Send_1_p1[i4] = fieldData_LaplaceCoeff_7_p1[((i4*132)+129)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
MPI_Isend(buffer_Send[0], 1179, MPI_DOUBLE, neighbor_remoteRank[1][0], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][0]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[0]);
reqOutstanding_Send[0] = true;
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
MPI_Isend(buffer_Send[1], 1179, MPI_DOUBLE, neighbor_remoteRank[1][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
MPI_Irecv(buffer_Recv[0], 1179, MPI_DOUBLE, neighbor_remoteRank[1][0], ((unsigned int)(neighbor_fragCommId[1][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = true;
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
MPI_Irecv(buffer_Recv[1], 1179, MPI_DOUBLE, neighbor_remoteRank[1][1], ((unsigned int)(neighbor_fragCommId[1][1]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[1]);
reqOutstanding_Recv[1] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
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
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
/* Statements in this Scop: S998 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i3*131)]);
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][(i3*17292)]);
int i4 = 1;
for (; (i4<=130); i4 += 2) {
fieldData_LaplaceCoeff_7_p1[((i4*132)-131)] = buffer_Recv_0_p1[(i4-1)];
fieldData_LaplaceCoeff_7_p1[((i4*132)+1)] = buffer_Recv_0_p1[i4];
}
for (; (i4<=131); i4 += 1) {
fieldData_LaplaceCoeff_7_p1[((i4*132)-131)] = buffer_Recv_0_p1[(i4-1)];
}
}
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
/* Statements in this Scop: S999 */
for (int i3 = 0; (i3<=8); i3 += 1) {
double* buffer_Recv_1_p1 = (&buffer_Recv[1][(i3*131)]);
double* fieldData_LaplaceCoeff_7_p1 = (&fieldData_LaplaceCoeff[7][(i3*17292)]);
int i4 = 131;
for (; (i4<=260); i4 += 2) {
fieldData_LaplaceCoeff_7_p1[((i4*132)-17161)] = buffer_Recv_1_p1[(i4-131)];
fieldData_LaplaceCoeff_7_p1[((i4*132)-17029)] = buffer_Recv_1_p1[(i4-130)];
}
for (; (i4<=261); i4 += 1) {
fieldData_LaplaceCoeff_7_p1[((i4*132)-17161)] = buffer_Recv_1_p1[(i4-131)];
}
}
}
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
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
if (isValidForSubdomain[1]) {
;
;
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][2]&&neighbor_isRemote[1][2])) {
MPI_Isend(&fieldData_LaplaceCoeff[7][265], 1, mpiDatatype_9_131_17292, neighbor_remoteRank[1][2], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][2]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[2]);
reqOutstanding_Send[2] = true;
}
if ((neighbor_isValid[1][3]&&neighbor_isRemote[1][3])) {
MPI_Isend(&fieldData_LaplaceCoeff[7][16897], 1, mpiDatatype_9_131_17292, neighbor_remoteRank[1][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][2]&&neighbor_isRemote[1][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff[7][1], 1, mpiDatatype_9_131_17292, neighbor_remoteRank[1][2], ((unsigned int)(neighbor_fragCommId[1][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = true;
}
if ((neighbor_isValid[1][3]&&neighbor_isRemote[1][3])) {
MPI_Irecv(&fieldData_LaplaceCoeff[7][17161], 1, mpiDatatype_9_131_17292, neighbor_remoteRank[1][3], ((unsigned int)(neighbor_fragCommId[1][3]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[3]);
reqOutstanding_Recv[3] = true;
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
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
if (isValidForSubdomain[1]) {
;
;
}
}
;
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
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