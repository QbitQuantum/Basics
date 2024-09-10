void shz::math::matrix<shz::math::f32, 4, 4>::mul(const shz::math::f32* left, const shz::math::f32*right, shz::math::f32* target) {
	shz::math::f32 _ALIGNED(16) left_transposed[shz::math::matrix<shz::math::f32, 4, 4>::size];
	matrix<shz::math::f32, 4, 4>::transpose(left, left_transposed);
	shz::math::f32 _ALIGNED(16) temp[4];

	for(size_t m=0; m<4; ++m){
		__m128 right_operand = _mm_load_ps(right);
		shz::math::f32* transposed = left_transposed;

		// This probably can be further optimized. Needs benchmarking
		// Idea: unroll loop and exploit _mm_hadd_ps to sum partials from 2 rows at once
		// AVX: with AVX instruction set this loop is trivial
		for(size_t n=0; n<4; ++n){
			__m128 left_operand = _mm_load_ps(transposed);
			__m128 mul_result = _mm_mul_ps(left_operand, right_operand);
			__m128 added = _mm_hadd_ps(mul_result, mul_result);
			added = _mm_hadd_ps(added, added); 
			_mm_store_ps(temp, added);

			*target = temp[0];

			target++;
			transposed += 4;
		}

		right += 4;
	}
}