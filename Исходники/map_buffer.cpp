int
main(int argc, char *argv[])
{
    HRESULT hr;

    D3D10_USAGE Usage = D3D10_USAGE_DYNAMIC;
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        if (strcmp(arg, "-dynamic") == 0) {
            Usage = D3D10_USAGE_DYNAMIC;
        } else if (strcmp(arg, "-staging") == 0) {
            Usage = D3D10_USAGE_STAGING;
        } else {
            fprintf(stderr, "error: unknown arg %s\n", arg);
            exit(1);
        }
    }

    com_ptr<IDXGIFactory> pFactory;
    hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
    if (FAILED(hr)) {
        return 1;
    }

    com_ptr<IDXGIAdapter> pAdapter;
    hr = pFactory->EnumAdapters(0, &pAdapter);
    if (FAILED(hr)) {
        return 1;
    }

    UINT Flags = 0;
    if (LoadLibraryA("d3d10sdklayers")) {
        Flags |= D3D10_CREATE_DEVICE_DEBUG;
    }

    com_ptr<ID3D10Device> pDevice;
    hr = D3D10CreateDevice(pAdapter,
                           D3D10_DRIVER_TYPE_HARDWARE,
                           NULL,
                           Flags,
                           D3D10_SDK_VERSION,
                           &pDevice);
    if (FAILED(hr)) {
        return 1;
    }

    UINT NumBuffers = 4;
    UINT NumSegments = 8;
    UINT SegmentSize = 512;

    D3D10_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof BufferDesc);
    BufferDesc.ByteWidth = NumSegments * SegmentSize;
    BufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    BufferDesc.MiscFlags = 0;
    BufferDesc.Usage = Usage;
    if (Usage == D3D10_USAGE_STAGING) {
        BufferDesc.BindFlags = 0;
    } else {
        BufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    }

    D3D10_MAP MapType = D3D10_MAP_WRITE;
    for (UINT i = 0; i < NumBuffers; ++i) {
        com_ptr<ID3D10Buffer> pVertexBuffer;
        hr = pDevice->CreateBuffer(&BufferDesc, NULL, &pVertexBuffer);
        if (FAILED(hr)) {
            return 1;
        }

        if (Usage == D3D10_USAGE_DYNAMIC) {
            MapType = D3D10_MAP_WRITE_DISCARD;
        }

        for (UINT j = 0; j < NumSegments; ++j) {
            BYTE *pMap = NULL;
            hr = pVertexBuffer->Map(MapType, 0, (void **)&pMap);
            if (FAILED(hr)) {
                return 1;
            } 

            int c = (j % 255) + 1;
            memset(pMap + j*SegmentSize, c, SegmentSize);

            pVertexBuffer->Unmap();
            
            if (Usage == D3D10_USAGE_DYNAMIC) {
                MapType = D3D10_MAP_WRITE_NO_OVERWRITE;
            }
        }

        pDevice->Flush();

        D3D10_QUERY_DESC QueryDesc;
        QueryDesc.Query = D3D10_QUERY_EVENT;
        QueryDesc.MiscFlags = 0;
        com_ptr<ID3D10Query> pQuery;
        hr = pDevice->CreateQuery(&QueryDesc, &pQuery);
        if (FAILED(hr)) {
            return 1;
        } 
        
        pQuery->End();

        do {
            hr = pQuery->GetData(NULL, 0, 0);
        } while (hr == S_FALSE);
        if (FAILED(hr)) {
            return 1;
        } 

    }

    return 0;
}