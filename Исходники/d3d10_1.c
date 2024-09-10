static void test_create_device(void)
{
    D3D10_FEATURE_LEVEL1 feature_level, supported_feature_level;
    DXGI_SWAP_CHAIN_DESC swapchain_desc, obtained_desc;
    IDXGISwapChain *swapchain;
    ID3D10Device1 *device;
    unsigned int i;
    ULONG refcount;
    HWND window;
    HRESULT hr;

    for (i = 0; i < sizeof(d3d10_feature_levels) / sizeof(*d3d10_feature_levels); ++i)
    {
        if (SUCCEEDED(hr = D3D10CreateDevice1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
                d3d10_feature_levels[i], D3D10_1_SDK_VERSION, &device)))
        {
            supported_feature_level = d3d10_feature_levels[i];
            break;
        }
    }

    if (FAILED(hr))
    {
        skip("Failed to create HAL device.\n");
        return;
    }

    feature_level = ID3D10Device1_GetFeatureLevel(device);
    ok(feature_level == supported_feature_level, "Got feature level %#x, expected %#x.\n",
            feature_level, supported_feature_level);

    ID3D10Device1_Release(device);

    hr = D3D10CreateDevice1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, NULL);
    ok(hr == E_INVALIDARG, "Got unexpected hr %#x.\n", hr);

    device = (ID3D10Device1 *)0xdeadbeef;
    hr = D3D10CreateDevice1(NULL, 0xffffffff, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &device);
    todo_wine ok(hr == E_INVALIDARG, "D3D10CreateDevice1 returned %#x.\n", hr);
    ok(!device, "Got unexpected device pointer %p.\n", device);

    device = (ID3D10Device1 *)0xdeadbeef;
    hr = D3D10CreateDevice1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            0, D3D10_1_SDK_VERSION, &device);
    ok(hr == E_INVALIDARG, "D3D10CreateDevice1 returned %#x.\n", hr);
    ok(!device, "Got unexpected device pointer %p.\n", device);

    window = CreateWindowA("static", "d3d10_1_test", 0, 0, 0, 0, 0, 0, 0, 0, 0);

    swapchain_desc.BufferDesc.Width = 800;
    swapchain_desc.BufferDesc.Height = 600;
    swapchain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swapchain_desc.BufferDesc.RefreshRate.Denominator = 60;
    swapchain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapchain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapchain_desc.SampleDesc.Count = 1;
    swapchain_desc.SampleDesc.Quality = 0;
    swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchain_desc.BufferCount = 1;
    swapchain_desc.OutputWindow = window;
    swapchain_desc.Windowed = TRUE;
    swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapchain_desc.Flags = 0;

    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &swapchain_desc, &swapchain, &device);
    ok(SUCCEEDED(hr), "D3D10CreateDeviceAndSwapChain1 failed %#x.\n", hr);

    memset(&obtained_desc, 0, sizeof(obtained_desc));
    hr = IDXGISwapChain_GetDesc(swapchain, &obtained_desc);
    ok(SUCCEEDED(hr), "GetDesc failed %#x.\n", hr);
    ok(obtained_desc.BufferDesc.Width == swapchain_desc.BufferDesc.Width,
            "Got unexpected BufferDesc.Width %u.\n", obtained_desc.BufferDesc.Width);
    ok(obtained_desc.BufferDesc.Height == swapchain_desc.BufferDesc.Height,
            "Got unexpected BufferDesc.Height %u.\n", obtained_desc.BufferDesc.Height);
    todo_wine ok(obtained_desc.BufferDesc.RefreshRate.Numerator == swapchain_desc.BufferDesc.RefreshRate.Numerator,
            "Got unexpected BufferDesc.RefreshRate.Numerator %u.\n",
            obtained_desc.BufferDesc.RefreshRate.Numerator);
    todo_wine ok(obtained_desc.BufferDesc.RefreshRate.Denominator == swapchain_desc.BufferDesc.RefreshRate.Denominator,
            "Got unexpected BufferDesc.RefreshRate.Denominator %u.\n",
            obtained_desc.BufferDesc.RefreshRate.Denominator);
    ok(obtained_desc.BufferDesc.Format == swapchain_desc.BufferDesc.Format,
            "Got unexpected BufferDesc.Format %#x.\n", obtained_desc.BufferDesc.Format);
    ok(obtained_desc.BufferDesc.ScanlineOrdering == swapchain_desc.BufferDesc.ScanlineOrdering,
            "Got unexpected BufferDesc.ScanlineOrdering %#x.\n", obtained_desc.BufferDesc.ScanlineOrdering);
    ok(obtained_desc.BufferDesc.Scaling == swapchain_desc.BufferDesc.Scaling,
            "Got unexpected BufferDesc.Scaling %#x.\n", obtained_desc.BufferDesc.Scaling);
    ok(obtained_desc.SampleDesc.Count == swapchain_desc.SampleDesc.Count,
            "Got unexpected SampleDesc.Count %u.\n", obtained_desc.SampleDesc.Count);
    ok(obtained_desc.SampleDesc.Quality == swapchain_desc.SampleDesc.Quality,
            "Got unexpected SampleDesc.Quality %u.\n", obtained_desc.SampleDesc.Quality);
    todo_wine ok(obtained_desc.BufferUsage == swapchain_desc.BufferUsage,
            "Got unexpected BufferUsage %#x.\n", obtained_desc.BufferUsage);
    ok(obtained_desc.BufferCount == swapchain_desc.BufferCount,
            "Got unexpected BufferCount %u.\n", obtained_desc.BufferCount);
    ok(obtained_desc.OutputWindow == swapchain_desc.OutputWindow,
            "Got unexpected OutputWindow %p.\n", obtained_desc.OutputWindow);
    ok(obtained_desc.Windowed == swapchain_desc.Windowed,
            "Got unexpected Windowed %#x.\n", obtained_desc.Windowed);
    ok(obtained_desc.SwapEffect == swapchain_desc.SwapEffect,
            "Got unexpected SwapEffect %#x.\n", obtained_desc.SwapEffect);
    ok(obtained_desc.Flags == swapchain_desc.Flags,
            "Got unexpected Flags %#x.\n", obtained_desc.Flags);

    refcount = IDXGISwapChain_Release(swapchain);
    ok(!refcount, "Swapchain has %u references left.\n", refcount);

    feature_level = ID3D10Device1_GetFeatureLevel(device);
    ok(feature_level == supported_feature_level, "Got feature level %#x, expected %#x.\n",
            feature_level, supported_feature_level);

    refcount = ID3D10Device1_Release(device);
    ok(!refcount, "Device has %u references left.\n", refcount);

    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, NULL, NULL, &device);
    ok(SUCCEEDED(hr), "D3D10CreateDeviceAndSwapChain1 failed %#x.\n", hr);
    refcount = ID3D10Device1_Release(device);
    ok(!refcount, "Device has %u references left.\n", refcount);

    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Got unexpected hr %#x.\n", hr);

    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &swapchain_desc, NULL, NULL);
    ok(hr == E_INVALIDARG, "Got unexpected hr %#x.\n", hr);

    swapchain = (IDXGISwapChain *)0xdeadbeef;
    device = (ID3D10Device1 *)0xdeadbeef;
    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            0, D3D10_1_SDK_VERSION, &swapchain_desc, &swapchain, &device);
    ok(hr == E_INVALIDARG, "Got unexpected hr %#x.\n", hr);
    ok(!swapchain, "Got unexpected swapchain pointer %p.\n", swapchain);
    ok(!device, "Got unexpected device pointer %p.\n", device);

    swapchain = (IDXGISwapChain *)0xdeadbeef;
    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &swapchain_desc, &swapchain, NULL);
    ok(hr == E_INVALIDARG, "Got unexpected hr %#x.\n", hr);
    ok(!swapchain, "Got unexpected swapchain pointer %p.\n", swapchain);

    swapchain_desc.OutputWindow = NULL;
    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &swapchain_desc, NULL, &device);
    ok(SUCCEEDED(hr), "D3D10CreateDeviceAndSwapChain1 failed %#x.\n", hr);
    refcount = ID3D10Device1_Release(device);
    ok(!refcount, "Device has %u references left.\n", refcount);

    swapchain = (IDXGISwapChain *)0xdeadbeef;
    device = (ID3D10Device1 *)0xdeadbeef;
    swapchain_desc.OutputWindow = NULL;
    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &swapchain_desc, &swapchain, &device);
    todo_wine ok(hr == DXGI_ERROR_INVALID_CALL, "D3D10CreateDeviceAndSwapChain1 returned %#x.\n", hr);
    if (SUCCEEDED(hr))
    {
        refcount = IDXGISwapChain_Release(swapchain);
        ok(!refcount, "Swapchain has %u references left.\n", refcount);
        refcount = ID3D10Device1_Release(device);
        ok(!refcount, "Device has %u references left.\n", refcount);
    }
    else
    {
        ok(!swapchain, "Got unexpected swapchain pointer %p.\n", swapchain);
        ok(!device, "Got unexpected device pointer %p.\n", device);
    }

    swapchain = (IDXGISwapChain *)0xdeadbeef;
    device = (ID3D10Device1 *)0xdeadbeef;
    swapchain_desc.OutputWindow = window;
    swapchain_desc.BufferDesc.Format = DXGI_FORMAT_BC5_UNORM;
    hr = D3D10CreateDeviceAndSwapChain1(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
            supported_feature_level, D3D10_1_SDK_VERSION, &swapchain_desc, &swapchain, &device);
    ok(hr == E_INVALIDARG, "D3D10CreateDeviceAndSwapChain1 returned %#x.\n", hr);
    ok(!swapchain, "Got unexpected swapchain pointer %p.\n", swapchain);
    ok(!device, "Got unexpected device pointer %p.\n", device);

    DestroyWindow(window);
}