HRESULT ComRegistration::registerTypeLib( HMODULE hInst )
{
	//get the qualified path of the dll calling this function
	WCHAR modulePath[MAX_PATH];
	GetModuleFileName( hInst, modulePath, MAX_PATH );

	ITypeLib *ptlib;

	HRESULT hr = LoadTypeLib( modulePath, &ptlib );
	if( !SUCCEEDED(hr) ) return hr;

	hr = RegisterTypeLib( ptlib, modulePath, NULL );
	
	ptlib->Release();

	return hr;
}