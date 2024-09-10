//--------------------------------------------------------------------------------------
// Render the scene using the D3D10 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D10FrameRender( ID3D10Device* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f }; // R, G, B, A
    ID3D10RenderTargetView* pRTV = DXUTGetD3D10RenderTargetView();
    pd3dDevice->ClearRenderTargetView( pRTV, ClearColor );
    ID3D10DepthStencilView* pDSV = DXUTGetD3D10DepthStencilView();
    pd3dDevice->ClearDepthStencilView( pDSV, D3D10_CLEAR_DEPTH, 1.0, 0 );

    // If the settings dialog is being shown, then render it instead of rendering the app's scene
    if( g_D3DSettingsDlg.IsActive() )
    {
        g_D3DSettingsDlg.OnRender( fElapsedTime );
        return;
    }

    // Set our render target since we can't present multisampled ref
    ID3D10RenderTargetView* pOrigRT;
    ID3D10DepthStencilView* pOrigDS;
    pd3dDevice->OMGetRenderTargets( 1, &pOrigRT, &pOrigDS );
    ID3D10RenderTargetView* aRTViews[ 1 ] = { g_pRTRV };
    pd3dDevice->OMSetRenderTargets( 1, aRTViews, g_pDSRV );

    pd3dDevice->ClearRenderTargetView( g_pRTRV, ClearColor );
    pd3dDevice->ClearDepthStencilView( g_pDSRV, D3D10_CLEAR_DEPTH, 1.0, 0 );

    // Set Matrices
    D3DXMATRIX mWorldViewProj;
    D3DXMATRIX mWorldView;
    D3DXMATRIX mViewProj;
    D3DXMATRIX mWorld;
    D3DXMATRIX mView;
    D3DXMATRIX mProj;

    // Fix the camera motion for now
    D3DXMATRIX mBlurViewProj[MAX_TIME_STEPS];
    for( int i = 0; i < MAX_TIME_STEPS; i++ )
    {
        mView = *g_Camera.GetViewMatrix();
        mProj = *g_Camera.GetProjMatrix();
        mBlurViewProj[i] = mView * mProj;
    }
    g_pmBlurViewProj->SetMatrixArray( ( float* )mBlurViewProj, 0, MAX_TIME_STEPS );

    D3DXMatrixIdentity( &mWorld );
    mView = *g_Camera.GetViewMatrix();
    mProj = *g_Camera.GetProjMatrix();
    mViewProj = mView * mProj;
    mWorldViewProj = mWorld * mViewProj;
    mWorldView = mWorld * mView;

    g_pmWorldViewProj->SetMatrix( ( float* )&mWorldViewProj );
    g_pmViewProj->SetMatrix( ( float* )&mViewProj );
    g_pmWorldView->SetMatrix( ( float* )&mWorldView );

    RenderSceneMesh( pd3dDevice, &g_SceneMesh, false );
    RenderFanMesh( pd3dDevice, &g_FanMesh, fTime, false );
    if( g_bRenderOgre )
        RenderSkinnedMesh( pd3dDevice, &g_AnimMesh, fTime, false );

    for( UINT iMesh = 0; iMesh < g_NumLinkedMeshes; iMesh++ )
        RenderLinkedMesh( pd3dDevice, &g_pLinkedMeshes[iMesh], &g_AnimMesh, g_MeshLinkages[iMesh].iBone, fTime,
                          false );

    if( g_bUseMotionBlur )
    {
        RenderFanMesh( pd3dDevice, &g_FanMesh, fTime, true );
        if( g_bRenderOgre )
            RenderSkinnedMesh( pd3dDevice, &g_AnimMesh, fTime, true );

        for( UINT iMesh = 0; iMesh < g_NumLinkedMeshes; iMesh++ )
            RenderLinkedMesh( pd3dDevice, &g_pLinkedMeshes[iMesh], &g_AnimMesh, g_MeshLinkages[iMesh].iBone, fTime,
                              true );
    }

    //MSAA resolve
    ID3D10Resource* pRT;
    pOrigRT->GetResource( &pRT );
    D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
    pOrigRT->GetDesc( &rtDesc );
    pd3dDevice->ResolveSubresource( pRT, D3D10CalcSubresource( 0, 0, 1 ), g_pRenderTarget, D3D10CalcSubresource( 0, 0,
                                                                                                                 1 ),
                                    rtDesc.Format );
    SAFE_RELEASE( pRT );

    // Use our Old RT again
    aRTViews[0] = pOrigRT;
    pd3dDevice->OMSetRenderTargets( 1, aRTViews, pOrigDS );
    SAFE_RELEASE( pOrigRT );
    SAFE_RELEASE( pOrigDS );

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" );
    RenderText();
    g_HUD.OnRender( fElapsedTime );
    g_SampleUI.OnRender( fElapsedTime );
    DXUT_EndPerfEvent();
}