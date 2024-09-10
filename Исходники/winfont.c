void 
font_glyph(const char * str, int unicode, void * buffer, struct font_context *ctx) {
	GLYPHMETRICS gm;
	memset(&gm,0,sizeof(gm));

#if !defined(_MSC_VER)
	uint8_t tmp[ctx->w * ctx->h];
#else
	msvc::dynarray<uint8_t> tmp(ctx->w * ctx->h);
#endif
	memset(tmp,0, ctx->w * ctx->h);

	GetGlyphOutlineW(
		(HDC)ctx->dc,
		unicode,
		GGO_GRAY8_BITMAP,
		&gm,
		ctx->w * ctx->h,
		tmp,
		&mat2
	);

	int w = (gm.gmBlackBoxX + 3) & ~3;
	int h = gm.gmBlackBoxY;

	uint8_t * buf = (uint8_t *)buffer;
	int offx = gm.gmptGlyphOrigin.x;
	int offy = ctx->ascent - gm.gmptGlyphOrigin.y;
	assert(offx >= 0);
	assert(offy >= 0);
	assert(offx + gm.gmBlackBoxX <= ctx->w);
	assert(offy + h <= ctx->h);

	int i,j;

	for (i=0;i<h;i++) {
		for (j=0;j<gm.gmBlackBoxX;j++) {
			int src = tmp[i*w+j];
			buf[(i + offy)*ctx->w + j + offx] = src * 255 / 64;
		}
	}
}