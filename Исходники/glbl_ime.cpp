/*
 * Initialize Global IME.
 * "atom" must be return value of RegisterClass(Ex).
 */
    void
global_ime_init(ATOM atom, HWND hWnd)
{
    IUnknown *pI;
    HRESULT hr;

    if (pIApp != NULL || pIMsg != NULL)
	return;
    OleInitialize(NULL);

    /*
     * Get interface IUnknown
     */
    hr = CoCreateInstance(CLSID_CActiveIMM, NULL, CLSCTX_SERVER,
	    IID_IUnknown, (void**)&pI);
    if (FAILED(hr) || !pI)
	return;

    /*
     * Get interface IActiveIMMApp
     */
    hr = pI->QueryInterface(IID_IActiveIMMApp, (void**)&pIApp);
    if (FAILED(hr))
	pIApp = NULL;

    /*
     * Get interface IActiveIMMMessagePumpOwner
     */
    hr = pI->QueryInterface(IID_IActiveIMMMessagePumpOwner, (void**)&pIMsg);
    if (FAILED(hr))
	pIMsg = NULL;

    if (pIApp != NULL)
    {
	pIApp->Activate(TRUE);
	pIApp->FilterClientWindows(&atom, 1);
    }
    if (pIMsg != NULL)
	pIMsg->Start();

    pI->Release();
    s_hWnd = hWnd;
}