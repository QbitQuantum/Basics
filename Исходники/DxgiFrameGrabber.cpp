void D3D11Grab(ID3D11Texture2D *pBackBuffer) {
    D3D11_TEXTURE2D_DESC tex_desc;
    pBackBuffer->GetDesc(&tex_desc);

    ID3D11Device *pDev;
    pBackBuffer->GetDevice(&pDev);
    ID3D11DeviceContext * pDevContext;
    pDev->GetImmediateContext(&pDevContext);

    ID3D11Texture2D * pTexture;
    D3D11_MAPPED_SUBRESOURCE mappedTexture;
    tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.ArraySize = 1;
    tex_desc.MipLevels = 1;
    tex_desc.BindFlags = 0;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.Usage = D3D11_USAGE_STAGING;
    tex_desc.MiscFlags = 0;

    HRESULT hr = pDev->CreateTexture2D(&tex_desc, NULL, &pTexture);
//    reportLog(EVENTLOG_INFORMATION_TYPE, L"d3d11 pDev->CreateTexture2D 0x%x", hr);

    pDevContext->CopyResource(pTexture, pBackBuffer);
    D3D11_BOX box = {0, 0, tex_desc.Width, tex_desc.Height, 0, 1};
    pDevContext->CopySubresourceRegion(pTexture, 0, 0, 0, 0, pBackBuffer, 0, &box);

    DxgiFrameGrabber *dxgiFrameGrabber = DxgiFrameGrabber::getInstance();
    IPCContext *ipcContext = dxgiFrameGrabber->m_ipcContext;
    Logger *logger = dxgiFrameGrabber->m_logger;

    //        __asm__("int $3");
    if (S_OK != (hr = pDevContext->Map(pTexture, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &mappedTexture))) {
        logger->reportLogError(L"d3d11 couldn't map texture, hresult = 0x%x", hr);
        goto end;
    }

    ipcContext->m_memDesc.width = tex_desc.Width;
    ipcContext->m_memDesc.height = tex_desc.Height;
    ipcContext->m_memDesc.rowPitch = mappedTexture.RowPitch;
    ipcContext->m_memDesc.frameId++;

//    reportLog(EVENTLOG_INFORMATION_TYPE, L"d3d11 texture description. width: %u, height: %u, pitch: %u", tex_desc.Width, tex_desc.Height, mappedTexture.RowPitch);

    DWORD errorcode;
    if (WAIT_OBJECT_0 == (errorcode = WaitForSingleObject(ipcContext->m_hMutex, 0))) {
        //            __asm__("int $3");
//        reportLog(EVENTLOG_INFORMATION_TYPE, L"d3d11 writing description to mem mapped file");
        memcpy(ipcContext->m_pMemMap, &ipcContext->m_memDesc, sizeof (ipcContext->m_memDesc));
//        reportLog(EVENTLOG_INFORMATION_TYPE, L"d3d11 writing data to mem mapped file");
        PVOID pMemDataMap = incPtr(ipcContext->m_pMemMap, sizeof (ipcContext->m_memDesc));
        if (mappedTexture.RowPitch == tex_desc.Width * 4) {
            memcpy(pMemDataMap, mappedTexture.pData, tex_desc.Width * tex_desc.Height * 4);
        } else {
            UINT i = 0, cleanOffset = 0, pitchOffset = 0;
            while (i < tex_desc.Height) {
                memcpy(incPtr(pMemDataMap, cleanOffset), incPtr(mappedTexture.pData, pitchOffset), tex_desc.Width * 4);
                cleanOffset += tex_desc.Width * 4;
                pitchOffset += mappedTexture.RowPitch;
                i++;
            }
        }
        ReleaseMutex(ipcContext->m_hMutex);
        SetEvent(ipcContext->m_hFrameGrabbedEvent);
    } else {
        logger->reportLogError(L"d3d11 couldn't wait mutex. errocode = 0x%x", errorcode);
    }

    pDevContext->Unmap(pTexture, D3D10CalcSubresource(0, 0, 1));
end:
    pTexture->Release();
    pDevContext->Release();
    pDev->Release();
}