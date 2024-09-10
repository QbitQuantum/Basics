static bool MCTextLayoutStyleItem(MCTextLayoutState& self, SCRIPT_ANALYSIS p_analysis, const unichar_t *p_chars, uint32_t p_char_count, MCTextLayoutFont *p_primary_font)
{
	bool t_success;
	t_success = true;

	// Create a metafile dc into which we render the text
	HDC t_metafile_dc;
	t_metafile_dc = nil;
	if (t_success)
	{
		t_metafile_dc = CreateEnhMetaFile(nil, nil, nil, nil);
		if (t_metafile_dc == nil)
			t_success = false;
	}

	// Choose the primary font
	if (t_success)
		SelectObject(t_metafile_dc, p_primary_font -> handle);

	// Now use ScriptStringAnalyse to output the text into the metafile.
	SCRIPT_STRING_ANALYSIS t_ssa;
	t_ssa = nil;
	if (t_success)
	{
		SCRIPT_STATE t_script_state;
		SCRIPT_CONTROL t_script_control;
		MCMemoryClear(&t_script_state, sizeof(SCRIPT_STATE));
		MCMemoryClear(&t_script_control, sizeof(SCRIPT_CONTROL));
		if (ScriptStringAnalyse(t_metafile_dc, p_chars, p_char_count, 0, -1, SSA_METAFILE | SSA_FALLBACK | SSA_GLYPHS | SSA_LINK, 0, &t_script_control, &t_script_state, nil, nil, nil, &t_ssa) != S_OK)
			t_success = false;
	}

	// Render the analysed text into the metafile.
	if (t_success)
		if (ScriptStringOut(t_ssa, 0, 0, 0, nil, 0, 0, FALSE) != S_OK)
			t_success = false;

	// Fetch the metafile (we are done with the DC now)
	HENHMETAFILE t_metafile;
	t_metafile = nil;
	if (t_metafile_dc != nil)
	{
		t_metafile = CloseEnhMetaFile(t_metafile_dc);
		if (t_metafile == nil)
			t_success = false;
	}

	// Now process the metafile to get the subranges of text styled to the
	// appropriate fallback font.
	if (t_success)
	{
		MCTextLayoutStyleItemContext t_context;
		t_context . state = &self;
		t_context . chars = p_chars;
		t_context . char_count = p_char_count;
		t_context . analysis = p_analysis;
		t_context . primary_font = p_primary_font;
		t_context . current_font = p_primary_font;
		t_context . pending_x = 0;
		t_context . pending_font = nil;
		t_context . pending_chars = nil;
		t_context . pending_char_count = 0;
		if (!EnumEnhMetaFile(nil, t_metafile, MCTextLayoutStyleItemCallback, &t_context, nil))
			t_success = false;
	}

	// Free the metafile
	if (t_metafile != nil)
		DeleteEnhMetaFile(t_metafile);

	return t_success;
}