DX12Device::DX12Device(bool debug)
{
  // Debug layer
  if (debug)
  {
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
      debugController->EnableDebugLayer();
    }
  }

  ComPtr<IDXGIFactory4> factory;
  if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
  {
    WindowManager::Message("DX12 Initialization Error", "Failed to create the factory");
  }

  // no warp device
  if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
  {
    WindowManager::Message("DX12 Initialization Error", "Failed to create the device");
  }

  // the command queue should have it's own class
  // Describe and create the command queue.
  D3D12_COMMAND_QUEUE_DESC queueDesc = {};
  queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

  if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue))))
  {
    WindowManager::Message("DX12 Initialization Error", "Failed to create the command queue");
  }

  // Describe and create the swap chain.
  DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
  swapChainDesc.BufferCount = FrameCount;
  swapChainDesc.BufferDesc.Width = WindowManager::GetWidth();
  swapChainDesc.BufferDesc.Height = WindowManager::GetHeight();
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  swapChainDesc.OutputWindow = WindowManager::GetHandle();
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.Windowed = TRUE;

  ComPtr<IDXGISwapChain> swapChain;
  if (FAILED(factory->CreateSwapChain(
    m_commandQueue.Get(),		// Swap chain needs the queue so that it can force a flush on it.
    &swapChainDesc,
    &swapChain
    )))
  {
    WindowManager::Message("DX12 Initialization Error", "Failed to create the swap chain");
  }

  swapChain.As(&m_swapChain);

  m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

  // Create descriptor heaps.
  {
    // Describe and create a render target view (RTV) descriptor heap.
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FrameCount;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap));

    m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  }

  // Create frame resources.
  {
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

    // Create a RTV for each frame.
    for (UINT n = 0; n < FrameCount; n++)
    {
      m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n]));
      m_device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
      rtvHandle.Offset(1, m_rtvDescriptorSize);
    }
  }

  m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));

  // Create the command list.
  if (FAILED(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_commandList))))
  {
    WindowManager::Message("DX12 Initialization Error", "Failed to create the command lsit");
  }

  // Command lists are created in the recording state, but there is nothing
  // to record yet. The main loop expects it to be closed, so close it now.
  if(FAILED(m_commandList->Close()))
  {
    WindowManager::Message("DX12 Initialization Error", "Failed to close the command lsit");
  }

  // Create synchronization objects.
  {
    if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))
    {
      WindowManager::Message("DX12 Initialization Error", "Failed to create fence");
    }

    m_fenceValue = 1;

    // Create an event handle to use for frame synchronization.
    m_fenceEvent = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);
    if (m_fenceEvent == nullptr)
    {
      if (FAILED(HRESULT_FROM_WIN32(GetLastError())))
      {
        WindowManager::Message("DX12 Initialization Error", "GENERIC ERROR");
      }
    }
  }

  /*
  // Command list allocators can only be reset when the associated 
  // command lists have finished execution on the GPU; apps should use 
  // fences to determine GPU execution progress.
  (m_commandAllocator->Reset());

  // However, when ExecuteCommandList() is called on a particular command 
  // list, that command list can then be reset at any time and must be before 
  // re-recording.
  (m_commandList->Reset(m_commandAllocator.Get(), m_pipelineState.Get()));

  // Indicate that the back buffer will be used as a render target.
  m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);

  // Record commands.
  const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
  m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

  // Indicate that the back buffer will now be used to present.
  m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

  (m_commandList->Close());*/
}