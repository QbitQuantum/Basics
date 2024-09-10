static M4Err gdip_add_text_to_path(FontRaster *dr, LPM4PATH path, Bool flipText,
					const unsigned short* string, Float left, Float top, Float x_scaling, Float y_scaling, 
					Float ascent, M4Rect *bounds)
{
	GpPath *path_tmp;
	GpMatrix *mat;
	GpStringFormat *fmt;
	Float real_start;
	unsigned short str[4];
	FontPriv *ctx = (FontPriv *)dr->priv;

	if (!ctx->font) return M4BadParam;

	
	RectF rc;
	rc.X = rc.Y = 0;
	rc.Width = rc.Height = 0;

	/*find first non-space char and estimate its glyph pos since GDIplus doesn't give this info*/
	s32 len = utf8_wcslen(string);
	s32 i=0;
	for (; i<len; i++) {
		if (string[i] != (unsigned short) ' ') break;
	}
	if (i>=len) return M4OK;

	GdipCreateStringFormat(StringFormatFlagsNoWrap | StringFormatFlagsNoFitBlackBox | StringFormatFlagsMeasureTrailingSpaces, LANG_NEUTRAL, &fmt);
	GdipSetStringFormatAlign(fmt, StringAlignmentNear);
	GdipCreatePath(FillModeAlternate, &path_tmp);

	/*to compute first glyph alignment (say 'x', we figure out its bounding full box by using the '_' char as wrapper (eg, "_x_")
	then the bounding box starting from xMin of the glyph ('x_'). The difference between both will give us a good approx 
	of the glyph alignment*/
	str[0] = (unsigned short) '_';
	str[1] = string[i];
	str[2] = (unsigned short) '_';
	str[3] = (unsigned short) 0;
	GdipAddPathString(path_tmp, str, -1, ctx->font, ctx->font_style, ctx->font_size, &rc, fmt);
	GdipGetPathWorldBounds(path_tmp, &rc, NULL, NULL);
	Float w1 = rc.Width - 2 * ctx->underscore_width;
	
	GdipResetPath(path_tmp);

	str[0] = string[i];
	str[1] = (unsigned short) '_';
	str[2] = (unsigned short) 0;
	rc.X = rc.Y = 0;
	rc.Width = rc.Height = 0;
	GdipAddPathString(path_tmp, str, -1, ctx->font, ctx->font_style, ctx->font_size, &rc, fmt);
	GdipGetPathWorldBounds(path_tmp, &rc, NULL, NULL);
	real_start = w1 - (rc.Width - ctx->underscore_width);

	GdipResetPath(path_tmp);

	rc.X = rc.Y = 0;
	rc.Width = rc.Height = 0;
	GdipAddPathString(path_tmp, string, -1, ctx->font, ctx->font_style, ctx->font_size, &rc, fmt);
	GdipGetPathWorldBounds(path_tmp, &rc, NULL, NULL);


	GdipCreateMatrix(&mat);
	Float off_left = rc.X;
	Float off_left_real = rc.X;

	/*adjust all white space at begin*/
	adjust_white_space(string, &off_left, -1*ctx->whitespace_width);

	if (flipText) {
		/*first translate in local system*/
		GdipTranslateMatrix(mat, left - off_left + real_start, -top, MatrixOrderAppend);
		/*then scale as specified*/
		GdipScaleMatrix(mat, x_scaling, -y_scaling, MatrixOrderAppend);
	} else {
		/*first translate in local system*/
		GdipTranslateMatrix(mat, left - off_left + real_start, top-ascent, MatrixOrderAppend);
		/*then scale as specified*/
		GdipScaleMatrix(mat, x_scaling, y_scaling, MatrixOrderAppend);
	}
	GdipTransformPath(path_tmp, mat);

	/*start enum*/
	s32 count;
	GdipGetPointCount(path_tmp, &count);
	GpPointF *pts = new GpPointF[count];
	BYTE *types = new BYTE[count];
	GdipGetPathTypes(path_tmp, types, count);
	GdipGetPathPoints(path_tmp, pts, count);

	for (i=0; i<count; ) {
		BOOL closed = 0;
		s32 sub_type;
		
		sub_type = types[i] & PathPointTypePathTypeMask;

		if (sub_type == PathPointTypeStart) {
			m4_path_add_move_to(path, pts[i].X, pts[i].Y);
			i++;
		}
		else if (sub_type == PathPointTypeLine) {
			m4_path_add_line_to(path, pts[i].X, pts[i].Y);
		
			if (types[i] & PathPointTypeCloseSubpath) m4_path_close(path);

			i++;
		}
		else if (sub_type == PathPointTypeBezier) {
			assert(i+2<=count);
			m4_path_add_cubic_to(path, pts[i].X, pts[i].Y, pts[i+1].X, pts[i+1].Y, pts[i+2].X, pts[i+2].Y);

			if (types[i+2] & PathPointTypeCloseSubpath) m4_path_close(path);

			i += 3;
		} else {
			assert(0);
			break;
		}
	}
	
	delete [] pts;
	delete [] types;
	
	GdipResetPath(path_tmp);
	adjust_white_space(string, &rc.Width, ctx->whitespace_width);
	rc.X = off_left_real;
	rc.X = off_left;
	/*special case where string is just space*/
	if (!rc.Height) rc.Height = 1;

	GdipAddPathRectangles(path_tmp, &rc, 1);
	GdipGetPathWorldBounds(path_tmp, &rc, mat, NULL);
	bounds->x = rc.X;
	bounds->y = rc.Y;
	bounds->width = rc.Width;
	bounds->height = rc.Height;

	GdipDeleteStringFormat(fmt);
	GdipDeletePath(path_tmp);
	GdipDeleteMatrix(mat);
	return M4OK;
}