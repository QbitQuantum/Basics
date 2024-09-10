static unsigned r600_texture_get_htile_size(struct r600_common_screen *rscreen,
					    struct r600_texture *rtex)
{
	unsigned cl_width, cl_height, width, height;
	unsigned slice_elements, slice_bytes, pipe_interleave_bytes, base_align;
	unsigned num_pipes = rscreen->tiling_info.num_channels;

	if (rscreen->chip_class <= EVERGREEN &&
	    rscreen->info.drm_major == 2 && rscreen->info.drm_minor < 26)
		return 0;

	/* HW bug on R6xx. */
	if (rscreen->chip_class == R600 &&
	    (rtex->surface.level[0].npix_x > 7680 ||
	     rtex->surface.level[0].npix_y > 7680))
		return 0;

	/* HTILE is broken with 1D tiling on old kernels and CIK. */
	if (rscreen->chip_class >= CIK &&
	    rtex->surface.level[0].mode == RADEON_SURF_MODE_1D &&
	    rscreen->info.drm_major == 2 && rscreen->info.drm_minor < 38)
		return 0;

	switch (num_pipes) {
	case 1:
		cl_width = 32;
		cl_height = 16;
		break;
	case 2:
		cl_width = 32;
		cl_height = 32;
		break;
	case 4:
		cl_width = 64;
		cl_height = 32;
		break;
	case 8:
		cl_width = 64;
		cl_height = 64;
		break;
	case 16:
		cl_width = 128;
		cl_height = 64;
		break;
	default:
		assert(0);
		return 0;
	}

	width = align(rtex->surface.npix_x, cl_width * 8);
	height = align(rtex->surface.npix_y, cl_height * 8);

	slice_elements = (width * height) / (8 * 8);
	slice_bytes = slice_elements * 4;

	pipe_interleave_bytes = rscreen->tiling_info.group_bytes;
	base_align = num_pipes * pipe_interleave_bytes;

	return (util_max_layer(&rtex->resource.b.b, 0) + 1) *
		align(slice_bytes, base_align);
}