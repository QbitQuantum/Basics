int cellFontGetCharGlyphMetrics(mem_ptr_t<CellFont> font, u32 code, mem_ptr_t<CellFontGlyphMetrics> metrics)
{
	cellFont.Log("cellFontGetCharGlyphMetrics(font_addr=0x%x, code=0x%x, metrics_addr=0x%x",
		font.GetAddr(), code, metrics.GetAddr());

	if (!font.IsGood() || metrics.IsGood())
		return CELL_FONT_ERROR_INVALID_PARAMETER;

	int x0, y0, x1, y1;
	int advanceWidth, leftSideBearing;
	float scale = stbtt_ScaleForPixelHeight(&(font->stbfont), font->scale_y);
	stbtt_GetCodepointBox(&(font->stbfont), code, &x0, &y0, &x1, &y1);
	stbtt_GetCodepointHMetrics(&(font->stbfont), code, &advanceWidth, &leftSideBearing);
	
	// TODO: Add the rest of the information
	metrics->width = (x1-x0) * scale;
	metrics->height = (y1-y0) * scale;
	metrics->Horizontal.bearingX = (float)leftSideBearing * scale;
	metrics->Horizontal.bearingY = 0;
	metrics->Horizontal.advance = (float)advanceWidth * scale;
	metrics->Vertical.bearingX = 0;
	metrics->Vertical.bearingY = 0;
	metrics->Vertical.advance = 0;
	return CELL_FONT_OK;
}