void
addCircleThroughCom()
{
    AutoCAD::IAcadApplication *pAcad;
    AutoCAD::IAcadDocument *pDoc;
    AutoCAD::IAcadModelSpace *pMSpace;

    HRESULT hr = NOERROR;
    LPUNKNOWN pUnk = NULL;
    LPDISPATCH pAcadDisp = acedGetIDispatch(TRUE); 
	if(pAcadDisp==NULL)
		return;
	
	hr = pAcadDisp->QueryInterface(AutoCAD::IID_IAcadApplication,(void**)&pAcad);
	pAcadDisp->Release();
	if (FAILED(hr))
		return;

	hr = pAcad->get_ActiveDocument(&pDoc);
	pAcad->Release();
	if (FAILED(hr))
		return;

	hr = pDoc->get_ModelSpace(&pMSpace);
	pDoc->Release();
	if (FAILED(hr))
		return;


    SAFEARRAYBOUND rgsaBound;
    rgsaBound.lLbound = 0L;
    rgsaBound.cElements = 3;
    long i;
    SAFEARRAY* pStartPoint = NULL;
    pStartPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);

    i = 0;
    double value = 4.0;
    SafeArrayPutElement(pStartPoint, &i, &value);
    
    i = 1;
    value = 2.0;
    SafeArrayPutElement(pStartPoint, &i, &value);
    
    i = 2;
    value = 0.0;
    SafeArrayPutElement(pStartPoint, &i, &value);
    
    VARIANT pt1;
    pt1.vt = VT_ARRAY | VT_R8;
    pt1.parray = pStartPoint;

    AutoCAD::IAcadCircle *pCircle;
    pMSpace->AddCircle(pt1, 2.0, &pCircle);
	VariantClear(&pt1);
    pMSpace->Release();
}