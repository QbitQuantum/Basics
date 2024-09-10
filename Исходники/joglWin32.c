ARGS()
{
	//int pdata;
	HDC hDC;
	HGLRC gc;
	THIS_CLASS();

	//printf( "DOING USE\n" );
	gc = (HGLRC)GET_INT_FIELD("renderContext");
	//pdata = (int) GET_INT_FIELD("pData");
	if( gc == 0 )
	{
		printf( "gc = 0\n" );
		return 0;
	}

	hDC = (HDC)GET_INT_FIELD("display");
	//printf( "USE - hDC: %d\n", hDC);

	if( !hDC )
	{
		printf( "use - hdc 0" );
		return 0;
	}

	if( wglGetCurrentContext() == NULL )
	{
		printf( "ERROR WITH CONTEXT" );

		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( (HGLRC)GET_INT_FIELD("renderContext") );

		SetDCPixelFormat(hDC);          
		// Create palette if needed
		GetOpenGLPalette(hDC);
		gc = wglCreateContext( hDC );
		wglMakeCurrent( hDC, gc );
		SET_INT_FIELD("renderContext", (long)gc );

		return 0;
	}
	
	if( !gc )
		return 0;
	
	if( !wglMakeCurrent( hDC, gc ) ) 
	{
		wglMakeCurrent( NULL, NULL );
		printf( "Error in wglMakeCurrent: %d", GetLastError() );
		return 0;

	}
	return 1;
}