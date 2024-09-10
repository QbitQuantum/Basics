//D3D10CreateDeviceAndSwapChain
extern "C" _declspec(dllexport) HRESULT WINAPI newD3D10CreateDeviceAndSwapChain(IDXGIAdapter *adapter,
                                                                                D3D10_DRIVER_TYPE DriverType,
                                                                                HMODULE Software,
                                                                                UINT Flags,
                                                                                UINT SDKVersion,
                                                                                DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
                                                                                IDXGISwapChain **ppSwapChain,
                                                                                ID3D10Device **ppDevice)
{
  dbg("d3d10: D3D10CreateDeviceAndSwapChain 0x%08X 0x%08X", adapter, *adapter);

  /*dbg("Mode: %dx%d %d.%dHz %s", pSwapChainDesc->BufferDesc.Width, pSwapChainDesc->BufferDesc.Height, pSwapChainDesc->BufferDesc.RefreshRate.Numerator, pSwapChainDesc->BufferDesc.RefreshRate.Denominator, pSwapChainDesc->Windowed?"Windowed":"Fullscreen");
  dbg("Multisample: %d samples, quality %d", pSwapChainDesc->SampleDesc.Count, pSwapChainDesc->SampleDesc.Quality);
  dbg("Buffers: %d (Usage %s), Swapeffect: %s", pSwapChainDesc->BufferCount, getUsageDXGI(pSwapChainDesc->BufferUsage), pSwapChainDesc->SwapEffect==DXGI_SWAP_EFFECT_DISCARD?"DISCARD":"SEQUENTIAL");

  dbg("Flags: %s %s %s", pSwapChainDesc->Flags&DXGI_SWAP_CHAIN_FLAG_NONPREROTATED?"NONPREROTATED":"",
                         pSwapChainDesc->Flags&DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH?"ALLOW_MODE_SWITCH":"",
                         pSwapChainDesc->Flags&DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE?"GDI_COMPATIBLE":"");*/

  HRESULT ret;

  /*ret = D3D10CreateDevice(adapter,
                          D3D10_DRIVER_TYPE_HARDWARE,
                          NULL,
                          0,
                          D3D10_SDK_VERSION,
                          ppDevice
                          );*/

  ret = D3D10CreateDevice(adapter,
                          DriverType,
                          Software,
                          Flags,
                          SDKVersion,
                          ppDevice
                          );

  /*IDXGIAdapter1New *anew;
  if(adapter->QueryInterface(IID_IDXGIAdapter, (void**) &anew) == S_OK) {
    adapter = anew->getReal();
    anew->Release();
  }*/

  IDXGIFactory1 *factory;
  //IDXGIFactory1New *fnew;
  //CreateDXGIFactory1()
  if(adapter->GetParent(IID_IDXGIFactory, (void**) &factory) == S_OK)
  {
    //factory = fnew->getReal();
    //fnew->Release();
    dbg("d3d10: Got parent factory");
  }

  //ret =  dllD3D10CreateDeviceAndSwapChain(anew, DriverType, Software, Flags, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice);

  (*ppSwapChain) = new IDXGISwapChainNew(factory, factory, *ppDevice, pSwapChainDesc);

  /*IDXGISwapChainNew *scnew;
  if((*ppSwapChain)->QueryInterface(IID_IDXGISwapChainNew, (void**) &scnew) == S_OK) {
    (*ppSwapChain) = scnew->getReal();
    scnew->Release();
  } else dbg("Booh! No real swap chain!");*/

  /*if(fnew)
  {
    fnew->Release();
    delete fnew;
    fnew = NULL;
  }*/

  return ret;
}