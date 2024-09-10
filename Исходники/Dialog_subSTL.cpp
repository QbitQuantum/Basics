void CDialog_subSTL::OnBnClickedButton1() //load STL
{
	CString strFile = _T("");
    CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.stl)|*.stl|All Files (*.*)|*.*||"), NULL);
    //dlgFile.m_ofn.lpstrInitialDir=_T("D:W\code_LPX");
    if (dlgFile.DoModal())
    {
        strFile = dlgFile.GetPathName();
    } 
    //std::string stdstrFile(CT2CA(strFile));//std::string s((LPCTSTR)strFile);
	//std::string ss((CStringA(strFile)));
    //const char* cstr = (LPCTSTR)strFile;
	CStringA strFileA(strFile);
	
	//vtkSmartPointer<vtkSTLReader> STLReader= vtkSmartPointer<vtkSTLReader>::New();
	p = strFileA.GetString();
	STLReader->SetFileName(p);
	vtkSmartPointer<vtkPolyDataMapper> map=vtkSmartPointer<vtkPolyDataMapper>::New();
	map->SetInput(STLReader->GetOutput());//decimated);
    vtkSmartPointer<vtkActor> act=vtkSmartPointer<vtkActor>::New();
    act->SetMapper(map);
    vtkSmartPointer<vtkRenderer> ren_STL=vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renwin_STL=vtkSmartPointer<vtkRenderWindow>::New();
    ren_STL->AddActor(act);
    renwin_STL->AddRenderer(ren_STL);
    
    CStatic *pclStatic = new CStatic(); //show VTK window on MFC
    LPRECT rect = new CRect; 
    pclStatic = (CStatic*)GetDlgItem(IDC_STATIC_V); 
	renwin_STL->SetParentId(pclStatic->m_hWnd);// 
	pclStatic->GetWindowRect(rect); 
    renwin_STL->SetSize(rect->right-rect->left, rect->bottom-rect->top); 
    renwin_STL->SetPosition(0,0); 
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor_STL =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor_STL->SetRenderWindow(renwin_STL);
	renwin_STL->Render();
    renderWindowInteractor_STL->Start();
}