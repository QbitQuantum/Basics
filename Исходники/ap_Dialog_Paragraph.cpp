void AP_Dialog_Paragraph::_createPreviewFromGC(GR_Graphics * gc,
											   UT_uint32 width,
											   UT_uint32 height)
{
	UT_return_if_fail (gc);

	// g_free any attached preview
	DELETEP(m_paragraphPreview);

	// platform's runModal should have set this
	UT_return_if_fail (m_pFrame);

	AV_View * baseview = m_pFrame->getCurrentView();
	UT_return_if_fail (baseview);

	FV_View * view = static_cast<FV_View *> (baseview);

	FL_DocLayout * dl = view->getLayout();
	UT_return_if_fail (dl);

	fl_BlockLayout * bl = dl->findBlockAtPosition((PT_DocPosition) view->getPoint());
	UT_return_if_fail (bl);

	UT_GrowBuf gb;
	bool hadMem = bl->getBlockBuf(&gb);

	UT_UCSChar * tmp = NULL;
	if (hadMem && gb.getLength() > 0)
	{
		gb.truncate(NUM_CHARS_FOR_SAMPLE);
		UT_UCS4_cloneString(&tmp, (UT_UCSChar *) gb.getPointer(0));
	}
	else
	{
		const XAP_StringSet * pSS = m_pApp->getStringSet();

		// if the paragraph was empty, use our sample
		UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewSampleFallback));
	}

	m_paragraphPreview = new AP_Preview_Paragraph(gc, tmp, this);

	FREEP(tmp);

	UT_return_if_fail (m_paragraphPreview);

	m_paragraphPreview->setWindowSize(width, height);

	// TODO : any setup of the GC for drawing

}