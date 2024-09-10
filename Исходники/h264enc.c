h264enc *h264enc_new(const struct h264enc_params *p)
{
	h264enc *c;
	int i;

	/* check parameter validity */
	if (!IS_ALIGNED(p->src_width, 16) || !IS_ALIGNED(p->src_height, 16) ||
		!IS_ALIGNED(p->width, 2) || !IS_ALIGNED(p->height, 2) ||
		p->width > p->src_width || p->height > p->src_height)
	{
		MSG("invalid picture size");
		return NULL;
	}

	if (p->qp == 0 || p->qp > 47)
	{
		MSG("invalid QP");
		return NULL;
	}

	if (p->src_format != H264_FMT_NV12 && p->src_format != H264_FMT_NV16)
	{
		MSG("invalid color format");
		return NULL;
	}

	/* allocate memory for h264enc structure */
	c = calloc(1, sizeof(*c));
	if (c == NULL)
	{
		MSG("can't allocate h264enc data");
		return NULL;
	}

	/* copy parameters */
	c->mb_width = DIV_ROUND_UP(p->width, 16);
	c->mb_height = DIV_ROUND_UP(p->height, 16);
	c->mb_stride = p->src_width / 16;

	c->crop_right = (c->mb_width * 16 - p->width) / 2;
	c->crop_bottom = (c->mb_height * 16 - p->height) / 2;

	c->profile_idc = p->profile_idc;
	c->level_idc = p->level_idc;

	c->entropy_coding_mode_flag = p->entropy_coding_mode ? 1 : 0;
	c->pic_init_qp = p->qp;
	c->keyframe_interval = p->keyframe_interval;

	c->write_sps_pps = 1;
	c->current_frame_num = 0;

	/* allocate input buffer */
	c->input_color_format = p->src_format;
	switch (c->input_color_format)
	{
	case H264_FMT_NV12:
		c->input_buffer_size = p->src_width * (p->src_height + p->src_height / 2);
		break;
	case H264_FMT_NV16:
		c->input_buffer_size = p->src_width * p->src_height * 2;
		break;
	}

	c->luma_buffer = ve_malloc(c->input_buffer_size);
	if (c->luma_buffer == NULL)
		goto nomem;

	c->chroma_buffer = c->luma_buffer + p->src_width * p->src_height;

	/* allocate bytestream output buffer */
	c->bytestream_buffer_size = 1 * 1024 * 1024;
	c->bytestream_buffer = ve_malloc(c->bytestream_buffer_size);
	if (c->bytestream_buffer == NULL)
		goto nomem;

	/* allocate reference picture memory */
	unsigned int luma_size = ALIGN(c->mb_width * 16, 32) * ALIGN(c->mb_height * 16, 32);
	unsigned int chroma_size = ALIGN(c->mb_width * 16, 32) * ALIGN(c->mb_height * 8, 32);
	for (i = 0; i < 2; i++)
	{
		c->ref_picture[i].luma_buffer = ve_malloc(luma_size + chroma_size);
		c->ref_picture[i].chroma_buffer = c->ref_picture[i].luma_buffer + luma_size;
		c->ref_picture[i].extra_buffer = ve_malloc(luma_size / 4);
		if (c->ref_picture[i].luma_buffer == NULL || c->ref_picture[i].extra_buffer == NULL)
			goto nomem;
	}

	/* allocate unknown purpose buffers */
	c->extra_buffer_frame = ve_malloc(ALIGN(c->mb_width, 4) * c->mb_height * 8);
	c->extra_buffer_line = ve_malloc(c->mb_width * 32);
	if (c->extra_buffer_frame == NULL || c->extra_buffer_line == NULL)
		goto nomem;

	return c;

nomem:
	MSG("can't allocate VE memory");
	h264enc_free(c);
	return NULL;
}