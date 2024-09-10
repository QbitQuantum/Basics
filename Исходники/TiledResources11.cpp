//--------------------------------------------------------------------------------------
// Create any D3D11 resources that depend on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
                                         const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    V_RETURN( g_DialogResourceManager.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );
    V_RETURN( g_SettingsDlg.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );

    FLOAT fAspect = (FLOAT)pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;

    // Setup the camera's projection parameters
    XMMATRIX matProjection = XMMatrixPerspectiveFovLH( XM_PIDIV4, fAspect, 0.001f, 100.0f );
    XMStoreFloat4x4A( &g_matProjection, matProjection );

    g_pTerrainView->GetCamera()->SetProjParams( XM_PIDIV4, fAspect, 0.01f, 1000.0f );

    g_HUD.SetLocation( pBackBufferSurfaceDesc->Width - 170, 0 );
    g_HUD.SetSize( 170, 170 );

    INT UIWidth = 250;
    INT UIHeight = 110;
    g_SampleUI.SetLocation( pBackBufferSurfaceDesc->Width - UIWidth, pBackBufferSurfaceDesc->Height - UIHeight );
    g_SampleUI.SetSize( UIWidth, UIHeight );

    g_HalfClientWidthPixels = (FLOAT)pBackBufferSurfaceDesc->Width * 0.5f;
    g_HalfClientHeightPixels = (FLOAT)pBackBufferSurfaceDesc->Height * 0.5f;

    ResidencySampleRender::ResizeRenderView( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

    return S_OK;
}