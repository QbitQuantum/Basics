//-----------------------------------------------------------------------------
// Name: InitOpenGL()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT
COpenGL::InitOpenGL( COscillDlg *pCWnd )
{
    PIXELFORMATDESCRIPTOR   pfd;
    
    m_pCDrawWnd = pCWnd->GetDlgItem( IDC_DRAWFRAME );

    m_pDC = new CClientDC( m_pCDrawWnd );
    if( NULL == m_pDC )
    {
        return RptError( pCWnd->m_hWnd, FALSE, "GetDC Failed" );
    }
    
    if( !SetupPixelFormat( pCWnd->m_hWnd ) )
        return FALSE;

    int nIndex = GetPixelFormat( m_pDC->GetSafeHdc() );
    DescribePixelFormat( m_pDC->GetSafeHdc(), nIndex, sizeof(pfd), &pfd );

    m_hDC = m_pDC->GetSafeHdc();
    m_hRC1 = wglCreateContext( m_pDC->GetSafeHdc() );
//	m_hRC2 = wglCreateContext( m_pDC->GetSafeHdc() );
	wglMakeCurrent( m_hDC, m_hRC1 );
//	wglShareLists( m_hRC2, m_hRC1 );

    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	gluOrtho2D( GLLEFT, GLRIGHT, GLBOTTOM, GLTOP );
    
    CRect   rcDrawFrame;
    GetWindowRect( m_pCDrawWnd->m_hWnd, &rcDrawFrame );

// 	TRACE( "%d,%d,%d,%d\r\n", rcDrawFrame.left,
// 							  rcDrawFrame.top, 
// 							  rcDrawFrame.right,
// 							  rcDrawFrame.bottom );

    rcDrawFrame.SetRect( rcDrawFrame.left + 3,
                         rcDrawFrame.top + 3,
                         rcDrawFrame.right - 3,
                         rcDrawFrame.bottom - 3 );
	
	int nWidth = (int)( ( rcDrawFrame.Height() - 16 ) * 2.3 );

	if ( nWidth > rcDrawFrame.Width() - 20 )
	{
		nWidth = rcDrawFrame.Width() - 20;
	}

	int xMargin = ( rcDrawFrame.Width() - nWidth ) / 2;

    glViewport(  xMargin, 5, nWidth, rcDrawFrame.Height() - 17 );


    glEnable( GL_SCISSOR_TEST );
    glScissor( xMargin, 5, nWidth, rcDrawFrame.Height() - 17 );
    
	wglMakeCurrent( NULL, NULL );

	m_bDspyThreadRunning = true;
	m_pDspyThread = AfxBeginThread( DspyThreadFunc, &m_sDspyThreadPara/*, THREAD_PRIORITY_HIGHEST*/ );

    return TRUE;
}