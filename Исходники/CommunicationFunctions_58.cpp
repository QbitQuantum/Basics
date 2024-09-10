void exchrhs_gmrfData_8(unsigned int slot) {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[0]) {
if ((!neighbor_isValid[0][0])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S589, S588, S590 */
{
{
{
int i1 = 0;
for (; (i1<(1&(~1))); i1 += 1) {
yPos = (((i1/2.560000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(2.560000e+02);
__m128d vec4 = _mm_set1_pd(yPos);
for (; (i1<254); i1 += 4) {
/* yPos = (((i1/2.560000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec2 = _mm_load1_pd((&posEnd[1]));
__m128d vec2_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec3 = _mm_load1_pd((&posBegin[1]));
__m128d vec3_2 = _mm_load1_pd((&posBegin[1]));
vec4 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(vec0, vec1), _mm_sub_pd(vec2, vec3)), vec3);
vec4 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(vec0_2, vec1), _mm_sub_pd(vec2_2, vec3_2)), vec3_2);
}
for (; (i1<257); i1 += 1) {
yPos = (((i1/2.560000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
{
int i1 = 0;
for (; (i1<(1&(~1))); i1 += 1) {
xPos = posBegin[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<254); i1 += 4) {
/* xPos = posBegin[0]; */
__m128d vec0 = _mm_load1_pd((&posBegin[0]));
__m128d vec0_2 = _mm_load1_pd((&posBegin[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<257); i1 += 1) {
xPos = posBegin[0];
}
}
}
{
double* fieldData_RHS_GMRF_8_p1 = (&fieldData_RHS_GMRF[8][0]);
int i1 = 0;
for (; (i1<=255); i1 += 2) {
fieldData_RHS_GMRF_8_p1[(i1*258)] = 0.000000e+00;
fieldData_RHS_GMRF_8_p1[((i1*258)+258)] = 0.000000e+00;
}
for (; (i1<=256); i1 += 1) {
fieldData_RHS_GMRF_8_p1[(i1*258)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[0][1])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S592, S591, S593 */
{
{
{
int i1 = 0;
for (; (i1<(1&(~1))); i1 += 1) {
yPos = (((i1/2.560000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(2.560000e+02);
__m128d vec4 = _mm_set1_pd(yPos);
for (; (i1<254); i1 += 4) {
/* yPos = (((i1/2.560000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec2 = _mm_load1_pd((&posEnd[1]));
__m128d vec2_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec3 = _mm_load1_pd((&posBegin[1]));
__m128d vec3_2 = _mm_load1_pd((&posBegin[1]));
vec4 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(vec0, vec1), _mm_sub_pd(vec2, vec3)), vec3);
vec4 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(vec0_2, vec1), _mm_sub_pd(vec2_2, vec3_2)), vec3_2);
}
for (; (i1<257); i1 += 1) {
yPos = (((i1/2.560000e+02)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
{
double* fieldData_RHS_GMRF_8_p1 = (&fieldData_RHS_GMRF[8][0]);
int i1 = 0;
for (; (i1<=255); i1 += 2) {
fieldData_RHS_GMRF_8_p1[((i1*258)+256)] = 0.000000e+00;
fieldData_RHS_GMRF_8_p1[((i1*258)+514)] = 0.000000e+00;
}
for (; (i1<=256); i1 += 1) {
fieldData_RHS_GMRF_8_p1[((i1*258)+256)] = 0.000000e+00;
}
}
}
{
int i1 = 0;
for (; (i1<(1&(~1))); i1 += 1) {
xPos = posEnd[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<254); i1 += 4) {
/* xPos = posEnd[0]; */
__m128d vec0 = _mm_load1_pd((&posEnd[0]));
__m128d vec0_2 = _mm_load1_pd((&posEnd[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<257); i1 += 1) {
xPos = posEnd[0];
}
}
}
}
}
if ((!neighbor_isValid[0][2])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S595, S594, S596 */
{
{
{
double* fieldData_RHS_GMRF_8_p1 = (&fieldData_RHS_GMRF[8][0]);
int i2 = 0;
for (; (i2<=255); i2 += 2) {
fieldData_RHS_GMRF_8_p1[i2] = 0.000000e+00;
fieldData_RHS_GMRF_8_p1[(i2+1)] = 0.000000e+00;
}
for (; (i2<=256); i2 += 1) {
fieldData_RHS_GMRF_8_p1[i2] = 0.000000e+00;
}
}
{
int i2 = 0;
for (; (i2<=255); i2 += 2) {
xPos = (((i2/2.560000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2+1)/2.560000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=256); i2 += 1) {
xPos = (((i2/2.560000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
int i2 = 0;
for (; (i2<=255); i2 += 2) {
yPos = posBegin[1];
yPos = posBegin[1];
}
for (; (i2<=256); i2 += 1) {
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
/* Statements in this Scop: S598, S597, S599 */
{
{
{
int i2 = 0;
for (; (i2<=255); i2 += 2) {
xPos = (((i2/2.560000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2+1)/2.560000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=256); i2 += 1) {
xPos = (((i2/2.560000e+02)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
{
int i2 = 0;
for (; (i2<=255); i2 += 2) {
yPos = posEnd[1];
yPos = posEnd[1];
}
for (; (i2<=256); i2 += 1) {
yPos = posEnd[1];
}
}
}
{
double* fieldData_RHS_GMRF_8_p1 = (&fieldData_RHS_GMRF[8][0]);
int i2 = 0;
for (; (i2<=255); i2 += 2) {
fieldData_RHS_GMRF_8_p1[(i2+66048)] = 0.000000e+00;
fieldData_RHS_GMRF_8_p1[(i2+66049)] = 0.000000e+00;
}
for (; (i2<=256); i2 += 1) {
fieldData_RHS_GMRF_8_p1[(i2+66048)] = 0.000000e+00;
}
}
}
}
}
}
}
}