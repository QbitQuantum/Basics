static bool setup_dxgi(IDXGISwapChain *swap)
{
    const char *process_name = get_process_name();
    bool ignore_d3d10 = false;
    IUnknown *device;
    HRESULT hr;

    /* Call of duty ghosts allows the context to be queried as a d3d10
     * context when it's actually a d3d11 context.  Why this is I don't
     * quite know. */
    if (_strcmpi(process_name, "iw6sp64_ship.exe") == 0 ||
            _strcmpi(process_name, "iw6mp64_ship.exe") == 0 ||
            _strcmpi(process_name, "justcause3.exe") == 0) {
        ignore_d3d10 = true;
    }

    if (!ignore_d3d10) {
        hr = swap->GetDevice(__uuidof(ID3D10Device), (void**)&device);
        if (SUCCEEDED(hr)) {
            data.swap = swap;
            data.capture = d3d10_capture;
            data.free = d3d10_free;
            device->Release();
            return true;
        }
    }

    hr = swap->GetDevice(__uuidof(ID3D11Device), (void**)&device);
    if (SUCCEEDED(hr)) {
        data.swap = swap;
        data.capture = d3d11_capture;
        data.free = d3d11_free;
        device->Release();
        return true;
    }

#if COMPILE_D3D12_HOOK
    hr = swap->GetDevice(__uuidof(ID3D12Device), (void**)&device);
    if (SUCCEEDED(hr)) {
        data.swap = swap;
        data.capture = d3d12_capture;
        data.free = d3d12_free;
        device->Release();
        return true;
    }
#endif

    return false;
}