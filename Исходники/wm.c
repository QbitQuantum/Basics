void
dump_surface(const char *filename, uint32_t binding_table_offset, int i)
{
	struct surface s;
	char *linear;
	__m256i alpha;

	get_surface(binding_table_offset, i, &s);

	int png_format;
	switch (s.format) {
	case SF_R8G8B8X8_UNORM:
	case SF_R8G8B8A8_UNORM:
	case SF_R8G8B8X8_UNORM_SRGB:
	case SF_R8G8B8A8_UNORM_SRGB:
		png_format = PNG_FORMAT_RGBA;
		break;
	case SF_B8G8R8A8_UNORM:
	case SF_B8G8R8X8_UNORM:
	case SF_B8G8R8A8_UNORM_SRGB:
	case SF_B8G8R8X8_UNORM_SRGB:
		png_format = PNG_FORMAT_BGRA;
		break;
	default:
		stub("image format");
		return;
	}

	switch (s.format) {
	case SF_R8G8B8X8_UNORM:
	case SF_B8G8R8X8_UNORM:
	case SF_R8G8B8X8_UNORM_SRGB:
	case SF_B8G8R8X8_UNORM_SRGB:
		alpha = _mm256_set1_epi32(0xff000000);
		break;
	default:
		alpha = _mm256_set1_epi32(0);
		break;
	}

	switch (s.tile_mode) {
	case LINEAR:
		linear = s.pixels;
		break;
	case XMAJOR:
		linear = detile_xmajor(&s, alpha);
		break;
	case YMAJOR:
		linear = detile_ymajor(&s, alpha);
		break;
	default:
		linear = s.pixels;
		stub("detile wmajor");
		break;
	}

	FILE *f = fopen(filename, "wb");
	ksim_assert(f != NULL);

	png_image pi = {
		.version = PNG_IMAGE_VERSION,
		.width = s.width,
		.height = s.height,
		.format = png_format
	};

	ksim_assert(png_image_write_to_stdio(&pi, f, 0, linear, s.stride, NULL));

	fclose(f);

	if (linear != s.pixels)
		free(linear);
}

static void
depth_test(struct primitive *p, struct dispatch *d)
{
	uint32_t cpp = depth_format_size(gt.depth.format);

	struct reg w_unorm;
	struct reg d24x8, cmp, d_f;

	void *base = ymajor_offset(p->depth.buffer, d->x, d->y, gt.depth.stride, cpp);

	if (gt.depth.test_enable) {
		const __m256 inv_scale = _mm256_set1_ps(1.0f / 16777215.0f);
		switch (gt.depth.format) {
		case D32_FLOAT:
			d_f.reg = _mm256_load_ps(base);
			break;
		case D24_UNORM_X8_UINT:
			d24x8.ireg = _mm256_load_si256(base);
			d_f.reg = _mm256_mul_ps(_mm256_cvtepi32_ps(d24x8.ireg),
						inv_scale);
			break;
		case D16_UNORM:
			stub("D16_UNORM");
		default:
			ksim_unreachable("invalid depth format");
		}

		/* Swizzle two middle pixel pairs so that dword 0-3 and 4-7
		 * match the shader dispatch subspan orderingg. */
		d_f.ireg = _mm256_permute4x64_epi64(d_f.ireg, SWIZZLE(0, 2, 1, 3));

		switch (gt.depth.test_function) {
		case COMPAREFUNCTION_ALWAYS:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_TRUE_US);
			break;
		case COMPAREFUNCTION_NEVER:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_FALSE_OS);
			break;
		case COMPAREFUNCTION_LESS:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_LT_OS);
			break;
		case COMPAREFUNCTION_EQUAL:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_EQ_OS);
			break;
		case COMPAREFUNCTION_LEQUAL:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_LE_OS);
			break;
		case COMPAREFUNCTION_GREATER:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_GT_OS);
			break;
		case COMPAREFUNCTION_NOTEQUAL:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_NEQ_OS);
			break;
		case COMPAREFUNCTION_GEQUAL:
			cmp.reg = _mm256_cmp_ps(d_f.reg, d->w.reg, _CMP_GE_OS);
			break;
		}
		d->mask.ireg = _mm256_and_si256(cmp.ireg, d->mask.ireg);
	}

	if (gt.depth.write_enable) {
		const __m256 scale = _mm256_set1_ps(16777215.0f);
		const __m256 half =  _mm256_set1_ps(0.5f);

		struct reg w;
		w.ireg = _mm256_permute4x64_epi64(d->w.ireg, SWIZZLE(0, 2, 1, 3));
		__m256i m = _mm256_permute4x64_epi64(d->mask.ireg,
						     SWIZZLE(0, 2, 1, 3));

		switch (gt.depth.format) {
		case D32_FLOAT:
			_mm256_maskstore_ps(base, m, w.reg);
			break;
		case D24_UNORM_X8_UINT:
			w_unorm.ireg = _mm256_cvtps_epi32(_mm256_add_ps(_mm256_mul_ps(w.reg, scale), half));
			_mm256_maskstore_epi32(base, m, w_unorm.ireg);
			break;
		case D16_UNORM:
			stub("D16_UNORM");
		default:
			ksim_unreachable("invalid depth format");
		}

	}
}