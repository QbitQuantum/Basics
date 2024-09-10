bool XD3DSwapChainImpl::resize(
    Renderer *renderer,
    ID3D11Device1 *dev,
    IUnknown *window,
    HWND handle,
    xuint32 w,
    xuint32 h,
    int rotation)
  {
  discard();
  if(swapChain != nullptr)
    {
    // If the swap chain already exists, resize it.
    if(failedCheck(swapChain->ResizeBuffers(
           2, // Double-buffered swap chain.
           w,
           h,
           DXGI_FORMAT_B8G8R8A8_UNORM,
           0
           )))
      {
      return false;
      }
    }
  else
    {
    ComPtr<ID3D11Device1> device = dev;
    ComPtr<IDXGIDevice1> dxgiDevice;
    if(failedCheck(device.As(&dxgiDevice)))
      {
      return false;
      }


    ComPtr<IDXGIAdapter> dxgiAdapter;
    if(failedCheck(dxgiDevice->GetAdapter(&dxgiAdapter)))
      {
      return false;
      }

    ComPtr<IDXGIFactory2> dxgiFactory;
    if(failedCheck(dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void **)&dxgiFactory)))
      {
      return false;
      }

    // Otherwise, create a new one using the same adapter as the existing Direct3D device.
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
    swapChainDesc.Width = w; // Match the size of the window.
    swapChainDesc.Height = h;
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // This is the most common swap chain format.
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1; // Don't use multi-sampling.
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2; // Use double-buffering to minimize latency.
    swapChainDesc.Scaling = DXGI_SCALING_NONE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // All Windows Store apps must use this SwapEffect.
    swapChainDesc.Flags = 0;

    if(window)
      {
      if(failedCheck(dxgiFactory->CreateSwapChainForCoreWindow(
                  dev,
                  window,
                  &swapChainDesc,
                  nullptr, // Allow on all displays.
                  &swapChain
                  )))
        {
        return false;
        }
      }
    else if(handle)
      {
      if(failedCheck(dxgiFactory->CreateSwapChainForHwnd(
                     dev,
                     handle,
                     &swapChainDesc,
                     0,
                     0,
                     &swapChain
                     )))
        {
        return false;
        }
      }
    else
      {
      return false;
      }


    // Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
    // ensures that the application will only render after each VSync, minimizing power consumption.
    if(failedCheck(dxgiDevice->SetMaximumFrameLatency(1)))
      {
      return false;
      }
    }

  DXGI_MODE_ROTATION rotationConv = (DXGI_MODE_ROTATION)(rotation + 1);
  if(failedCheck(swapChain->SetRotation(rotationConv)))
    {
    return false;
    }

  if(!XD3DFrameBufferImpl::create(renderer, dev, swapChain.Get()))
    {
    return false;
    }

  return true;
  }