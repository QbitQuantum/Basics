bool CGraphicView::GetScreenPtFrom3DPoint( const CPoint3D& modelSpacePt, CPoint& screenPt )
{
	// this function works for any xyz point but usually we will just be returning the 
	// screen point for a grid point or node.
	GLint viewport[4];
	GLdouble mvMatrix[16], projMatrix[16];
	double winX = 0.0;
	double winY = 0.0;
	double winZ = 0.0; //depth value between 0 and 1 - for depth sorting
	bool bSuccess = false;

	HGLRC currentRC = wglGetCurrentContext();
	if( !currentRC )
	{
		TRACE( "CGraphicView::GetScreenPtFrom3DPoint Failed in GetCurrentContext\n" );
		return bSuccess;
	}
	HDC hDC = wglGetCurrentDC( );
	if( !hDC )
	{
		TRACE( "CGraphicView::GetScreenPtFrom3DPoint Failed in GetCurrentDC\n" );
		return bSuccess;
	}

	//if( !wglMakeCurrent( m_pDC->GetSafeHdc(), m_hDC ) )
	if( !wglMakeCurrent( hDC, currentRC ) )
	{
		TRACE( "CGraphicView::GetScreenPtFrom3DPoint Failed in MakeCurrent\n" );
		return bSuccess;
	}

	glGetIntegerv( GL_VIEWPORT, viewport );
	glGetDoublev( GL_MODELVIEW_MATRIX, mvMatrix );
	glGetDoublev( GL_PROJECTION_MATRIX, projMatrix );

	if( !gluProject( modelSpacePt.x, modelSpacePt.y, modelSpacePt.z, 
		             mvMatrix, projMatrix, viewport, 
				     &winX, &winY, &winZ ) )
	{
		//TRACE( "Failed in GetScreenPt #2\n" );
		//wglMakeCurrent( NULL, NULL );
		return bSuccess;
	}

	//openGL convention (origin at lower left)
	screenPt.x = int(winX);
	screenPt.y = int(winY);


	//windows convention (origin at upper left)
	screenPt.y = viewport[3] - viewport[1] - screenPt.y;
	bSuccess = true;
	return bSuccess;
}