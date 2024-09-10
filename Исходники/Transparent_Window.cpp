// +--------------+
// | D3DStartup() |
// +--------------+----------------------------------+
// | Initialise Direct3D and perform once only tasks |
// +-------------------------------------------------+
HRESULT D3DStartup(HWND hWnd)
{
  BOOL                  bCompOk             = FALSE;   // Is composition enabled? 
  D3DPRESENT_PARAMETERS pp;                            // Presentation prefs
  DWORD                 msqAAQuality        = 0;       // Non-maskable quality
  D3DLIGHT9             ltDirectionalLight;            // Light description
  D3DVECTOR             vctLightDirection   = {-1.0f,  // X component
                                               -0.3f,  // Y component
                                               -1.0f}; // Z component
  D3DXMATRIX            mtxView;                       // View matrix
  D3DXMATRIX            mtxProjection;                 // Projection matrix

  // Make sure that DWM composition is enabled
  DwmIsCompositionEnabled(&bCompOk);
  if(!bCompOk) return E_FAIL;

  // Create a Direct3D object
  if(FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &g_pD3D))) return E_FAIL;

  // Setup presentation parameters
  ZeroMemory(&pp, sizeof(pp));
  pp.Windowed            = TRUE;
  pp.SwapEffect          = D3DSWAPEFFECT_DISCARD; // Required for multi sampling
  pp.BackBufferFormat    = D3DFMT_A8R8G8B8;       // Back buffer format with alpha channel

  // Set highest quality non-maskable AA available or none if not
  if(SUCCEEDED(g_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
                                                  D3DDEVTYPE_HAL,
                                                  D3DFMT_A8R8G8B8,
                                                  TRUE,
                                                  D3DMULTISAMPLE_NONMASKABLE,
                                                  &msqAAQuality
                                                  )))
  {
    // Set AA quality
   /* pp.MultiSampleType     = D3DMULTISAMPLE_NONMASKABLE;
    pp.MultiSampleQuality  = msqAAQuality - 1;*/
  }
  else
  {
    // No AA
    pp.MultiSampleType     = D3DMULTISAMPLE_NONE;
  }

  // Create a Direct3D device object
  if(FAILED(g_pD3D->CreateDeviceEx(D3DADAPTER_DEFAULT,
                                   D3DDEVTYPE_HAL,
                                   hWnd,
                                   D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                   &pp,
                                   NULL,
                                   &g_pD3DDevice
                                   ))) return E_FAIL;

  // Configure the device state
  g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);        // Enable 3D lighting
  g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, ARGB_AMBIENT); // Set ambient lighting
  g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE); // Disable specular highlighting
  
  // Create a directional light
  ZeroMemory(&ltDirectionalLight, sizeof(ltDirectionalLight));
  ltDirectionalLight.Type       = D3DLIGHT_DIRECTIONAL;
  ltDirectionalLight.Diffuse.r  = 1.0f;
  ltDirectionalLight.Diffuse.g  = 1.0f;
  ltDirectionalLight.Diffuse.b  = 1.0f;
  ltDirectionalLight.Diffuse.a  = 1.0f;				
  ltDirectionalLight.Direction  = vctLightDirection;

  // Add as light 0
  g_pD3DDevice->SetLight(0, &ltDirectionalLight);
  g_pD3DDevice->LightEnable(0, TRUE);

  // Configure camera
  D3DXMatrixLookAtLH(&mtxView,
                     &D3DXVECTOR3 (0.0f, 0.0f, 25.0f), // Camera position
                     &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),  // Look-at target
                     &D3DXVECTOR3 (0.0f, 1.0f, 0.0f)); // Up direction
  g_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

  // Configure projection
  D3DXMatrixPerspectiveFovLH(&mtxProjection,
                             D3DXToRadian(45),                          // Horizontal field of view
                             (FLOAT)((FLOAT)g_iWidth/(FLOAT)g_iHeight),	// Aspect ratio
                             0.0f,										                  // Near view plane
                             100.0f);										                // Far view plane
  g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

  return S_OK;
}