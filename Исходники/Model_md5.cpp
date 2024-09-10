====================
TransformJoints
====================
*/
static void TransformJoints( idJointMat *__restrict outJoints, const int numJoints, const idJointMat *__restrict inJoints1, const idJointMat *__restrict inJoints2 ) {

	float * outFloats = outJoints->ToFloatPtr();
	const float * inFloats1 = inJoints1->ToFloatPtr();
	const float * inFloats2 = inJoints2->ToFloatPtr();

	assert_16_byte_aligned( outFloats );
	assert_16_byte_aligned( inFloats1 );
	assert_16_byte_aligned( inFloats2 );


	const __m128 mask_keep_last = __m128c( _mm_set_epi32( 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000 ) );

	for ( int i = 0; i < numJoints; i += 2, inFloats1 += 2 * 12, inFloats2 += 2 * 12, outFloats += 2 * 12 ) {
		__m128 m1a0 = _mm_load_ps( inFloats1 + 0 * 12 + 0 );
		__m128 m1b0 = _mm_load_ps( inFloats1 + 0 * 12 + 4 );
		__m128 m1c0 = _mm_load_ps( inFloats1 + 0 * 12 + 8 );
		__m128 m1a1 = _mm_load_ps( inFloats1 + 1 * 12 + 0 );
		__m128 m1b1 = _mm_load_ps( inFloats1 + 1 * 12 + 4 );
		__m128 m1c1 = _mm_load_ps( inFloats1 + 1 * 12 + 8 );

		__m128 m2a0 = _mm_load_ps( inFloats2 + 0 * 12 + 0 );
		__m128 m2b0 = _mm_load_ps( inFloats2 + 0 * 12 + 4 );
		__m128 m2c0 = _mm_load_ps( inFloats2 + 0 * 12 + 8 );
		__m128 m2a1 = _mm_load_ps( inFloats2 + 1 * 12 + 0 );
		__m128 m2b1 = _mm_load_ps( inFloats2 + 1 * 12 + 4 );
		__m128 m2c1 = _mm_load_ps( inFloats2 + 1 * 12 + 8 );