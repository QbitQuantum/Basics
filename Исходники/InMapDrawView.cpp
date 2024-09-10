void CInMapDrawView::Draw()
{
	CVertexArray* pointsVa = GetVertexArray();
	pointsVa->Initialize();
	CVertexArray* linesVa = GetVertexArray();
	linesVa->Initialize();

	InMapDraw_QuadDrawer drawer;
	drawer.linesVa = linesVa;
	drawer.pointsVa = pointsVa;
	drawer.visibleLabels = &visibleLabels;

	glDepthMask(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);

	readMap->GridVisibility(camera, CInMapDrawModel::DRAW_QUAD_SIZE, 1e9, &drawer);

	glDisable(GL_TEXTURE_2D);
	glLineWidth(3.f);
	linesVa->DrawArrayC(GL_LINES); //! draw lines

	// XXX hopeless drivers, retest in a year or so...
	// width greater than 2 causes GUI flicker on ATI hardware as of driver version 9.3
	// so redraw lines with width 1
	if (globalRendering->atiHacks) {
		glLineWidth(1.f);
		linesVa->DrawArrayC(GL_LINES);
	}

	// draw points
	glLineWidth(1);
	glEnable(GL_TEXTURE_2D);
	pointsVa->DrawArrayTC(GL_QUADS); //! draw point markers

	if (!visibleLabels.empty()) {
		font->SetColors(); //! default

		//! draw point labels
		for (std::vector<const CInMapDrawModel::MapPoint*>::const_iterator pi = visibleLabels.begin(); pi != visibleLabels.end(); ++pi) {
			float3 pos = (*pi)->GetPos();
			pos.y += 111.0f;

			const unsigned char* color = (*pi)->IsBySpectator() ? color4::white : teamHandler->Team((*pi)->GetTeamID())->color;
			font->SetTextColor(color[0]/255.0f, color[1]/255.0f, color[2]/255.0f, 1.0f); //FIXME (overload!)
			font->glWorldPrint(pos, 26.0f, (*pi)->GetLabel());
		}

		visibleLabels.clear();
	}

	glDepthMask(1);
}