// Given an EXCEPINFO, register the error information with the
// IErrorInfo interface.
BOOL PyCom_SetCOMErrorFromExcepInfo(const EXCEPINFO *pexcepinfo, REFIID riid)
{
	ICreateErrorInfo *pICEI;
	HRESULT hr = CreateErrorInfo(&pICEI);
	if ( SUCCEEDED(hr) )
	{
		pICEI->SetGUID(riid);
		pICEI->SetHelpContext(pexcepinfo->dwHelpContext);
		if ( pexcepinfo->bstrDescription )
			pICEI->SetDescription(pexcepinfo->bstrDescription);
		if ( pexcepinfo->bstrHelpFile )
			pICEI->SetHelpFile(pexcepinfo->bstrHelpFile);
		if ( pexcepinfo->bstrSource )
			pICEI->SetSource(pexcepinfo->bstrSource);

		IErrorInfo *pIEI;
		Py_BEGIN_ALLOW_THREADS
		hr = pICEI->QueryInterface(IID_IErrorInfo, (LPVOID*) &pIEI);
		Py_END_ALLOW_THREADS
		if ( SUCCEEDED(hr) )
		{
			SetErrorInfo(0, pIEI);
			pIEI->Release();
		}
		pICEI->Release();			
	}
	return SUCCEEDED(hr);
}