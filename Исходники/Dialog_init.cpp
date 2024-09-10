void CDialog_init::OnBnClickedButton1() // load STL file and X-ray contour image
{
    
	vtkSmartPointer<vtkSTLReader> pickedDoneSTL=vtkSmartPointer<vtkSTLReader>::New();	//load STL
	if(!g_prox_or_dist)
		pickedDoneSTL->SetFileName(g_STL_PNG_DIST[0].c_str());
	else
		pickedDoneSTL->SetFileName(g_STL_PNG_PROX[0].c_str());
	pickedDoneSTL->Update();

	transformFilter->SetInputConnection(pickedDoneSTL->GetOutputPort());//move and rotate STL
	translation->Translate(0,0,0);
    transformFilter->SetTransform(translation);
    transformFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(transformFilter->GetOutputPort());
	//mapper->SetInputConnection(pickedDoneSTL->GetOutputPort());
	
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
	vtkSmartPointer<vtkRenderer> FemurRenderer =vtkSmartPointer<vtkRenderer>::New();
    FemurRenderer->AddActor(actor);
   
	vtkSmartPointer<vtkCamera> Femurcam=vtkSmartPointer<vtkCamera>::New();
    Femurcam->SetPosition(0,-DETECTOR_SID/2,0); //555 is a half of SID (=1110)
    Femurcam->SetFocalPoint(0,DETECTOR_SID/2,0);
	Femurcam->SetViewUp(0,-DETECTOR_SID/2,1);
    //Femurcam->SetViewAngle(14.9); 
	Femurcam->SetViewAngle(17); 
	Femurcam->SetClippingRange(-500,700);
	     //fx is roughly 6035 for 1560x1440 images
	     //fx is modified into 6035/2 since our x-ray images has 720x780 sizes.
	     //from this value, we estimated the real size of the detector : Height 132.5 = 360(=720/2)*1110(SID)/3017.5(=6035/2)
	     //Then, one side angle was calucated as 6.807 = atan(DETECTOR_WIDTH/2/1110)
	     //view angle was calculated as 7.45 * 2 = 14.9
    FemurRenderer->SetActiveCamera(Femurcam);
	vtkSmartPointer<vtkJPEGReader> JPEGReader =vtkSmartPointer<vtkJPEGReader>::New(); //load contour image
    if(!g_prox_or_dist)
		JPEGReader->SetFileName(g_STL_PNG_DIST[1].c_str());
	else
		JPEGReader->SetFileName(g_STL_PNG_PROX[1].c_str());
    
	JPEGReader->Update();
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(JPEGReader->GetOutputPort());
    vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();
	//y direction is normal of the plane
	//-z direction is up direction of camera
	//x direction is lateral direction of camera
	
	plane->SetOrigin(0,DETECTOR_SID/2,0);
	plane->SetPoint1(-DETECTOR_WIDTH/2, DETECTOR_SID/2,0);
	plane->SetPoint2(0,DETECTOR_SID/2,-DETECTOR_HEIGHT/2);
	plane->SetNormal(0,DETECTOR_SID/2,0);
	plane->SetResolution(XRAY_WIDTH,XRAY_HEIGHT);
    plane->SetCenter(0,0,0);

    //plane->Push(45);
    vtkSmartPointer<vtkTextureMapToPlane> texturePlane = vtkSmartPointer<vtkTextureMapToPlane>::New();
    texturePlane->SetInputConnection(plane->GetOutputPort());
    vtkSmartPointer<vtkPolyDataMapper> planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    planeMapper->SetInputConnection(texturePlane->GetOutputPort());
    vtkSmartPointer<vtkActor> texturedPlane = vtkSmartPointer<vtkActor>::New();
    texturedPlane->SetMapper(planeMapper);
    texturedPlane->SetTexture(texture);
    vtkSmartPointer<vtkTextActor> textActor=vtkSmartPointer<vtkTextActor>::New();
    textActor->GetTextProperty()->SetFontSize(12);
    textActor->GetTextProperty()->SetColor(1.0,1.0,0.0);
    textActor->SetPosition2(10,20);
    textActor->SetInput("Cam Pos : 0, 555,0");

	vtkSmartPointer<vtkRenderer> ren =vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(ren);
	renderWindow->AddRenderer(FemurRenderer);
    
	vtkSmartPointer<vtkCamera> cam=vtkSmartPointer<vtkCamera>::New();
    cam->SetPosition(0,-DETECTOR_SID/2,0);
    cam->SetFocalPoint(0,DETECTOR_SID/2,0);
    //cam->SetViewAngle(14.9);
	cam->SetViewAngle(17);
	cam->SetViewUp(0,-DETECTOR_SID/2,-1);
	cam->SetClippingRange(-500,700);

    ren->SetActiveCamera(cam);
    ren->AddActor(texturedPlane);
    ren->AddActor(textActor);
    ren->SetBackground(0.2,0.3,0.4);
    ren->SetLayer(0); 
	ren->InteractiveOff();
    FemurRenderer->SetLayer(1); // choose window render for interactor
    renderWindow->SetNumberOfLayers(2);
	CStatic *pclStatic = new CStatic(); 
    LPRECT rect = new CRect; 
	pclStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIEW); 
	renderWindow->SetParentId(pclStatic->m_hWnd);// 
	pclStatic->GetWindowRect(rect); 
    renderWindow->SetSize(rect->right-rect->left, rect->bottom-rect->top); 
    renderWindow->SetPosition(0,0); 
	
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->Render();
    //renderWindowInteractor->Start();	

	vtkSmartPointer<vtkJPEGReader>Load_Drr=vtkSmartPointer<vtkJPEGReader>::New();

	if(!g_prox_or_dist)
		Load_Drr->SetFileName(g_STL_PNG_DIST[0].c_str());
	else
		Load_Drr->SetFileName(g_STL_PNG_PROX[0].c_str());

	Load_Drr->Update();
	m_Px.SetRange(-480,480,TRUE);
	m_Px.SetTicFreq(5);
	m_Px.SetPos(0);
	m_Py.SetRange(-600,600,TRUE);
	m_Py.SetTicFreq(5);
	m_Py.SetPos(0);
	m_Pz.SetRange(-480,480,TRUE);
	m_Pz.SetTicFreq(5);
	m_Pz.SetPos(0);
	m_Rx.SetRange(-480,480,TRUE);
	m_Rx.SetTicFreq(5);
	m_Rx.SetPos(0);
	m_Ry.SetRange(-480,480,TRUE);
	m_Ry.SetTicFreq(5);
	m_Ry.SetPos(0);
	m_Rz.SetRange(-480,480,TRUE);
	m_Rz.SetTicFreq(5);
	m_Rz.SetPos(0);

	CStdioFile file;
	if(!file.Open(_T("Saved_parameter.txt"),CFile::modeRead))
	{
				GetDlgItem(IDC_EDIT1)->SetWindowText(_T("0"));
				GetDlgItem(IDC_EDIT2)->SetWindowText(_T("0"));
				GetDlgItem(IDC_EDIT3)->SetWindowText(_T("0"));
				GetDlgItem(IDC_EDIT4)->SetWindowText(_T("0"));
				GetDlgItem(IDC_EDIT5)->SetWindowText(_T("0"));
				GetDlgItem(IDC_EDIT6)->SetWindowText(_T("0"));
	}
	else
	{
		CString All;
		CString sx[6];
		CString token=_T("");
		int i=0;
		file.ReadString(All);
		while (AfxExtractSubString(token, All, i,' '))
			{   
				sx[i]=token;
			   i++;
			   if(i>=6)break;
			}
					GetDlgItem(IDC_EDIT1)->SetWindowText(sx[0]);
					GetDlgItem(IDC_EDIT2)->SetWindowText(sx[1]);
					GetDlgItem(IDC_EDIT3)->SetWindowText(sx[2]);
					GetDlgItem(IDC_EDIT4)->SetWindowText(sx[3]);
					GetDlgItem(IDC_EDIT5)->SetWindowText(sx[4]);
					GetDlgItem(IDC_EDIT6)->SetWindowText(sx[5]);
		file.Close();
	}
	

	//view2 start
    vtkSmartPointer<vtkRenderer> FemurRenderer2 =vtkSmartPointer<vtkRenderer>::New();
    FemurRenderer2->AddActor(actor);
	vtkSmartPointer<vtkCamera> Femurcam2=vtkSmartPointer<vtkCamera>::New();
    Femurcam2->SetPosition(DETECTOR_SID/2,-DETECTOR_SID/2,0);
    Femurcam2->SetFocalPoint(0,0,0);
    Femurcam2->SetViewAngle(52);
    FemurRenderer2->SetActiveCamera(Femurcam2);
    renderWindow2->AddRenderer(FemurRenderer2);
	
	CStatic *pclStatic2 = new CStatic(); 
    LPRECT rect2 = new CRect; 
	pclStatic2 = (CStatic*)GetDlgItem(IDC_STATIC_VIEW2); 
	renderWindow2->SetParentId(pclStatic2->m_hWnd);// 
	pclStatic2->GetWindowRect(rect2); 
    //renderWindow2->SetSize(rect2->right-rect2->left, rect2->bottom-rect2->top); 
	renderWindow2->SetSize(780, 720); 
    renderWindow2->SetPosition(0,0); 
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor2 =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor2->SetRenderWindow(renderWindow2);
    renderWindow2->Render();
    //renderWindowInteractor2->Start();	
    /////////////////////view2 end
    //view3 start
    vtkSmartPointer<vtkRenderer> FemurRenderer3 =vtkSmartPointer<vtkRenderer>::New();
    FemurRenderer3->AddActor(actor);
	vtkSmartPointer<vtkCamera> Femurcam3=vtkSmartPointer<vtkCamera>::New();

	if(!g_prox_or_dist)
	Femurcam3->SetPosition(0,0, -DETECTOR_SID/2);
	else
    Femurcam3->SetPosition(0,0, -DETECTOR_SID/2);
    Femurcam3->SetFocalPoint(0,0,0);
    Femurcam3->SetViewAngle(52);
    FemurRenderer3->SetActiveCamera(Femurcam3);
    renderWindow3->AddRenderer(FemurRenderer3);
	
	CStatic *pclStatic3 = new CStatic(); 
    LPRECT rect3 = new CRect; 
	pclStatic3 = (CStatic*)GetDlgItem(IDC_STATIC_VIEW3); 
	renderWindow3->SetParentId(pclStatic3->m_hWnd);// 
	pclStatic3->GetWindowRect(rect3); 
    renderWindow3->SetSize(rect3->right-rect3->left, rect3->bottom-rect3->top); 
    renderWindow3->SetPosition(0,0); 
	
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor3 =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor3->SetRenderWindow(renderWindow3);
    renderWindow3->Render();
    renderWindowInteractor3->Start();	
	//view3 end
}