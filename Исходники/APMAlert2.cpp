void SetupHooks() {
	logInfo("Setting up hooks.");
	if(hooksSetup) return;

	HMODULE d3dMod = GetModuleHandle("d3d9.dll");
	if(d3dMod == NULL) {
		ErrorMsg("GetModuleHandle(d3d9.dll)");
		return;
	}
	HMODULE d3dxMod = LoadLibrary("d3dx9_43.dll");
	if(d3dxMod == NULL) {
		ErrorMsg("LoadLibrary(d3dx9_43.dll)");
		return;
	}
	HMODULE winmmMod = LoadLibrary("winmm.dll");
	if(winmmMod == NULL) {
		ErrorMsg("LoadLibrary(winmm.dll)");
		return;
	}

	D3DCreate = (pDirect3DCreate9)GetProcAddress(d3dMod, "Direct3DCreate9");
	if(D3DCreate == NULL) {
		ErrorMsg("GetProcAddress(d3dMod, \"Direct3DCreate9\")");
		return;
	}
	oPlaySound = (pPlaySoundA)GetProcAddress(winmmMod, "PlaySoundA");
	if(oPlaySound == NULL) {
		ErrorMsg("GetProcAddress(winmmMod, \"PlaySoundA\")");
		return;
	}
	oD3DXCreateFont = (pD3DXCreateFont)GetProcAddress(d3dxMod, "D3DXCreateFontA");
	if(oD3DXCreateFont == NULL) {
		ErrorMsg("GetProcAddress(d3dxMod, \"D3DXCreateFontA\")");
		return;
	}
	oD3DXCreateLine = (pD3DXCreateLine)GetProcAddress(d3dxMod, "D3DXCreateLine");
	if(oD3DXCreateLine == NULL) {
		ErrorMsg("GetProcAddress(d3dxMod, \"D3DXCreateLine\")");
		return;
	}

	// Create a dummy window to call CreateDevice on
    HWND hwnd;
	hwnd = CreateWindow("BUTTON", "APMAlertDummyWindow", 0, 0, 0, 27, 27, NULL, NULL, hInstance, NULL);
	if(hwnd == NULL) {
		ErrorMsg("CreateWindow");
		return;
	}

    //UpdateWindow(hwnd);

	IDirect3D9 *pD3D = D3DCreate(D3D_SDK_VERSION);
	if(pD3D == NULL) {
		ErrorMsg("Direct3DCreate9");
		return;
	}
	D3DDISPLAYMODE d3ddm;
	HRESULT hRes = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if(FAILED(hRes)) { 
		char errorMsg[512];
		const char * dxErrorStr = DXGetErrorString(hRes);
		sprintf_s(errorMsg, 512, "GetAdapterDisplayMode returned 0x%08x: %s", hRes, dxErrorStr);
		logError(errorMsg);
		goto cleanup;
	}
	D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = d3ddm.Format;

	IDirect3DDevice9 * ppD3DDevice;

	hRes = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
						&d3dpp, &ppD3DDevice);
	if(FAILED(hRes)) {
		char errorMsg[512];
		const char * dxErrorStr = DXGetErrorString(hRes);
		sprintf_s(errorMsg, 512, "CreateDevice returned 0x%08x: %s", hRes, dxErrorStr);
		logError(errorMsg);
		goto cleanup;
	}

	// Get our function pointers from the virtual table
	// This pointer dereferencing works because the virtual table is the first item in memory
	//  of the every object
	void ** vTable = *((void***)ppD3DDevice);

	// Access the function pointers we need
	addrEndScene = vTable[42]; // EndScene is the 43rd function (you can just count in the interface decl in the header)

	/*
	char path_d3d9_dll[MAX_PATH];
	GetSystemDirectory(path_d3d9_dll, MAX_PATH);	
	strncat_s(path_d3d9_dll, MAX_PATH, "\\d3d9.dll", 10);
	SIZE_T offset = (unsigned int)addrEndScene - (unsigned int)GetModuleHandle(path_d3d9_dll);
	printf("EndScene() Addr: 0x%08x -- SC2.exe!d3d9.dll+0x%x\n", addrEndScene, offset);
	*/

	DWORD oldProtect;
	// backup the top 6 bytes of each function
	if(VirtualProtect(addrEndScene, 6, PAGE_EXECUTE_READWRITE, &oldProtect) == FALSE) {
		ErrorMsg("VirtualProtect");
		return; // make the address read/writable
	}
	memcpy(backup_EndScene, addrEndScene, 6);
	VirtualProtect(addrEndScene, 6, oldProtect, &oldProtect); // restore old protection

	// We are going to write over the top 6 bytes of every function we want to hook.
	// This way, whenever they are called, we can jump to our custom hook function and run our own stuff.
	// To maintain proper game functionality we will restore the backup code, run the function as it should be, 
	// then restore our patch code at the top when it returns to our hook function.
	
	// create our 6 byte patch consisting of: push <addr_hook>; retn (essentially a call that doesn't disturb the stack)
	patch_EndScene[0] = 0x68; // PUSH
	*((DWORD *)(patch_EndScene+1)) = (DWORD)&hkEndScene; // value to push
	patch_EndScene[5] = 0xC3; // RETN

	hooksSetup = true;

	logInfo("Hooks setup and ready for use.");

	ppD3DDevice->Release();
	ppD3DDevice = NULL;
	pD3D->Release();
	pD3D = NULL;

cleanup:
	if(pD3D != NULL)
		pD3D->Release();
	// Destroy the dummy window
	DestroyWindow(hwnd);
}