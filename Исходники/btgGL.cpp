void btgGLInit(CView *pView)
{
	oldRect = drawRect;

	pView->GetClientRect(&drawRect);

	if(oldRect != drawRect)
	{
		if (hGLDeviceContext != NULL)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hGLRenderContext);
			hGLRenderContext = 0;
		}
	}

	hGLDeviceContext = wglGetCurrentDC();
	if (hGLDeviceContext == NULL || hGLRenderContext == 0)
	{
		hGLDeviceContext = ::GetDC(pView->GetSafeHwnd());

		setupPixelFormat(hGLDeviceContext);
		setupPalette(hGLDeviceContext);
		hGLRenderContext = wglCreateContext(hGLDeviceContext);  //create GL render context and select into window
		wglMakeCurrent(hGLDeviceContext, hGLRenderContext);

		//create the viewport for rendering
		auxInitPosition(0, 0, drawRect.right - drawRect.left, drawRect.bottom - drawRect.top);
		//set mode (direct color)
		auxInitDisplayMode(AUX_RGB);
	}
	else
	{
		//wglMakeCurrent(hGLDeviceContext, hGLRenderContext);
	}

	CBTGDoc* pDoc = (CBTGDoc*)pView->GetDocument();
	glClearColor((GLfloat)pDoc->mBGRed / 255.0f,
				 (GLfloat)pDoc->mBGGreen / 255.0f,
				 (GLfloat)pDoc->mBGBlue / 255.0f,
				 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, drawRect.right - drawRect.left, 0, drawRect.bottom - drawRect.top);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}