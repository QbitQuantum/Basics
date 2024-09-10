/**
 * This function is only called in non-native mode
 * Its responsibility is to initialize D3D, create a device and a device manager
 * and call SetD3DDeviceManager with it.
 */
HRESULT CDecDXVA2::InitD3D()
{
  HRESULT hr = S_OK;

  if (FAILED(hr = LoadDXVA2Functions())) {
    DbgLog((LOG_ERROR, 10, L"-> Failed to load DXVA2 DLL functions"));
    return E_FAIL;
  }

  m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
  if (!m_pD3D) {
    DbgLog((LOG_ERROR, 10, L"-> Failed to acquire IDirect3D9"));
    return E_FAIL;
  }

  int lAdapter = D3DADAPTER_DEFAULT;

  D3DADAPTER_IDENTIFIER9 d3dai = {0};
  m_pD3D->GetAdapterIdentifier(lAdapter, 0, &d3dai);

  const char *vendor = "Unknown";
  for (int i = 0; vendors[i].id != 0; i++) {
    if (vendors[i].id == d3dai.VendorId) {
      vendor = vendors[i].name;
      break;
    }
  }

  DbgLog((LOG_TRACE, 10, L"-> Running on adapter %d, %S, vendor 0x%04X(%S), device 0x%04X", lAdapter, d3dai.Description, d3dai.VendorId, vendor, d3dai.DeviceId));
  m_dwVendorId = d3dai.VendorId;
  m_dwDeviceId = d3dai.DeviceId;

  D3DPRESENT_PARAMETERS d3dpp;
  D3DDISPLAYMODE d3ddm;

  ZeroMemory(&d3dpp, sizeof(d3dpp));
  m_pD3D->GetAdapterDisplayMode(lAdapter, &d3ddm);

  d3dpp.Windowed               = TRUE;
  d3dpp.BackBufferWidth        = 640;
  d3dpp.BackBufferHeight       = 480;
  d3dpp.BackBufferCount        = 0;
  d3dpp.BackBufferFormat       = d3ddm.Format;
  d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
  d3dpp.Flags                  = D3DPRESENTFLAG_VIDEO;

  hr = m_pD3D->CreateDevice(lAdapter, D3DDEVTYPE_HAL, GetShellWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE, &d3dpp, &m_pD3DDev);
  if (FAILED(hr)) {
    DbgLog((LOG_TRACE, 10, L"-> Creation of device failed with hr: %X", hr));
    return E_FAIL;
  }

  hr = CreateD3DDeviceManager(m_pD3DDev, &m_pD3DResetToken, &m_pD3DDevMngr);
  if (FAILED(hr)) {
    DbgLog((LOG_TRACE, 10, L"-> Creation of Device manager failed with hr: %X", hr));
    return E_FAIL;
  }

  hr = SetD3DDeviceManager(m_pD3DDevMngr);
  if (FAILED(hr)) {
    DbgLog((LOG_TRACE, 10, L"-> SetD3DDeviceManager failed with hr: %X", hr));
    return E_FAIL;
  }

  return S_OK;
}