GpStatus
cairo_MeasureString (GpGraphics *graphics, GDIPCONST WCHAR *stringUnicode, int length, GDIPCONST GpFont *font, GDIPCONST RectF *rc,
	GDIPCONST GpStringFormat *format,  RectF *boundingBox, int *codepointsFitted, int *linesFilled)
{
	cairo_matrix_t SavedMatrix;
	GpStringFormat *fmt;
	GpStringDetailStruct *StringDetails;
	WCHAR *CleanString;
	int StringLen = length;
	GpStatus status;

	status = AllocStringData (&CleanString, &StringDetails, length);
	if (status != Ok)
		return status;

	/* a NULL format is valid, it means get the generic default values (and free them later) */
	if (!format) {
		GdipStringFormatGetGenericDefault ((GpStringFormat **)&fmt);
	} else {
		fmt = (GpStringFormat *)format;
	}

	/* is the following ok ? */
	cairo_get_font_matrix (graphics->ct, &SavedMatrix);

	status = MeasureString (graphics, stringUnicode, &StringLen, font, rc, fmt, NULL, boundingBox, codepointsFitted, 
		linesFilled, CleanString, StringDetails, NULL);

	/* Restore matrix to original values */
	cairo_set_font_matrix (graphics->ct, &SavedMatrix);

	/* Cleanup */
	GdipFree (CleanString);
	GdipFree (StringDetails);

	/* we must delete the default stringformat (when one wasn't provided by the caller) */
	if (format != fmt)
		GdipDeleteStringFormat (fmt);

	return status;
}