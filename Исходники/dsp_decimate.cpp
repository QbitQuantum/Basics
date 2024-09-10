buffer_c16_t FIRC16xR16x32Decim8::execute(
	const buffer_c16_t& src,
	const buffer_c16_t& dst
) {
	vec2_s16* const z = static_cast<vec2_s16*>(__builtin_assume_aligned(z_.data(), 4));
	const vec2_s16* const t = static_cast<vec2_s16*>(__builtin_assume_aligned(taps_.data(), 4));
	uint32_t* const d = static_cast<uint32_t*>(__builtin_assume_aligned(dst.p, 4));

	const auto k = output_scale;

	const size_t count = src.count / decimation_factor;
	for(size_t i=0; i<count; i++) {
		const vec2_s16* const in = static_cast<const vec2_s16*>(__builtin_assume_aligned(&src.p[i * decimation_factor], 4));

		complex32_t accum;

		// Oldest samples are discarded.
		accum = mac_shift(z, t, 0, accum);
		accum = mac_shift(z, t, 1, accum);
		accum = mac_shift(z, t, 2, accum);
		accum = mac_shift(z, t, 3, accum);

		// Middle samples are shifted earlier in the "z" delay buffer.
		accum = mac_shift_and_store(z, t, decimation_factor, 0, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 1, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 2, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 3, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 4, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 5, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 6, accum);
		accum = mac_shift_and_store(z, t, decimation_factor, 7, accum);

		// Newest samples come from "in" buffer, are copied to "z" delay buffer.
		accum = mac_shift_and_store_new_c16_samples(z, t, in, decimation_factor, 0, taps_count, accum);
		accum = mac_shift_and_store_new_c16_samples(z, t, in, decimation_factor, 1, taps_count, accum);
		accum = mac_shift_and_store_new_c16_samples(z, t, in, decimation_factor, 2, taps_count, accum);
		accum = mac_shift_and_store_new_c16_samples(z, t, in, decimation_factor, 3, taps_count, accum);

		d[i] = scale_round_and_pack(accum, k);
	}

	return {
		dst.p,
		count,
		src.sampling_rate / decimation_factor
	};
}