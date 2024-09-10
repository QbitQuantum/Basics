static void
pdf_write_line_cap_appearance(fz_context *ctx, fz_buffer *buf, fz_rect *rect,
		float x, float y, float dx, float dy, float w, int ic, pdf_obj *cap)
{
	if (cap == PDF_NAME(Square))
	{
		float r = fz_max(2.5f, w * 2.5f);
		fz_append_printf(ctx, buf, "%g %g %g %g re\n", x-r, y-r, r*2, r*2);
		fz_append_string(ctx, buf, ic ? "b\n" : "s\n");
		include_cap(rect, x, y, r);
	}
	else if (cap == PDF_NAME(Circle))
	{
		float r = fz_max(2.5f, w * 2.5f);
		float m = r * CIRCLE_MAGIC;
		fz_append_printf(ctx, buf, "%g %g m\n", x, y+r);
		fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", x+m, y+r, x+r, y+m, x+r, y);
		fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", x+r, y-m, x+m, y-r, x, y-r);
		fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", x-m, y-r, x-r, y-m, x-r, y);
		fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", x-r, y+m, x-m, y+r, x, y+r);
		fz_append_string(ctx, buf, ic ? "b\n" : "s\n");
		include_cap(rect, x, y, r);
	}
	else if (cap == PDF_NAME(Diamond))
	{
		float r = fz_max(2.5f, w * 2.5f);
		fz_append_printf(ctx, buf, "%g %g m\n", x, y+r);
		fz_append_printf(ctx, buf, "%g %g l\n", x+r, y);
		fz_append_printf(ctx, buf, "%g %g l\n", x, y-r);
		fz_append_printf(ctx, buf, "%g %g l\n", x-r, y);
		fz_append_string(ctx, buf, ic ? "b\n" : "s\n");
		include_cap(rect, x, y, r);
	}
	else if (cap == PDF_NAME(OpenArrow))
	{
		pdf_write_arrow_appearance(ctx, buf, rect, x, y, dx, dy, w);
		fz_append_string(ctx, buf, "S\n");
	}
	else if (cap == PDF_NAME(ClosedArrow))
	{
		pdf_write_arrow_appearance(ctx, buf, rect, x, y, dx, dy, w);
		fz_append_string(ctx, buf, ic ? "b\n" : "s\n");
	}
	/* PDF 1.5 */
	else if (cap == PDF_NAME(Butt))
	{
		float r = fz_max(3, w * 3);
		fz_point a = { x-dy*r, y+dx*r };
		fz_point b = { x+dy*r, y-dx*r };
		fz_append_printf(ctx, buf, "%g %g m\n", a.x, a.y);
		fz_append_printf(ctx, buf, "%g %g l\n", b.x, b.y);
		fz_append_string(ctx, buf, "S\n");
		*rect = fz_include_point_in_rect(*rect, a);
		*rect = fz_include_point_in_rect(*rect, b);
	}
	/* PDF 1.6 */
	else if (cap == PDF_NAME(ROpenArrow))
	{
		pdf_write_arrow_appearance(ctx, buf, rect, x, y, -dx, -dy, w);
		fz_append_string(ctx, buf, "S\n");
	}
	else if (cap == PDF_NAME(RClosedArrow))
	{
		pdf_write_arrow_appearance(ctx, buf, rect, x, y, -dx, -dy, w);
		fz_append_string(ctx, buf, ic ? "b\n" : "s\n");
	}
	else if (cap == PDF_NAME(Slash))
	{
		float r = fz_max(5, w * 5);
		float angle = atan2f(dy, dx) - (30 * FZ_PI / 180);
		fz_point a, b, v;
		v = rotate_vector(angle, 0, r);
		a = fz_make_point(x + v.x, y + v.y);
		v = rotate_vector(angle, 0, -r);
		b = fz_make_point(x + v.x, y + v.y);
		fz_append_printf(ctx, buf, "%g %g m\n", a.x, a.y);
		fz_append_printf(ctx, buf, "%g %g l\n", b.x, b.y);
		fz_append_string(ctx, buf, "S\n");
		*rect = fz_include_point_in_rect(*rect, a);
		*rect = fz_include_point_in_rect(*rect, b);
	}
}