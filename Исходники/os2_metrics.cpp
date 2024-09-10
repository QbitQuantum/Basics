bool os2_metrics::init(void *font_id)
{
	// retrieve needed fields from the OS/2 table

	DWORD font_data_size;

	const HDC font_holder = dc_pool_instance.claim();
	assert(font_holder != NULL);
	font_mgr_instance.select_font(font_id, font_holder);

	font_data_size = GetFontData(font_holder, OS2_TABLE_TAG, offsetof(TT_OS2, xAvgCharWidth), reinterpret_cast<byte *>(&_xAvgCharWidth), sizeof(_xAvgCharWidth));
	if (font_data_size == GDI_ERROR)
		goto failed_init_os2_metrics;

	font_data_size = GetFontData(font_holder, OS2_TABLE_TAG, offsetof(TT_OS2, usWeightClass), reinterpret_cast<byte *>(&_usWeightClass), sizeof(_usWeightClass));
	if (font_data_size == GDI_ERROR)
		goto failed_init_os2_metrics;

	font_data_size = GetFontData(font_holder, OS2_TABLE_TAG, offsetof(TT_OS2, usWidthClass), reinterpret_cast<byte *>(&_usWidthClass), sizeof(_usWidthClass));
	if (font_data_size == GDI_ERROR)
		goto failed_init_os2_metrics;

	font_data_size = GetFontData(font_holder, OS2_TABLE_TAG, offsetof(TT_OS2, fsSelection), reinterpret_cast<byte *>(&_fsSelection), sizeof(_fsSelection));
	if (font_data_size == GDI_ERROR)
		goto failed_init_os2_metrics;

	_xAvgCharWidth = SWAPWORD(_xAvgCharWidth);
	_usWeightClass = SWAPWORD(_usWeightClass);
	_usWidthClass = SWAPWORD(_usWidthClass);
	_fsSelection = SWAPWORD(_fsSelection);

	return true;

failed_init_os2_metrics:
	dc_pool_instance.free(font_holder);
	return false;
}