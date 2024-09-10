/**
 * g2d_copy - copy contents in source buffer to destination buffer.
 *
 * @ctx: a pointer to g2d_context structure.
 * @src: a pointer to g2d_image structure including image and buffer
 *	information to source.
 * @dst: a pointer to g2d_image structure including image and buffer
 *	information to destination.
 * @src_x: x start position to source buffer.
 * @src_y: y start position to source buffer.
 * @dst_x: x start position to destination buffer.
 * @dst_y: y start position to destination buffer.
 * @w: width value to source and destination buffers.
 * @h: height value to source and destination buffers.
 */
int
g2d_copy(struct g2d_context *ctx, struct g2d_image *src,
		struct g2d_image *dst, unsigned int src_x, unsigned int src_y,
		unsigned int dst_x, unsigned dst_y, unsigned int w,
		unsigned int h)
{
	union g2d_rop4_val rop4;
	union g2d_point_val pt;
	unsigned int src_w = 0, src_h = 0, dst_w = 0, dst_h = 0;

	g2d_add_cmd(ctx, DST_SELECT_REG, G2D_SELECT_MODE_BGCOLOR);
	g2d_add_cmd(ctx, DST_COLOR_MODE_REG, dst->color_mode);
	g2d_add_base_addr(ctx, dst, g2d_dst);
	g2d_add_cmd(ctx, DST_STRIDE_REG, dst->stride);

	g2d_add_cmd(ctx, SRC_SELECT_REG, G2D_SELECT_MODE_NORMAL);
	g2d_add_cmd(ctx, SRC_COLOR_MODE_REG, src->color_mode);
	g2d_add_base_addr(ctx, src, g2d_src);
	g2d_add_cmd(ctx, SRC_STRIDE_REG, src->stride);

	src_w = w;
	src_h = h;
	if (src_x + src->width > w)
		src_w = src->width - src_x;
	if (src_y + src->height > h)
		src_h = src->height - src_y;

	dst_w = w;
	dst_h = w;
	if (dst_x + dst->width > w)
		dst_w = dst->width - dst_x;
	if (dst_y + dst->height > h)
		dst_h = dst->height - dst_y;

	w = MIN(src_w, dst_w);
	h = MIN(src_h, dst_h);

	if (w <= 0 || h <= 0) {
		fprintf(stderr, "invalid width or height.\n");
		g2d_reset(ctx);
		return -EINVAL;
	}

	pt.val = 0;
	pt.data.x = src_x;
	pt.data.y = src_y;
	g2d_add_cmd(ctx, SRC_LEFT_TOP_REG, pt.val);
	pt.val = 0;
	pt.data.x = src_x + w;
	pt.data.y = src_y + h;
	g2d_add_cmd(ctx, SRC_RIGHT_BOTTOM_REG, pt.val);

	pt.val = 0;
	pt.data.x = dst_x;
	pt.data.y = dst_y;
	g2d_add_cmd(ctx, DST_LEFT_TOP_REG, pt.val);
	pt.val = 0;
	pt.data.x = dst_x + w;
	pt.data.y = dst_y + h;
	g2d_add_cmd(ctx, DST_RIGHT_BOTTOM_REG, pt.val);

	rop4.val = 0;
	rop4.data.unmasked_rop3 = G2D_ROP3_SRC;
	g2d_add_cmd(ctx, ROP4_REG, rop4.val);

	return g2d_flush(ctx);
}