void CMatCanvas::Create(CWnd* parent,CRect pos,UINT in_winId)
{
 	const char* cName = AfxRegisterWndClass(CS_OWNDC | 
 			CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT,
 			::LoadCursor(NULL,IDC_ARROW));
	Base::Create(cName, "Canvas" ,WS_VISIBLE, pos, parent, in_winId,NULL);

	// DMMSOLID added point
	Point2I temp(0,0);
	GFXCDSSurface::create(m_pSurface, TRUE,
		pos.Width(), pos.Height(), GetSafeHwnd(), &temp);

	RectI screenView(Point2I(0,0),Point2I(pos.Width()-1, pos.Height()-1));

//    double max_dim = (pos.Width() > pos.Height()) ? (double)pos.Width() : (double)pos.Height();
//	RectF worldView(Point2F(-pos.Width()/max_dim, pos.Height()/max_dim),
//			            Point2F(pos.Width()/max_dim, -pos.Height()/max_dim));
	RectF worldView(Point2F(0, 0),
			            Point2F(pos.Width(), pos.Height()));

    m_pTSCamera = new TSPerspectiveCamera(screenView, worldView, 1.F, 1.0E4f);

    m_renderContext->setSurface(m_pSurface);
    m_renderContext->setPointArray(&DefaultPointArray);
    m_renderContext->setCamera(m_pTSCamera);
    m_renderContext->setLights(m_GSceneLights);

    m_renderContext->getSurface()->setHazeSource(GFX_HAZE_NONE);
//    m_renderContext->getSurface()->setShadeSource(GFX_SHADE_NONE);
    m_renderContext->getSurface()->setAlphaSource(GFX_ALPHA_NONE);
    m_renderContext->getSurface()->setTransparency(FALSE);

}