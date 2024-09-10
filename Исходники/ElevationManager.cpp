//
//  FUNCTION: private CoCreateInstanceAsAdmin(HWND, REFCLSID, REFIID, __out void**)
//
//  PURPOSE: Creates an instance of the specified IID in an elevated process us the COM Elevation Moniker.
//
//  COMMENTS:
//		hwndMain	- The Window associated with this call.
//		rclsid		- CLSID associated with the data and code that will be used to create the object. 
//		riid		- Reference to the identifier of the interface to be used to communicate with the object.
//		ppv			- [out] Address of pointer variable that receives the interface pointer requested in riid. 
//						Upon successful return, *ppv contains the requested interface pointer. 
//						Upon failure, *ppv contains NULL.
//
//		Fails if:	-User declines Elevation
//					-{CLSID}/Elevation/Enabled != 1 (See Register.cpp)
//					-{CLSID}/LocalizedString not set or invalid (See Register.cpp)
//
HRESULT ElevationManager::CoCreateInstanceAsAdmin(HWND hwndMain, __in REFCLSID rclsid, __in REFIID riid, __deref_out void ** ppv)
{
    BIND_OPTS3 bo;
	WCHAR  wszCLSID[CLSIDSize];
	WCHAR  wszMonikerName[MonikerSize+CLSIDSize];

    StringFromGUID2(rclsid, wszCLSID, ARRAYSIZE(wszCLSID)); 
    HRESULT hr = StringCchPrintf(wszMonikerName, ARRAYSIZE(wszMonikerName), MonikerName, wszCLSID);
    if (FAILED(hr))
        return hr;
    memset(&bo, 0, sizeof(bo));
    bo.cbStruct = sizeof(bo);
    bo.hwnd = hwndMain;
	bo.dwClassContext  = CLSCTX_LOCAL_SERVER;
    hr = CoGetObject(wszMonikerName, &bo, riid, ppv);
	return hr;
}