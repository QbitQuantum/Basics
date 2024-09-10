/**
 * Convert a chroma-keyed image to standard ARGB32.
 * SSE2-optimized version.
 *
 * This operates on the image itself, and does not return
 * a duplicated image with the adjusted image.
 *
 * NOTE: The image *must* be ARGB32.
 *
 * @param key Chroma key color.
 * @return 0 on success; negative POSIX error code on error.
 */
int rp_image::apply_chroma_key_sse2(uint32_t key)
{
	RP_D(rp_image);
	rp_image_backend *const backend = d->backend;
	assert(backend->format == FORMAT_ARGB32);
	if (backend->format != FORMAT_ARGB32) {
		// ARGB32 only.
		return -EINVAL;
	}

	const unsigned int diff = (backend->stride - this->row_bytes()) / sizeof(uint32_t);
	uint32_t *img_buf = static_cast<uint32_t*>(backend->data());

	// SSE2 constants.
	const __m128i xmm_key = _mm_setr_epi32(key, key, key, key);
	const __m128i xmm_ones = _mm_setr_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);

	for (unsigned int y = static_cast<unsigned int>(backend->height); y > 0; y--) {
		// Process 4 pixels per iteration with SSE2.
		unsigned int x = static_cast<unsigned int>(backend->width);
		for (; x > 3; x -= 4, img_buf += 4) {
			__m128i *xmm_data = reinterpret_cast<__m128i*>(img_buf);

			// Compare the pixels to the chroma key.
			// Equal values will be 0xFFFFFFFF.
			// Non-equal values will be 0x00000000.
			__m128i res = _mm_cmpeq_epi32(*xmm_data, xmm_key);

			// Invert the results and mask the original data.
			// Original data will now have 00s for chroma-keyed pixels.
			*xmm_data = _mm_and_si128(_mm_xor_si128(res, xmm_ones), *xmm_data);
		}

		// Remaining pixels.
		for (; x > 0; x--, img_buf++) {
			if (*img_buf == key) {
				*img_buf = 0;
			}
		}

		// Next row.
		img_buf += diff;
	}

	// Adjust sBIT.
	// TODO: Only if transparent pixels were found.
	if (d->has_sBIT && d->sBIT.alpha == 0) {
		d->sBIT.alpha = 1;
	}

	// Chroma key applied.
	return 0;
}