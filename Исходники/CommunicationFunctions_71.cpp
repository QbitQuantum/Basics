void exchlaplacecoeffData_2(unsigned int slot) {
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((!neighbor_isValid[1][0])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S710, S704, S707, S701, S709, S700, S703, S706, S708, S702, S705 */
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
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+394)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+402)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+394)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+226)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+234)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+226)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+170)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+178)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+170)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+58)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+66)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+58)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+450)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+458)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+450)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+114)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+122)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+114)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/4.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(4.000000e+00);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<3); i1 += 4) {
/* yPos = ((((i1-1)/4.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<6); i1 += 1) {
yPos = ((((i1-1)/4.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+2)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+10)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+2)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+338)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+346)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+338)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+282)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+290)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+282)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posBegin[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<3); i1 += 4) {
/* xPos = posBegin[0]; */
__m128d vec0 = _mm_load1_pd((&posBegin[0]));
__m128d vec0_2 = _mm_load1_pd((&posBegin[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<6); i1 += 1) {
xPos = posBegin[0];
}
}
}
}
}
if ((!neighbor_isValid[1][1])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S716, S719, S713, S721, S715, S718, S712, S711, S720, S714, S717 */
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
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
yPos = ((((i1-1)/4.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
__m128d vec1 = _mm_set1_pd(1.000000e+00);
__m128d vec2 = _mm_set1_pd(4.000000e+00);
__m128d vec5 = _mm_set1_pd(yPos);
for (; (i1<3); i1 += 4) {
/* yPos = ((((i1-1)/4.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]); */
__m128d vec0 = _mm_set_pd(i1+1,i1);
__m128d vec0_2 = _mm_set_pd(i1+1,i1);
__m128d vec3 = _mm_load1_pd((&posEnd[1]));
__m128d vec3_2 = _mm_load1_pd((&posEnd[1]));
__m128d vec4 = _mm_load1_pd((&posBegin[1]));
__m128d vec4_2 = _mm_load1_pd((&posBegin[1]));
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0, vec1), vec2), _mm_sub_pd(vec3, vec4)), vec4);
vec5 = _mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_sub_pd(vec0_2, vec1), vec2), _mm_sub_pd(vec3_2, vec4_2)), vec4_2);
}
for (; (i1<6); i1 += 1) {
yPos = ((((i1-1)/4.000000e+00)*(posEnd[1]-posBegin[1]))+posBegin[1]);
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+454)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+462)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+454)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+230)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+238)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+230)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+118)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+126)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+118)] = 0.000000e+00;
}
}
}
{
int i1 = 1;
for (; (i1<(2&(~1))); i1 += 1) {
xPos = posEnd[0];
}
__m128d vec1 = _mm_set1_pd(xPos);
for (; (i1<3); i1 += 4) {
/* xPos = posEnd[0]; */
__m128d vec0 = _mm_load1_pd((&posEnd[0]));
__m128d vec0_2 = _mm_load1_pd((&posEnd[0]));
vec1 = vec0;
vec1 = vec0_2;
}
for (; (i1<6); i1 += 1) {
xPos = posEnd[0];
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+286)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+294)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+286)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+342)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+350)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+342)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+398)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+406)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+398)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+174)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+182)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+174)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+62)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+70)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+62)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+6)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[((i1*8)+14)] = 0.000000e+00;
}
for (; (i1<=5); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)+6)] = 0.000000e+00;
}
}
}
}
}
if ((!neighbor_isValid[1][2])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S722, S731, S725, S728, S727, S730, S724, S732, S726, S729, S723 */
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
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+344)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+345)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+344)] = 0.000000e+00;
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+400)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+401)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+400)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+120)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+121)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+120)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+8)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+9)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+8)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+64)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+65)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+64)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+456)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+457)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+456)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+232)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+233)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+232)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+288)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+289)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+288)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=5); i2 += 2) {
xPos = ((((i2-2)/4.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/4.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=6); i2 += 1) {
xPos = ((((i2-2)/4.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+176)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+177)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+176)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=5); i2 += 2) {
yPos = posBegin[1];
yPos = posBegin[1];
}
for (; (i2<=6); i2 += 1) {
yPos = posBegin[1];
}
}
}
}
}
if ((!neighbor_isValid[1][3])) {
{
double xPos;
double yPos;
/* Statements in this Scop: S743, S737, S733, S742, S736, S739, S738, S741, S735, S740, S734 */
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
int i2 = 2;
for (; (i2<=5); i2 += 2) {
yPos = posEnd[1];
yPos = posEnd[1];
}
for (; (i2<=6); i2 += 1) {
yPos = posEnd[1];
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+376)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+377)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+376)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+488)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+489)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+488)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+40)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+41)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+40)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+208)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+209)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+208)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+152)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+153)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+152)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+320)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+321)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+320)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+432)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+433)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+432)] = 0.000000e+00;
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+96)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+97)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+96)] = 0.000000e+00;
}
}
}
{
int i2 = 2;
for (; (i2<=5); i2 += 2) {
xPos = ((((i2-2)/4.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
xPos = ((((i2-1)/4.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
for (; (i2<=6); i2 += 1) {
xPos = ((((i2-2)/4.000000e+00)*(posEnd[0]-posBegin[0]))+posBegin[0]);
}
}
}
{
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][0]);
int i2 = 2;
for (; (i2<=5); i2 += 2) {
fieldData_LaplaceCoeff_2_p1[(i2+264)] = 0.000000e+00;
fieldData_LaplaceCoeff_2_p1[(i2+265)] = 0.000000e+00;
}
for (; (i2<=6); i2 += 1) {
fieldData_LaplaceCoeff_2_p1[(i2+264)] = 0.000000e+00;
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
/* Statements in this Scop: S744 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][(i0*56)]);
double* buffer_Send_1_p1 = (&buffer_Send[1][(i0*5)]);
int i1 = 1;
for (; (i1<=4); i1 += 2) {
buffer_Send_1_p1[(i1-1)] = fieldData_LaplaceCoeff_2_p1[((i1*8)+6)];
buffer_Send_1_p1[i1] = fieldData_LaplaceCoeff_2_p1[((i1*8)+14)];
}
for (; (i1<=5); i1 += 1) {
buffer_Send_1_p1[(i1-1)] = fieldData_LaplaceCoeff_2_p1[((i1*8)+6)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
MPI_Isend(buffer_Send[1], 45, MPI_DOUBLE, neighbor_remoteRank[1][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
MPI_Irecv(buffer_Recv[0], 45, MPI_DOUBLE, neighbor_remoteRank[1][0], ((unsigned int)(neighbor_fragCommId[1][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
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
/* Statements in this Scop: S745 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i0*5)]);
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][(i0*56)]);
int i1 = 3;
for (; (i1<=6); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)-14)] = buffer_Recv_0_p1[(i1-3)];
fieldData_LaplaceCoeff_2_p1[((i1*8)-6)] = buffer_Recv_0_p1[(i1-2)];
}
for (; (i1<=7); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)-14)] = buffer_Recv_0_p1[(i1-3)];
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
MPI_Isend(&fieldData_LaplaceCoeff[2][42], 1, mpiDatatype_9_5_56, neighbor_remoteRank[1][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][2]&&neighbor_isRemote[1][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff[2][10], 1, mpiDatatype_9_5_56, neighbor_remoteRank[1][2], ((unsigned int)(neighbor_fragCommId[1][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
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
/* Statements in this Scop: S746 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][(i0*56)]);
double* buffer_Send_0_p1 = (&buffer_Send[0][(i0*7)]);
int i1 = 0;
for (; (i1<=5); i1 += 2) {
buffer_Send_0_p1[i1] = fieldData_LaplaceCoeff_2_p1[((i1*8)+3)];
buffer_Send_0_p1[(i1+1)] = fieldData_LaplaceCoeff_2_p1[((i1*8)+11)];
}
for (; (i1<=6); i1 += 1) {
buffer_Send_0_p1[i1] = fieldData_LaplaceCoeff_2_p1[((i1*8)+3)];
}
}
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
/* Statements in this Scop: S747 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][(i0*56)]);
double* buffer_Send_1_p1 = (&buffer_Send[1][(i0*7)]);
int i1 = 0;
for (; (i1<=5); i1 += 2) {
buffer_Send_1_p1[i1] = fieldData_LaplaceCoeff_2_p1[((i1*8)+5)];
buffer_Send_1_p1[(i1+1)] = fieldData_LaplaceCoeff_2_p1[((i1*8)+13)];
}
for (; (i1<=6); i1 += 1) {
buffer_Send_1_p1[i1] = fieldData_LaplaceCoeff_2_p1[((i1*8)+5)];
}
}
}
}
}
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
MPI_Isend(buffer_Send[0], 63, MPI_DOUBLE, neighbor_remoteRank[1][0], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][0]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[0]);
reqOutstanding_Send[0] = true;
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
MPI_Isend(buffer_Send[1], 63, MPI_DOUBLE, neighbor_remoteRank[1][1], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][1]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[1]);
reqOutstanding_Send[1] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][0]&&neighbor_isRemote[1][0])) {
MPI_Irecv(buffer_Recv[0], 63, MPI_DOUBLE, neighbor_remoteRank[1][0], ((unsigned int)(neighbor_fragCommId[1][0]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[0]);
reqOutstanding_Recv[0] = true;
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
MPI_Irecv(buffer_Recv[1], 63, MPI_DOUBLE, neighbor_remoteRank[1][1], ((unsigned int)(neighbor_fragCommId[1][1]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[1]);
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
/* Statements in this Scop: S748 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Recv_0_p1 = (&buffer_Recv[0][(i0*7)]);
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][(i0*56)]);
int i1 = 1;
for (; (i1<=6); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)-7)] = buffer_Recv_0_p1[(i1-1)];
fieldData_LaplaceCoeff_2_p1[((i1*8)+1)] = buffer_Recv_0_p1[i1];
}
for (; (i1<=7); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)-7)] = buffer_Recv_0_p1[(i1-1)];
}
}
}
if ((neighbor_isValid[1][1]&&neighbor_isRemote[1][1])) {
/* Statements in this Scop: S749 */
for (int i0 = 0; (i0<=8); i0 += 1) {
double* buffer_Recv_1_p1 = (&buffer_Recv[1][(i0*7)]);
double* fieldData_LaplaceCoeff_2_p1 = (&fieldData_LaplaceCoeff[2][(i0*56)]);
int i1 = 7;
for (; (i1<=12); i1 += 2) {
fieldData_LaplaceCoeff_2_p1[((i1*8)-49)] = buffer_Recv_1_p1[(i1-7)];
fieldData_LaplaceCoeff_2_p1[((i1*8)-41)] = buffer_Recv_1_p1[(i1-6)];
}
for (; (i1<=13); i1 += 1) {
fieldData_LaplaceCoeff_2_p1[((i1*8)-49)] = buffer_Recv_1_p1[(i1-7)];
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
MPI_Isend(&fieldData_LaplaceCoeff[2][17], 1, mpiDatatype_9_7_56, neighbor_remoteRank[1][2], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][2]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[2]);
reqOutstanding_Send[2] = true;
}
if ((neighbor_isValid[1][3]&&neighbor_isRemote[1][3])) {
MPI_Isend(&fieldData_LaplaceCoeff[2][33], 1, mpiDatatype_9_7_56, neighbor_remoteRank[1][3], ((unsigned int)commId << 16) + ((unsigned int)(neighbor_fragCommId[1][3]) & 0x0000ffff), mpiCommunicator, &mpiRequest_Send[3]);
reqOutstanding_Send[3] = true;
}
}
}
;
for (int fragmentIdx = 0; fragmentIdx < 1; ++fragmentIdx) {
if (isValidForSubdomain[1]) {
if ((neighbor_isValid[1][2]&&neighbor_isRemote[1][2])) {
MPI_Irecv(&fieldData_LaplaceCoeff[2][1], 1, mpiDatatype_9_7_56, neighbor_remoteRank[1][2], ((unsigned int)(neighbor_fragCommId[1][2]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[2]);
reqOutstanding_Recv[2] = true;
}
if ((neighbor_isValid[1][3]&&neighbor_isRemote[1][3])) {
MPI_Irecv(&fieldData_LaplaceCoeff[2][49], 1, mpiDatatype_9_7_56, neighbor_remoteRank[1][3], ((unsigned int)(neighbor_fragCommId[1][3]) << 16) + ((unsigned int)commId & 0x0000ffff), mpiCommunicator, &mpiRequest_Recv[3]);
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