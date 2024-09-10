void _stdcall ProxyDevice::SetGammaRamp(DWORD a, const D3DGAMMARAMP *b)
{
    IDirect3DSwapChain9 *sc;
    D3DPRESENT_PARAMETERS pp;

    realDevice->GetSwapChain(0, &sc);
    sc->GetPresentParameters(&pp);
    sc->Release();

    if(pp.Windowed)
        SetDeviceGammaRamp(GetDC(pp.hDeviceWindow), (void*)b);
    else
        realDevice->SetGammaRamp(0, a, b);
}