static inline void
jxr_unpack_sample(fz_context *ctx, struct info *info, jxr_image_t image, int *sp, unsigned char *dp)
{
	int k, bpc, comps, alpha;
	float v;

	if (info->format == JXRC_FMT_32bppRGBE)
	{
		dp[0] = sRGB_from_scRGB(ldexpf(sp[0], sp[3] - 128 - 8)) * 255 + 0.5f;
		dp[1] = sRGB_from_scRGB(ldexpf(sp[1], sp[3] - 128 - 8)) * 255 + 0.5f;
		dp[2] = sRGB_from_scRGB(ldexpf(sp[2], sp[3] - 128 - 8)) * 255 + 0.5f;
		return;
	}
	if (info->format == JXRC_FMT_16bppBGR565)
	{
		dp[0] = sp[0] << 3;
		dp[1] = sp[1] << 2;
		dp[2] = sp[2] << 3;
		return;
	}

	comps = fz_mini(fz_colorspace_n(ctx, info->cspace), jxr_get_IMAGE_CHANNELS(image));
	alpha = jxr_get_ALPHACHANNEL_FLAG(image);
	bpc = jxr_get_CONTAINER_BPC(image);

	for (k = 0; k < comps + alpha; k++)
	{
		switch (bpc)
		{
		default: fz_throw(ctx, FZ_ERROR_GENERIC, "unknown sample type: %d", bpc);
		case JXR_BD1WHITE1: dp[k] = sp[k] ? 255 : 0; break;
		case JXR_BD1BLACK1: dp[k] = sp[k] ? 0 : 255; break;
		case JXR_BD5: dp[k] = sp[k] << 3; break;
		case JXR_BD8: dp[k] = sp[k]; break;
		case JXR_BD10: dp[k] = sp[k] >> 2; break;
		case JXR_BD16: dp[k] = sp[k] >> 8; break;

		case JXR_BD16S:
			v = sp[k] * (1.0f / (1 << 13));
			goto decode_float32;
		case JXR_BD32S:
			v = sp[k] * (1.0f / (1 << 24));
			goto decode_float32;
		case JXR_BD16F:
			v = float32_from_float16(sp[k]);
			goto decode_float32;
		case JXR_BD32F:
			v = float32_from_int32_bits(sp[k]);
			goto decode_float32;
		decode_float32:
			if (k < comps)
				dp[k] = sRGB_from_scRGB(fz_clamp(v, 0, 1)) * 255 + 0.5f;
			else
				dp[k] = fz_clamp(v, 0, 1) * 255 + 0.5f;
			break;
		}
	}
}