static void compute_correction_matrix(colgate_instance_t *o)
{
	int i;

	/*
	 * Find out what the given neutral color would be in LMS space,
	 * and use that value to build a correction factor for each component
	 * so that the neutral color really becomes gray (in LMS).
	 */
	float ref_r = o->neutral_color.r * 255.0f;
	float ref_g = o->neutral_color.g * 255.0f;
	float ref_b = o->neutral_color.b * 255.0f;

	float linear_r = convert_srgb_to_linear_rgb(ref_r);
	float linear_g = convert_srgb_to_linear_rgb(ref_g);
	float linear_b = convert_srgb_to_linear_rgb(ref_b);

	float x, y, z;
	convert_linear_rgb_to_linear_xyz(linear_r, linear_g, linear_b, &x, &y, &z);

	float l, m, s;
	convert_linear_xyz_to_linear_lms(x, y, z, &l, &m, &s);

	float l_scale, m_scale, s_scale;
	compute_lms_scaling_factors(x, y, z, &l_scale, &m_scale, &s_scale);

	/*
	 * Now apply the color balance. Simply put, we find the chromacity point
	 * for the desired white temperature, see what LMS scaling factors they
	 * would have given us, and then reverse that transform. For T=6500K,
	 * the default, this gives us nearly an identity transform (but only nearly,
	 * since the D65 illuminant does not exactly match the results of T=6500K);
	 * we normalize so that T=6500K really is a no-op.
	 */
	float white_x, white_y, white_z, l_scale_white, m_scale_white, s_scale_white;
	convert_color_temperature_to_xyz(o->color_temperature, &white_x, &white_y, &white_z);
	compute_lms_scaling_factors(white_x, white_y, white_z, &l_scale_white, &m_scale_white, &s_scale_white);

	float ref_x, ref_y, ref_z, l_scale_ref, m_scale_ref, s_scale_ref;
	convert_color_temperature_to_xyz(6500.0f, &ref_x, &ref_y, &ref_z);
	compute_lms_scaling_factors(ref_x, ref_y, ref_z, &l_scale_ref, &m_scale_ref, &s_scale_ref);

	l_scale *= l_scale_ref / l_scale_white;
	m_scale *= m_scale_ref / m_scale_white;
	s_scale *= s_scale_ref / s_scale_white;

	/*
	 * Concatenate all the different linear operations into a single 3x3 matrix.
	 * Note that since we postmultiply our vectors, the order of the matrices
	 * has to be the opposite of the execution order.
	 */
	Matrix3x3 temp, temp2, corr_matrix;
	Matrix3x3 lms_scale_matrix = {
		l_scale,    0.0f,    0.0f,
		   0.0f, m_scale,    0.0f,
		   0.0f,    0.0f, s_scale,
	};
	multiply_3x3_matrices(xyz_to_rgb_matrix, lms_to_xyz_matrix, temp);
	multiply_3x3_matrices(temp, lms_scale_matrix, temp2);
	multiply_3x3_matrices(temp2, xyz_to_lms_matrix, temp);
	multiply_3x3_matrices(temp, rgb_to_xyz_matrix, corr_matrix);

	// Scale for fixed-point, and clamp. We clamp the matrix elements
	// instead of the actual fixed-point numbers below, to make sure
	// we get consistent results over the entire range.
	for (i = 0; i < 9; ++i) {
		corr_matrix[i] *= (float)(1 << MATRIX_ELEMENT_FRAC_BITS);
		if (corr_matrix[i] < -(1 << MATRIX_ELEMENT_BITS)) {
			corr_matrix[i] = -(1 << MATRIX_ELEMENT_BITS);
		}
		if (corr_matrix[i] > (1 << MATRIX_ELEMENT_BITS) - 1) {
			corr_matrix[i] = (1 << MATRIX_ELEMENT_BITS) - 1;
		}
	}

	// Precompute some of the multiplications (after conversion from sRGB)
	// to save some time per-pixel later. Each of these contain the given color
	// converted to linear space and then multiplied by three different factors,
	// given by the matrix.
	for (i = 0; i < 256; ++i) {
		int x = convert_srgb_to_linear_rgb(i) * (float)(1 << INPUT_PIXEL_BITS);

		int r0 = lrintf(x * corr_matrix[0]);
		int r1 = lrintf(x * corr_matrix[3]);
		int r2 = lrintf(x * corr_matrix[6]);

		int g0 = lrintf(x * corr_matrix[1]);
		int g1 = lrintf(x * corr_matrix[4]);
		int g2 = lrintf(x * corr_matrix[7]);

		int b0 = lrintf(x * corr_matrix[2]);
		int b1 = lrintf(x * corr_matrix[5]);
		int b2 = lrintf(x * corr_matrix[8]);

#if __SSE2__
		o->premult_r[i] = _mm_setr_epi32(r0, r1, r2, 0);
		o->premult_g[i] = _mm_setr_epi32(g0, g1, g2, 0);
		o->premult_b[i] = _mm_setr_epi32(b0, b1, b2, 0);
#else
		o->premult_r[i][0] = r0;
		o->premult_r[i][1] = r1;
		o->premult_r[i][2] = r2;

		o->premult_g[i][0] = g0;
		o->premult_g[i][1] = g1;
		o->premult_g[i][2] = g2;

		o->premult_b[i][0] = b0;
		o->premult_b[i][1] = b1;
		o->premult_b[i][2] = b2;
#endif
	}
}