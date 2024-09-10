bool
DeviceManagerD3D9::Init()
{
  WNDCLASSW wc;
  HRESULT hr;

  if (!GetClassInfoW(GetModuleHandle(NULL), kClassName, &wc)) {
      ZeroMemory(&wc, sizeof(WNDCLASSW));
      wc.hInstance = GetModuleHandle(NULL);
      wc.lpfnWndProc = ::DefWindowProc;
      wc.lpszClassName = kClassName;
      if (!RegisterClassW(&wc)) {
          NS_WARNING("Failed to register window class for DeviceManager.");
          return false;
      }
  }

  mFocusWnd = ::CreateWindowW(kClassName, L"D3D9Window", WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL,
                              NULL, GetModuleHandle(NULL), NULL);

  if (!mFocusWnd) {
    NS_WARNING("Failed to create DeviceManagerD3D9 Window.");
    return false;
  }

  /* Create an Nv3DVUtils instance */ 
  if (!mNv3DVUtils) { 
    mNv3DVUtils = new Nv3DVUtils(); 
    if (!mNv3DVUtils) { 
      NS_WARNING("Could not create a new instance of Nv3DVUtils.\n"); 
    } 
  } 

  /* Initialize the Nv3DVUtils object */ 
  if (mNv3DVUtils) { 
    mNv3DVUtils->Initialize(); 
  } 

  HMODULE d3d9 = LoadLibraryW(L"d3d9.dll");
  Direct3DCreate9Func d3d9Create = (Direct3DCreate9Func)
    GetProcAddress(d3d9, "Direct3DCreate9");
  Direct3DCreate9ExFunc d3d9CreateEx = (Direct3DCreate9ExFunc)
    GetProcAddress(d3d9, "Direct3DCreate9Ex");
  
#ifdef USE_D3D9EX
  if (d3d9CreateEx) {
    hr = d3d9CreateEx(D3D_SDK_VERSION, getter_AddRefs(mD3D9Ex));
    if (SUCCEEDED(hr)) {
      mD3D9 = mD3D9Ex;
    }
  }
#endif

  if (!mD3D9) {
    if (!d3d9Create) {
      return false;
    }

    mD3D9 = dont_AddRef(d3d9Create(D3D_SDK_VERSION));

    if (!mD3D9) {
      return false;
    }
  }

  D3DADAPTER_IDENTIFIER9 ident;
  hr = mD3D9->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &ident);

  if (FAILED(hr)) {
    return false;
  }

  if (!PL_strncasecmp(ident.Driver, "nvumdshim.dll", PL_strlen(ident.Driver))) {
    // XXX - This is a device using NVidia Optimus. We have no idea how to do
    // interop here so let's fail and use BasicLayers. See bug 597320.
    return false;
  }

  D3DPRESENT_PARAMETERS pp;
  memset(&pp, 0, sizeof(D3DPRESENT_PARAMETERS));

  pp.BackBufferWidth = 1;
  pp.BackBufferHeight = 1;
  pp.BackBufferFormat = D3DFMT_A8R8G8B8;
  pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  pp.Windowed = TRUE;
  pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
  pp.hDeviceWindow = mFocusWnd;

  if (mD3D9Ex) {
    hr = mD3D9Ex->CreateDeviceEx(D3DADAPTER_DEFAULT,
                                 D3DDEVTYPE_HAL,
                                 mFocusWnd,
                                 D3DCREATE_FPU_PRESERVE |
                                 D3DCREATE_MULTITHREADED |
                                 D3DCREATE_MIXED_VERTEXPROCESSING,
                                 &pp,
                                 NULL,
                                 getter_AddRefs(mDeviceEx));
    if (SUCCEEDED(hr)) {
      mDevice = mDeviceEx;
    }

    D3DCAPS9 caps;
    if (mDeviceEx && mDeviceEx->GetDeviceCaps(&caps)) {
      if (LACKS_CAP(caps.Caps2, D3DCAPS2_DYNAMICTEXTURES)) {
        // XXX - Should we actually hit this we'll need a CanvasLayer that
        // supports static D3DPOOL_DEFAULT textures.
        NS_WARNING("D3D9Ex device not used because of lack of support for \
                   dynamic textures. This is unexpected.");
        mDevice = nsnull;
        mDeviceEx = nsnull;
      }
    }
  }