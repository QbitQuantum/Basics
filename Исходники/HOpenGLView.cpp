int CHOpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_hDC = GetDC()->m_hDC ;

	// set the pixel format
	if(!SetPixelformat(m_hDC))
	{
		return -1;
	}

	// create rendering context and make it current
	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC,m_hglRC);

	// initialize renderring mode 
	InitGL();

	return 0;
}