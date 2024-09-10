// --------------------------------------------------------------------------
void CCalibrateControl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CameraDialog* dlg=(CameraDialog*)this->GetParent();
	image.Show(pDC->m_hDC, 0, 0, image.Width(), image.Height(), dlg->offsetx, dlg->offsety);
	
	CPen red(PS_SOLID, 1, RGB(255, 0, 0));
	CPen green(PS_SOLID, 1, RGB(0, 255, 0));
	CPen blue(PS_SOLID, 1, RGB(0, 0, 255));
	CPen aqua(PS_SOLID, 1, RGB(0, 255, 255));
	DrawLines(pDC, dlg->x, &red);
	DrawLines(pDC, dlg->y, &green);
	DrawLines(pDC, dlg->z, &blue);
	DrawLines(pDC, dlg->r, &aqua);
	
	
	// draw vanishing points !!!!!!!!!
	CvPoint VX = cvPointFrom32f(dlg->coordsHomo2Image(dlg->VX));
	CvPoint VY = cvPointFrom32f(dlg->coordsHomo2Image(dlg->VY));
	CvPoint VZ = cvPointFrom32f(dlg->coordsHomo2Image(dlg->VZ));
	CBrush bred(RGB(255, 0, 0));
	CBrush bgreen(RGB(0, 255, 0));
	CBrush bblue(RGB(0, 0, 255));
 	pDC->SelectObject(bred);
	pDC->Ellipse(VX.x-2*DOT-dlg->offsetx, VX.y-2*DOT-dlg->offsety, VX.x+2*DOT-dlg->offsetx, VX.y+2*DOT-dlg->offsety);
	pDC->SelectObject(bgreen);
	pDC->Ellipse(VY.x-2*DOT-dlg->offsetx, VY.y-2*DOT-dlg->offsety, VY.x+2*DOT-dlg->offsetx, VY.y+2*DOT-dlg->offsety);
	pDC->SelectObject(bblue);
	pDC->Ellipse(VZ.x-2*DOT-dlg->offsetx, VZ.y-2*DOT-dlg->offsety, VZ.x+2*DOT-dlg->offsetx, VZ.y+2*DOT-dlg->offsety);
	
}