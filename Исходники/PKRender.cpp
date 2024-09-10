void CPKRender::Release()
{
	//deselect rendering context and delete it
	wglMakeCurrent( m_hDC , NULL );
	wglDeleteContext( m_hglRC );
}