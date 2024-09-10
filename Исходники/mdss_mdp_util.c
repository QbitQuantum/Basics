int mdss_mdp_get_plane_sizes(u32 format, u32 w, u32 h,
			     struct mdss_mdp_plane_sizes *ps, u32 bwc_mode)
{
	struct mdss_mdp_format_params *fmt;
	int i, rc;
	u32 bpp, ystride0_off, ystride1_off;
	if (ps == NULL)
		return -EINVAL;

	if ((w > MAX_IMG_WIDTH) || (h > MAX_IMG_HEIGHT))
		return -ERANGE;

	fmt = mdss_mdp_get_format_params(format);
	if (!fmt)
		return -EINVAL;

	bpp = fmt->bpp;
	memset(ps, 0, sizeof(struct mdss_mdp_plane_sizes));

	if (bwc_mode) {
		rc = mdss_mdp_get_rau_strides(w, h, fmt, ps);
		if (rc)
			return rc;
		ystride0_off = DIV_ROUND_UP(h, ps->rau_h[0]);
		ystride1_off = DIV_ROUND_UP(h, ps->rau_h[1]);
		ps->plane_size[0] = (ps->ystride[0] * ystride0_off) +
				    (ps->ystride[1] * ystride1_off);
		ps->ystride[0] += ps->ystride[1];
		ps->ystride[1] = 2;
		ps->plane_size[1] = ps->rau_cnt * ps->ystride[1] *
				   (ystride0_off + ystride1_off);
	} else {
		if (fmt->fetch_planes == MDSS_MDP_PLANE_INTERLEAVED) {
			ps->num_planes = 1;
			ps->plane_size[0] = w * h * bpp;
			ps->ystride[0] = w * bpp;
		} else if (format == MDP_Y_CBCR_H2V2_VENUS) {
			int cf = COLOR_FMT_NV12;
			ps->num_planes = 2;
			ps->ystride[0] = VENUS_Y_STRIDE(cf, w);
			ps->ystride[1] = VENUS_UV_STRIDE(cf, w);
			ps->plane_size[0] = VENUS_Y_SCANLINES(cf, h) *
				ps->ystride[0];
			ps->plane_size[1] = VENUS_UV_SCANLINES(cf, h) *
				ps->ystride[1];
		} else {
			u8 hmap[] = { 1, 2, 1, 2 };
			u8 vmap[] = { 1, 1, 2, 2 };
			u8 horiz, vert, stride_align, height_align;

			horiz = hmap[fmt->chroma_sample];
			vert = vmap[fmt->chroma_sample];

			switch (format) {
			case MDP_Y_CR_CB_GH2V2:
				stride_align = 16;
				height_align = 1;
				break;
			default:
				stride_align = 1;
				height_align = 1;
				break;
			}

			ps->ystride[0] = ALIGN(w, stride_align);
			ps->ystride[1] = ALIGN(w / horiz, stride_align);
			ps->plane_size[0] = ps->ystride[0] *
				ALIGN(h, height_align);
			ps->plane_size[1] = ps->ystride[1] * (h / vert);

			if (fmt->fetch_planes == MDSS_MDP_PLANE_PSEUDO_PLANAR) {
				ps->num_planes = 2;
				ps->plane_size[1] *= 2;
				ps->ystride[1] *= 2;
			} else { /* planar */
				ps->num_planes = 3;
				ps->plane_size[2] = ps->plane_size[1];
				ps->ystride[2] = ps->ystride[1];
			}
		}
	}
	for (i = 0; i < ps->num_planes; i++)
		ps->total_size += ps->plane_size[i];

	return 0;
}