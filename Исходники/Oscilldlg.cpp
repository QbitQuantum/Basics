//-----------------------------------------------------------------------------
// Name: UpdateFrame()
// Desc: 
//-----------------------------------------------------------------------------
void COscillDlg::UpdateFrame( BYTE byDrawMask )
{
// 	start = clock();
//	TRACE( "Enter UpdateFrame\r\n" );
	
	g_COGL.m_sDspyThreadPara.byDrawMask = byDrawMask;
	g_eventDspy.SetEvent();
/*
	int		xCnt;
	m_nXCnt %= m_nSampPerFrame;	// make sure m_nXCnt < m_nSampPerFrame   
								// when m_nSampPerFrameis reduced in 
								// spneditTimebaseScale()

	xCnt = m_nXCnt + m_nXCntOffset + 1;			// add 1 so that fill the display area
	
 	if ( m_nQueueRearOffset < 0 )	// when the nPosition is smaller than  
 	{								// m_nNumOfDiv, m_nQueueRearOffset != 0
 		xCnt = m_nSampPerFrame;
 	}

	if ( xCnt > MAX_SAMP_RECORD )
	{
		xCnt = MAX_SAMP_RECORD;
		bClearFlag = true;
	}
	
//	wglMakeCurrent( g_COGL.hDC, g_COGL.hRC1 );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	if ( bClearFlag || 0 == m_nXCnt )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	g_COGL.DrawGrid( GLLEFT, GLRIGHT, GLBOTTOM, GLTOP );

	glTranslatef( m_fXPosition * GLWITDH / 12, 
		          m_fYPositionA * GLHEIGHT / 6 + 150.0f, 
				  0.1f );
	glScalef( ( GLWITDH / m_nSampPerFrame ), 
			  1 / c_fVSCoef[ m_byScaleA ], 1.0f );
	glColor3ub( 255, 0, 0 );
	
 	long x = g_psQueue->rear + m_nQueueRearOffset;
// 	xCnt = (int)fSampPerFrame < g_psQueue->num ? (int)fSampPerFrame : g_psQueue->num;
//	TRACE( "\txCnt:%d", xCnt );
	glBegin( GL_LINE_STRIP );
	{
		for( xCnt--; xCnt >= 0 ; xCnt-- )
		{
			glVertex2f( (GLfloat)xCnt, (GLfloat)g_psQueue->nData[x] );
			x--;
			if ( -1 == x )
			{
				x = MAX_SAMP_RECORD - 1;
			}
		}
	}
	glEnd();

	glFinish();

// 	finish = clock();
// 	duration = (double)(finish - start);
// 	TRACE( "UpdateFrame:\t%f\r\n", duration );

//	wglMakeCurrent(NULL, NULL);

//	TRACE( "Leave UpdateFrame\r\n" );
*/
}