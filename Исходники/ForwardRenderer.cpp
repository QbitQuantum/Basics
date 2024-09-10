void ForwardRenderer::DrawScene()
{
    DrawShadowMap();

    RendererCore::Instance()->SetOriginalRenderTargetDepth();

    float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // Set constants
    XMMATRIX view = XMLoadFloat4x4( RendererCore::Instance()->GetView() );
    XMMATRIX proj = XMLoadFloat4x4( RendererCore::Instance()->GetProj() );

    XMMATRIX shadowTransform = XMLoadFloat4x4( &m_ShadowTransform );


    int iCount = m_vDrawElements.size();
    for ( int i = 0; i < iCount; ++i )
    {
        DrawElement* pElem = m_vDrawElements[i];
        if ( !pElem )
            continue;

        UINT stride = pElem->stride;
        UINT offset = pElem->offset;

        GetD3D11DeviceImmContext()->IASetInputLayout( pElem->m_pInputLayout );
        GetD3D11DeviceImmContext()->IASetPrimitiveTopology( pElem->ePrimitiveTopology );

        pElem->m_spShader->SetDirLight( m_DirLights[0] );
        pElem->m_spShader->SetDirLights( m_DirLights );
        pElem->m_spShader->SetPointLight( m_PointLight );
        pElem->m_spShader->SetSpotLight( m_SpotLight );
        pElem->m_spShader->SetEyePosW( RendererCore::Instance()->GetEyePosW() );
        pElem->m_spShader->SetFogStart( 15.0f );
        pElem->m_spShader->SetFogRange( 300.0f );
        pElem->m_spShader->SetFogColor( Colors::Silver );

        for ( auto itor = pElem->m_vecSubElement.begin(); itor != pElem->m_vecSubElement.end() ; ++itor )
        {
            ID3DX11EffectTechnique* pTech = pElem->m_spShader->GetTech( (*itor).m_iTechIndex );
            if ( !pTech )
                continue;


            ID3D11Buffer* pVB = pElem->m_spVB->GetVB();
            GetD3D11DeviceImmContext()->IASetVertexBuffers( 0, 1, &pVB, &stride, &offset );

            if ( pElem->m_spIB )
                GetD3D11DeviceImmContext()->IASetIndexBuffer( pElem->m_spIB->GetIB(), DXGI_FORMAT_R32_UINT, 0 );

            if ( pElem->m_pRasterS )
                GetD3D11DeviceImmContext()->RSSetState( pElem->m_pRasterS );
            if ( pElem->m_pBlendS )
                GetD3D11DeviceImmContext()->OMSetBlendState( pElem->m_pBlendS, blendFactor, 0xffffffff );
            if ( pElem->m_pDepthStencilS )
                GetD3D11DeviceImmContext()->OMSetDepthStencilState( pElem->m_pDepthStencilS, pElem->m_uiStencilRef );

            XMMATRIX world;
            XMFLOAT3 oldLightDirections;
            if ( pElem->m_bStencilReflect )
            {
                XMVECTOR mirrorPlane = XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f ); // xy plane
                XMMATRIX R = XMMatrixReflect( mirrorPlane );
                world = XMLoadFloat4x4( &pElem->m_vecSubElement[0].m_World ) * R;

                oldLightDirections = m_DirLights[0].Direction;

                XMVECTOR lightDir = XMLoadFloat3( &m_DirLights[0].Direction );
                XMVECTOR reflectedLightDir = XMVector3TransformNormal( lightDir, R );
                XMStoreFloat3( &m_DirLights[0].Direction, reflectedLightDir );

                //ÀÓ½Ã¹æÆí
                pElem->m_spShader->SetDirLight( m_DirLights[0] );
            }
            else if ( pElem->m_bShadowmap )
            {
                XMVECTOR shadowPlane = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ); // xz plane
                XMVECTOR toMainLight = -XMLoadFloat3( &m_DirLights[0].Direction );
                XMMATRIX S = XMMatrixShadow( shadowPlane, toMainLight );
                XMMATRIX shadowOffsetY = XMMatrixTranslation( 0.0f, 0.001f, 0.0f );

                world = XMLoadFloat4x4( &pElem->m_vecSubElement[0].m_World )*S*shadowOffsetY;
            }
            else
            {
                world = XMLoadFloat4x4( &pElem->m_vecSubElement[0].m_World );
            }

            TexturePtr spDiffuseMap = (*itor).m_spDiffuseMap;
            TexturePtr spCubeMap = (*itor).m_spCubeMap;
            TexturePtr spNormalMap = (*itor).m_spNormalMap;
            TexturePtr spShadowMap = (*itor).m_spShadowMap;

            world = XMLoadFloat4x4( &(*itor).m_World );

            XMMATRIX worldInvTranspose = MathHelper::InverseTranspose( world );
            XMMATRIX viewProj = view*proj;
            XMMATRIX worldViewProj = world*view*proj;

            XMMATRIX texTransform = XMLoadFloat4x4( &(*itor).m_TexTransform );

            D3DX11_TECHNIQUE_DESC techDesc;
            pTech->GetDesc( &techDesc );

            for ( UINT p = 0; p < techDesc.Passes; ++p )
            {

                pElem->m_spShader->SetWorld( world );
                pElem->m_spShader->SetWorldViewProj( worldViewProj );
                pElem->m_spShader->SetViewProj( viewProj );
                pElem->m_spShader->SetWorldInvTranspose( worldInvTranspose );
                pElem->m_spShader->SetTexTransform( texTransform );
                pElem->m_spShader->SetShadowTransform( world*shadowTransform );
                pElem->m_spShader->SetMaterial( (*itor).m_mat );

                if ( spDiffuseMap )
                {
                    if ( !spDiffuseMap->IsArray() )
                        pElem->m_spShader->SetDiffuseMap( spDiffuseMap->GetSRV() );
                    else
                        pElem->m_spShader->SetDiffuseMapArray( spDiffuseMap->GetSRV() );
                }

                if ( spCubeMap )
                {
                    pElem->m_spShader->SetCubeMap( spCubeMap->GetSRV() );
                }

                if ( spNormalMap )
                {
                    pElem->m_spShader->SetNormalMap( spNormalMap->GetSRV() );
                }

                if ( spShadowMap )
                {
                    pElem->m_spShader->SetShadowMap( spShadowMap->GetSRV() );
                }

                pTech->GetPassByIndex( p )->Apply( 0, GetD3D11DeviceImmContext() );

                if ( pElem->m_bDrawIndex )
                {

                    GetD3D11DeviceImmContext()->DrawIndexed( (*itor).m_IndexCount, (*itor).m_StartIndexLocation, (*itor).m_BaseVertexLocation );
                }
                else
                {
                    GetD3D11DeviceImmContext()->Draw( (*itor).m_VertexCount, (*itor).m_StartVertexLocation );
                }
            }


            if ( pElem->m_bStencilReflect )
            {
                m_DirLights[0].Direction = oldLightDirections;
            }
        }
    }

    DrawScreenQuad();
}