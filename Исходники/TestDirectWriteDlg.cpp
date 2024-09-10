HRESULT CTestDirectWriteDlg::CreateDevInDependentResources()
{
	HRESULT hr = S_OK;
	IFR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory));

	IFR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)));

	IDWriteFontFacePtr pFontFace = NULL;
	IDWriteFontFilePtr pFontFiles = NULL;

	if (SUCCEEDED(hr))
	{
		CString strPath;

		 // open a file name
		ZeroMemory( &ofn , sizeof( ofn));
		ofn.lStructSize = sizeof ( ofn );
		ofn.hwndOwner = NULL  ;
		ofn.lpstrFile = szFile ;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof( szFile );
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TTF\0";
		ofn.nFilterIndex =1;
		ofn.lpstrFileTitle = NULL ;
		ofn.nMaxFileTitle = 0 ;
		ofn.lpstrInitialDir=NULL ;
		ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;
		GetOpenFileName( &ofn );
	
		// Now simpley display the file name 
		MessageBox (ofn.lpstrFile , L"File Name" , MB_OK);

		strPath.ReleaseBuffer ();
		strPath += szFile;

		hr = m_pDWriteFactory->CreateFontFileReference(
			strPath,
			NULL,
			&pFontFiles);
	}

	IDWriteFontFile* fontFileArray[] = {pFontFiles};

	if(pFontFiles==NULL)
	{
		MessageBox(L"No font file is found at executable folder", L"Error");
		return E_FAIL;
	}

	IFR(m_pDWriteFactory->CreateFontFace(
		DWRITE_FONT_FACE_TYPE_TRUETYPE,
		1, // file count
		fontFileArray,
		0,
		DWRITE_FONT_SIMULATIONS_NONE,
		&pFontFace
		));

	//CString szOutline = m_szOutline;
	CString szOutline(L"Hello!");

	UINT* pCodePoints = new UINT[szOutline.GetLength()];
	UINT16* pGlyphIndices = new UINT16[szOutline.GetLength()];
	ZeroMemory(pCodePoints, sizeof(UINT) * szOutline.GetLength());
	ZeroMemory(pGlyphIndices, sizeof(UINT16) * szOutline.GetLength());
	for(int i=0; i<szOutline.GetLength(); ++i)
	{
		pCodePoints[i] = szOutline.GetAt(i);
	}
	pFontFace->GetGlyphIndicesW(pCodePoints, szOutline.GetLength(), pGlyphIndices);

	//Create the path geometry
	IFR(m_pD2DFactory->CreatePathGeometry(&m_pPathGeometry));

	IFR(m_pPathGeometry->Open((ID2D1GeometrySink**)&m_pGeometrySink));

	IFR(pFontFace->GetGlyphRunOutline(
		ConvertPointSizeToDIP(48.0f), 
		pGlyphIndices, 
		NULL,
		NULL,
		szOutline.GetLength(),
		FALSE,
		FALSE,
		m_pGeometrySink));

	IFR(m_pGeometrySink->Close());

	if(pCodePoints)
	{
		delete [] pCodePoints;
		pCodePoints = NULL;
	}

	if(pGlyphIndices)
	{
		delete [] pGlyphIndices;
		pGlyphIndices = NULL;
	}

	return hr;
}