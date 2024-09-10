//------------------------------------------------------------------------------------------------
// Name: acquireGraphics
// Desc: Implements a robust algorithm to create the Direct3D device
//------------------------------------------------------------------------------------------------
bool EvidyonClient::createD3DDevice(bool windowed, unsigned int requiredNumberOfBlendMatrices)
{
  // Get the main Direct3D object from the display structure
  IDirect3D9* d3d = d3d_;

  { // Display the adapter that we are using
    D3DADAPTER_IDENTIFIER9 identifier;
    if (!APP_WARNING(FAILED(d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &identifier)))("Failed to get adapter information"))
      DEBUG_INFO("Using \"%s\"", identifier.Description);
  }

  // Set up the structure used to create the Direct3D device.
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp, sizeof(d3dpp));

  // Initialize some parts of the parameters
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.EnableAutoDepthStencil = TRUE;
  d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
  //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
  d3dpp.BackBufferCount = 1;
  //d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

  // Set up the rest of the parameters based on the windowed mode
  if (windowed)
  {
    d3dpp.Windowed = TRUE;
		d3dpp.BackBufferWidth  = config_.getSetting("Graphics", "ResolutionX", 800);
    d3dpp.BackBufferHeight = config_.getSetting("Graphics", "ResolutionY", 600);
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the application's window
    RECT rc = { 0, 0, d3dpp.BackBufferWidth, d3dpp.BackBufferHeight };
    AdjustWindowRect(&rc, WS_POPUPWINDOW|WS_CAPTION, FALSE);
    d3dpp.hDeviceWindow = CreateWindow(STRING_WINDOWCLASS,
                                       STRING_WINDOWTITLE, 
                                       WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX,
                                       50,
                                       50,
                                       rc.right-rc.left,
                                       rc.bottom-rc.top,
                                       NULL,
                                       NULL,
                                       GetModuleHandle(NULL),
                                       NULL);
  }
  else
  {
    // Get the current display mode (this should always succeed)
    D3DDISPLAYMODE displayMode;
    if (APP_ERROR(FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))("Couldn't get current display mode"))
      return false;

    // Use the current display mode
    d3dpp.Windowed = FALSE;
		d3dpp.BackBufferWidth  = config_.getSetting("Graphics", "ResolutionX", (int)displayMode.Width);
    d3dpp.BackBufferHeight = config_.getSetting("Graphics", "ResolutionY", (int)displayMode.Height);

    switch (config_.getSetting("Graphics", "ColorDepth", 16)) {
      default:
      case 16: d3dpp.BackBufferFormat = D3DFMT_R5G6B5; break;
      case 15: d3dpp.BackBufferFormat = D3DFMT_X1R5G5B5; break;
      case 24: d3dpp.BackBufferFormat = D3DFMT_R8G8B8; break;
      case 32: d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; break;
    }

    // Create the application's window
    d3dpp.hDeviceWindow = CreateWindow(STRING_WINDOWCLASS, STRING_WINDOWTITLE, 
                      WS_POPUP, 0, 0, d3dpp.BackBufferWidth, d3dpp.BackBufferHeight,
                      NULL, NULL, GetModuleHandle(NULL), NULL);
  }

  // Make sure a window was created
  if (APP_ERROR(d3dpp.hDeviceWindow == NULL)("Unable to create application window"))
  {
    // Try again in windowed mode if this was fullscreen; otherwise, fail
    if (!windowed)
      return createD3DDevice(true, requiredNumberOfBlendMatrices);
    else
      return false;
  }

  // Should we force the rendering into software mode?
  bool forceSoftwareMode = config_.getSetting("Graphics", "ForceSoftwareRendering", 0) == 1;

  // Parameters that will be used to create the device
  bool createHardwareDevice = !forceSoftwareMode;  // Use D3DCREATE_HARDWARE_VERTEXPROCESSING; otherwise, D3DCREATE_SOFTWARE_VERTEXPROCESSING
  bool createPureDevice = false;    // Set the D3DCREATE_PUREDEVICE flag.  Only valid if createHardwareDevice is true.
  bool createMixedDevice = false;   // Set the D3DCREATE_MIXED_VERTEXPROCESSING flag.  Only valid if createHardwareDevice is false.

  // Get device capabilities so we can determine what kind of device to make
  D3DCAPS9 devCaps;
  if (!APP_ERROR(FAILED(d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devCaps)))("Couldn't get device capibilities"))
  {
    // Determine whether or not we can use a pure hardware device
    createPureDevice = createHardwareDevice && ((devCaps.DevCaps & D3DDEVCAPS_PUREDEVICE) != 0);


    if (APP_WARNING(devCaps.MaxVertexBlendMatrices < 4 || devCaps.MaxVertexBlendMatrixIndex + 1 < requiredNumberOfBlendMatrices)
        ("This computer's hardware doesn't support indexed blended animation; using software device to compensate"))
    {
      createHardwareDevice = false;
      createMixedDevice = false;    //createMixedDevice = true;
    }
  }

  createPureDevice = false;


  // Build the flags for the device creation procedure
  DWORD createFlags = createHardwareDevice ? (D3DCREATE_HARDWARE_VERTEXPROCESSING | (createPureDevice ? D3DCREATE_PUREDEVICE : 0)) :
               (createMixedDevice ? D3DCREATE_MIXED_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING);

  // Create the Direct3D device here
  IDirect3DDevice9* d3dDevice;
  if (APP_ERROR(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, createFlags, &d3dpp, &d3dDevice)))("Failed to create optimal Direct3D device"))
  {
    // Set up the most generic-possible flags and attempt to create again
    d3dpp.PresentationInterval = 0;
    createFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    createMixedDevice = false;

    // Try to create again
    if (APP_FATAL(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, createFlags, &d3dpp, &d3dDevice)))("Failed to create fallback Direct3D device"))
    {
      // If we were creating in fullscreen mode, try again in windowed mode
      if (!windowed)
      {
        // Kill the window we made
        DestroyWindow(d3dpp.hDeviceWindow);

        // Inidicate what's going to happen
        DEBUG_INFO("Failed to create a fullscreen device; trying windowed mode");

        // Try again in windowed mode
        return createD3DDevice(true, requiredNumberOfBlendMatrices);
      }
    }
    else
    {
      // Let the user know that we recovered
      DEBUG_INFO("Recovered from failure to create optimal D3D device by resorting to fallback settings");
    }
  }

  // Save the device and parameters as output
  d3d_device_ = d3dDevice;
  myMainWindow = d3dpp.hDeviceWindow;
  myUsingMixedDeviceFlag = createMixedDevice;
  myUsingSoftwareDeviceFlag = (createFlags & D3DCREATE_SOFTWARE_VERTEXPROCESSING) == D3DCREATE_SOFTWARE_VERTEXPROCESSING;
  memcpy_s(&d3d_params_, sizeof(d3d_params_), &d3dpp, sizeof(d3dpp));

  // Success
  return true;
}