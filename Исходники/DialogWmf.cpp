//*********************************
// OnButtonRun 
//*********************************
void CDialogWmf::OnButtonRun() 
{
	
	BeginWaitCursor();

	UpdateData(TRUE);

	// Get DC
	CDC *pDC = m_pDoc->GetView()->GetDC();
	ASSERT(pDC);

	// Get view rect
	CRect rect;
	m_pDoc->GetView()->GetClientRect(&rect);
	rect.InflateRect(5,5);

	// Create metafile device context
	HDC hMetaDC = CreateEnhMetaFile(pDC->m_hDC,"metafile.emf",NULL,NULL);
	if(!hMetaDC)
	{
		AfxMessageBox("Unable to create MetaFile");
		ReleaseDC(pDC);
		return;
	}

	// Get DC from handle
	CDC *pMetaDC = CDC::FromHandle(hMetaDC);
	ASSERT(pMetaDC);
	pMetaDC->SetMapMode(MM_TEXT); 

	// Position / translation / scale
	glPushMatrix();
	CMeshView *pView = (CMeshView *)m_pDoc->GetView();
	glTranslated(pView->m_xTranslation,pView->m_yTranslation,pView->m_zTranslation);
	glRotatef(pView->m_xRotation, 1.0, 0.0, 0.0);
	glRotatef(pView->m_yRotation, 0.0, 1.0, 0.0);
	glRotatef(pView->m_zRotation, 0.0, 0.0, 1.0);
	glScalef(pView->m_xScaling,pView->m_yScaling,pView->m_zScaling);

	// Get OpenGL parameters
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];
	glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
	glGetIntegerv(GL_VIEWPORT,viewport);

	// Start rendering via std GDI 2D drawing functions
	CSceneGraph3d *pScene = &m_pDoc->m_SceneGraph;
	for(int i=0;i<pScene->NbObject();i++)
	{
		CObject3d *pObject = pScene->GetAt(i);
		if(pObject->GetType() == TYPE_MESH3D) // meshes only
			// The line mode (no sort)
			if(m_Mode == MODE_LINE) 
				((CMesh3d *)pObject)->glDrawProjectLine(pMetaDC,
				                                        modelMatrix,
																								projMatrix,
																								viewport,
																								m_ColorLine,
																								m_Ratio,
																								rect.Height());
			else 
				// The face mode (faces are z-sorted 
				// according to their barycenter)
				((CMesh3d *)pObject)->glDrawProjectFace(pMetaDC,
				                                        modelMatrix,
																								projMatrix,
																								viewport,
																								m_ColorLine,
																								m_ColorFace,
																								m_Ratio,
																								rect.Height(),
																								m_RatioNbFaces);
	}

	glPopMatrix();

	// Close metafile
	HENHMETAFILE hMetaFile = CloseEnhMetaFile(hMetaDC);

	// Fill the clipboard (direct sent to wmf2eps or 
	// any windows app such as Powerpoint)
	OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_ENHMETAFILE,CopyEnhMetaFile(hMetaFile,NULL));
	CloseClipboard();

	// Cleanup
	DeleteEnhMetaFile(hMetaFile);
	ReleaseDC(pDC);

	EndWaitCursor();
}