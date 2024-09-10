void CInMapDraw::Draw(void)
{
	GML_STDMUTEX_LOCK(inmap); //! Draw

	glDepthMask(0);

	CVertexArray* va = GetVertexArray();
	va->Initialize();
	CVertexArray* lineva = GetVertexArray();
	lineva->Initialize();
	//font->Begin();
	font->SetColors(); //! default

	InMapDraw_QuadDrawer drawer;
	drawer.imd = this;
	drawer.lineva = lineva;
	drawer.va = va;
	drawer.texture = texture;

	readmap->GridVisibility(camera, DRAW_QUAD_SIZE, 3000.0f, &drawer);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(3.f);
	lineva->DrawArrayC(GL_LINES); //! draw lines
	// XXX hopeless drivers, retest in a year or so...
	// width greater than 2 causes GUI flicker on ATI hardware as of driver version 9.3
	// so redraw lines with width 1
	if (gu->atiHacks) {
		glLineWidth(1.f);
		lineva->DrawArrayC(GL_LINES);
	}
	// draw points
	glLineWidth(1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	va->DrawArrayTC(GL_QUADS); //! draw point markers 
	//font->End(); //! draw point markers text

	glDepthMask(1);
}