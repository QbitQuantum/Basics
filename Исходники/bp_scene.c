void 
bp_ray_trace_packet (const ray4_t *ray, vector_t *colors, simd4i_t srcprim_id, int depth, simd4_t fdepth)
{
	unsigned int activeMask;
	intersect4_t isect4;

	ASSIGN (colors [0], background);
	ASSIGN (colors [1], background);
	ASSIGN (colors [2], background);
	ASSIGN (colors [3], background);

 	if ((depth > curr_scene->settings.max_trace_level) 
	    | (simd4_extract_sign (simd4_float_lt (fdepth, simd4_from_float (curr_scene->settings.adc_bailout))) == 0xf)) {
		return;
	}

 	isect4.prim_id = simd4i_minus_ones;

 	bp_kd_tree_packet_find_nearest (curr_scene->kd_tree_root, ray, &isect4);

	activeMask = _mm_movemask_ps (simd4_float_eq (_mm_cvtepi32_ps (isect4.prim_id), simd4f_minus_ones));

 	/* If there was no intersection terminate early */
	if (activeMask == 0xF)
		return;

 	bp_shade_packet (curr_scene, &isect4, ray, colors, depth, fdepth, srcprim_id);
}