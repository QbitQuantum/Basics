//--------------------------------------------------------------------------------------
// Name: Render()
// Desc: Renders the gamepad help image and its labelled callouts
//--------------------------------------------------------------------------------------
VOID Help::Render( Font* pFont, const HELP_CALLOUT* pTags, DWORD dwNumCallouts )
{
#ifdef ALLOW_CALLOUT_EDITTING
    // Use the shoulder buttons, triggers, and dpad to edit callout positions
    XINPUT_STATE CurrInputState;
    static XINPUT_STATE LastInputState = {0};
    static DWORD dwCurrCallout = 0;

    if( XInputGetState( 0, &CurrInputState ) == ERROR_SUCCESS )
    {
        if( ( 0 != (CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_LEFT_SHOULDER) ) &&
            ( 0 == (LastInputState.Gamepad.wButtons&XINPUT_GAMEPAD_LEFT_SHOULDER) ) )
            dwCurrCallout = (dwCurrCallout+dwNumCallouts-1) % dwNumCallouts;
        if( ( 0 != (CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER) ) &&
            ( 0 == (LastInputState.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER) ) )
            dwCurrCallout = (dwCurrCallout+dwNumCallouts+1) % dwNumCallouts;

        HELP_CALLOUT_POS* pCallout = &g_pHelpCallouts[pTags[dwCurrCallout].wControl];
        XMFLOAT2* pPos1 = &pCallout->Button;
        XMFLOAT2* pPos2 = &pCallout->Placement[pTags[dwCurrCallout].wPlacement].Line;
        XMFLOAT2* pPos3 = &pCallout->Placement[pTags[dwCurrCallout].wPlacement].Text;

        if( CurrInputState.Gamepad.bLeftTrigger )
        {
            pPos1->x -= CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT  ? 1.0f : 0.0f;
            pPos1->x += CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT ? 1.0f : 0.0f;
            pPos1->y -= CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP    ? 1.0f : 0.0f;
            pPos1->y += CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN  ? 1.0f : 0.0f;
        }
        else if( CurrInputState.Gamepad.bRightTrigger )
        {
            pPos2->x -= CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT  ? 1.0f : 0.0f;
            pPos2->x += CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT ? 1.0f : 0.0f;
            pPos2->y -= CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP    ? 1.0f : 0.0f;
            pPos2->y += CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN  ? 1.0f : 0.0f;
            pPos3->x -= CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT  ? 1.0f : 0.0f;
            pPos3->x += CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT ? 1.0f : 0.0f;
            pPos3->y -= CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_UP    ? 1.0f : 0.0f;
            pPos3->y += CurrInputState.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_DOWN  ? 1.0f : 0.0f;
        }

        memcpy( &LastInputState, &CurrInputState, sizeof(XINPUT_STATE) );
    }
#endif // ALLOW_CALLOUT_EDITTING

    // Calculate a scale factor based on the video mode
    D3DDISPLAYMODE ModeDesc;
    XGTEXTURE_DESC TextureDesc;
    g_pd3dDevice->GetDisplayMode( 0, &ModeDesc );
    XGGetTextureDesc( m_pGamepadTexture, 0, &TextureDesc );

    FLOAT fScale = ModeDesc.Width / 1280.0f;
    FLOAT h = fScale * 720 * 0.48f;
    FLOAT w = TextureDesc.Width * h / TextureDesc.Height;
    FLOAT x = ( ModeDesc.Width - w ) / 2;
    FLOAT y = ( ModeDesc.Height - h ) / 2;

    D3DRECT rcSaved = pFont->m_rcWindow;
    pFont->SetWindow( 0, 0, ModeDesc.Width, ModeDesc.Height );

    // Setup the gamepad vertices
    struct VERTEX
    {
        FLOAT sx, sy;
        FLOAT tu, tv;
    };

    // Set up state for rendering the gamepad
    g_pd3dDevice->SetVertexDeclaration( g_pHelpVertexDecl );
    g_pd3dDevice->SetVertexShader( g_pHelpVertexShader );
    g_pd3dDevice->SetTexture( 0, m_pGamepadTexture );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
    g_pd3dDevice->SetRenderState( D3DRS_VIEWPORTENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
    g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    g_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );

    // Draw the scene-darkening quad
    {
        VERTEX GamepadVertices[4] =
        {
            {                0.0f,                 0.0f, 0.0f, 0.0f },
            { 1.0f * ModeDesc.Width,                 0.0f, 1.0f, 0.0f },
            { 1.0f * ModeDesc.Width, 1.0f * ModeDesc.Height, 1.0f, 1.0f },
            {                0.0f, 1.0f * ModeDesc.Height, 0.0f, 1.0f },
        };

        g_pd3dDevice->SetPixelShader( g_pDarkPixelShader );
        g_pd3dDevice->DrawPrimitiveUP( D3DPT_QUADLIST, 1, GamepadVertices, sizeof( GamepadVertices[0] ) );
    }

    // Draw the gamepad image
    {
        VERTEX GamepadVertices[4] =
        {
            { x,   y,   0.0f, 0.0f },
            { x + w, y,   1.0f, 0.0f },
            { x + w, y + h, 1.0f, 1.0f },
            { x,   y + h, 0.0f, 1.0f },
        };

        g_pd3dDevice->SetPixelShader( g_pHelpPixelShader );
        g_pd3dDevice->DrawPrimitiveUP( D3DPT_QUADLIST, 1, GamepadVertices, sizeof( GamepadVertices[0] ) );
    }

    // Set state to draw the lines
    g_pd3dDevice->SetTexture( 0, m_pLineTexture );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

    for( DWORD i = 0; i < dwNumCallouts; i++ )
    {
        if( pTags[i].wControl >= ARRAYSIZE( g_vHelpCallouts ) )
            continue;

        HELP_CALLOUT_POS* pCallout = &g_pHelpCallouts[pTags[i].wControl];
        XMFLOAT2 line1 = pCallout->Button;
        XMFLOAT2 line2 = pCallout->Placement[pTags[i].wPlacement].Line;
        line1.x = fScale * ( line1.x - 640 ) + ModeDesc.Width / 2;
        line1.y = fScale * ( line1.y - 360 ) + ModeDesc.Height / 2;
        line2.x = fScale * ( line2.x - 640 ) + ModeDesc.Width / 2;
        line2.y = fScale * ( line2.y - 360 ) + ModeDesc.Height / 2;
        XMVECTOR vc = XMVector2Normalize( XMVectorSet( line2.y - line1.y, -line2.x + line1.x, 0, 0 ) );

#ifdef ALLOW_CALLOUT_EDITTING
        if( dwCurrCallout == i )
            vc *= 2;
#endif // ALLOW_CALLOUT_EDITTING

        // Initialize the callout line vertices
        VERTEX LineVertices[4] =
        {
            { ( line1.x - 2 * vc.x ), ( line1.y - 2 * vc.y ), 0.0f, 0.0f },
            { ( line1.x + 2 * vc.x ), ( line1.y + 2 * vc.y ), 1.0f, 0.0f },
            { ( line2.x + 2 * vc.x ), ( line2.y + 2 * vc.y ), 1.0f, 1.0f },
            { ( line2.x - 2 * vc.x ), ( line2.y - 2 * vc.y ), 0.0f, 1.0f },
        };

        g_pd3dDevice->DrawPrimitiveUP( D3DPT_QUADLIST, 1, LineVertices, sizeof( LineVertices[0] ) );
    }

    // Turn the viewport back on
    g_pd3dDevice->SetRenderState( D3DRS_VIEWPORTENABLE, TRUE );

    // Prepare font for rendering
    pFont->Begin();
    static FLOAT fFontXScale = 1.0f;
    static FLOAT fFontYScale = 1.0f;
    pFont->SetScaleFactors( fFontXScale * fScale, fFontYScale * fScale );

    // Render the callouts
    for( DWORD i = 0; i < dwNumCallouts; i++ )
    {
        if( pTags[i].wControl >= ARRAYSIZE( g_vHelpCallouts ) )
            continue;

        HELP_CALLOUT_POS* pCallout = &g_pHelpCallouts[pTags[i].wControl];
        XMFLOAT2 pos = pCallout->Placement[pTags[i].wPlacement].Text;
        pos.x = fScale * ( pos.x - 640 ) + ModeDesc.Width / 2;
        pos.y = fScale * ( pos.y - 360 ) + ModeDesc.Height / 2;

        // Draw the callout text
        pFont->DrawText( pos.x, pos.y, 0xffffffff,
                         pTags[i].strText, g_pHelpCallouts[pTags[i].wControl].dwFontFlags );
    }

    // Flush the text drawing
    pFont->SetScaleFactors( 1.0f, 1.0f );
    pFont->End();

    pFont->m_rcWindow = rcSaved;
}