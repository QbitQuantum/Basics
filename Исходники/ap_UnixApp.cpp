bool AP_UnixApp::makePngPreview(const char * pszInFile, const char * pszPNGFile, UT_sint32 iWidth, UT_sint32 iHeight)
{
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24, iWidth, iHeight);
	cairo_t *cr = cairo_create (surface);

	GR_UnixCairoAllocInfo ai(NULL, false);

	GR_CairoGraphics * pG = static_cast<GR_CairoGraphics*>(GR_UnixCairoGraphics::graphicsAllocator(ai));
	pG->setCairo(cr);
	pG->beginPaint(); // needed to avoid cairo reference loss

	UT_Error error = UT_OK;
	PD_Document * pNewDoc = new PD_Document();
	error = pNewDoc->readFromFile(pszInFile,IEFT_Unknown, NULL);

	if (error != UT_OK) 
	{
		return false;
	}
	AP_Preview_Abi * pPrevAbi = new AP_Preview_Abi(pG,iWidth,iHeight,NULL, PREVIEW_ZOOMED,pNewDoc);
	dg_DrawArgs da;
	memset(&da, 0, sizeof(da));
	da.pG = pG;
	GR_Painter * pPaint = new GR_Painter(pG);
	pPaint->clearArea(0,0,pG->tlu(iWidth),pG->tlu(iHeight));
	pPrevAbi->getView()->draw(0, &da);
	pG->endPaint();
	cairo_destroy(cr);
	DELETEP(pPaint);
	cairo_surface_write_to_png(surface, pszPNGFile);
	cairo_surface_destroy(surface);
	DELETEP(pG);
	DELETEP(pPrevAbi); // This deletes pNewDoc
	return true;
}