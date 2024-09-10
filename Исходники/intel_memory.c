unsigned int
intel_compute_size(struct intel_screen_private *intel,
                   int w, int h, int bpp, unsigned usage,
                   uint32_t *tiling, int *stride)
{
	int pitch, size;

	if (*tiling != I915_TILING_NONE) {
		/* First check whether tiling is necessary. */
		pitch = (w * bpp  + 7) / 8;
		pitch = ALIGN(pitch, 64);
		size = pitch * ALIGN (h, 2);
		if (INTEL_INFO(intel)->gen < 040) {
			/* Gen 2/3 has a maximum stride for tiling of
			 * 8192 bytes.
			 */
			if (pitch > KB(8))
				*tiling = I915_TILING_NONE;

			/* Narrower than half a tile? */
			if (pitch < 256)
				*tiling = I915_TILING_NONE;

			/* Older hardware requires fences to be pot size
			 * aligned with a minimum of 1 MiB, so causes
			 * massive overallocation for small textures.
			 */
			if (size < 1024*1024/2 && !intel->has_relaxed_fencing)
				*tiling = I915_TILING_NONE;
		} else if (!(usage & INTEL_CREATE_PIXMAP_DRI2) && size <= 4096) {
			/* Disable tiling beneath a page size, we will not see
			 * any benefit from reducing TLB misses and instead
			 * just incur extra cost when we require a fence.
			 */
			*tiling = I915_TILING_NONE;
		}
	}

	pitch = (w * bpp + 7) / 8;
	if (!(usage & INTEL_CREATE_PIXMAP_DRI2) && pitch <= 256)
		*tiling = I915_TILING_NONE;

	if (*tiling != I915_TILING_NONE) {
		int aligned_h, tile_height;

		if (IS_GEN2(intel))
			tile_height = 16;
		else if (*tiling == I915_TILING_X)
			tile_height = 8;
		else
			tile_height = 32;
		aligned_h = ALIGN(h, tile_height);

		*stride = intel_get_fence_pitch(intel,
						ALIGN(pitch, 512),
						*tiling);

		/* Round the object up to the size of the fence it will live in
		 * if necessary.  We could potentially make the kernel allocate
		 * a larger aperture space and just bind the subset of pages in,
		 * but this is easier and also keeps us out of trouble (as much)
		 * with drm_intel_bufmgr_check_aperture().
		 */
		size = intel_get_fence_size(intel, *stride * aligned_h);

		if (size > intel->max_tiling_size)
			*tiling = I915_TILING_NONE;
	}

	if (*tiling == I915_TILING_NONE) {
		/* We only require a 64 byte alignment for scanouts, but
		 * a 256 byte alignment for sharing with PRIME.
		 */
		*stride = ALIGN(pitch, 256);
		/* Round the height up so that the GPU's access to a 2x2 aligned
		 * subspan doesn't address an invalid page offset beyond the
		 * end of the GTT.
		 */
		size = *stride * ALIGN(h, 2);
	}

	return size;
}