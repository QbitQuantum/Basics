void ntGenerateTextures(const ShaderScripts& shaderScript, 
                        nlEngineContext* cxt )
{
#if 0
    /* この関数が呼ばれる前にテクスチャは解放されている事が期待される */
    for( int i=0;i<MAX_TEXTURE_NUM;++i){ NL_ASSERT( !cxt->texs[i].texture );}
    const ShaderScriptGroup& tsScripts = shaderScript.tsScripts;
    const ShaderScript& commonScrips = shaderScript.commonScripts;
    /**/
    NL_ASSERT( 0 < tsScripts.numScript );
    /**/
    ID3D11Device* d3dDevice = cxt->d3dDevice;
    ID3D11DeviceContext* d3dContext = cxt->d3dContext;

    tsScripts.numScript;
    tsScripts.scripts[0].script;
    tsScripts.scripts[0].name;

    //const nlInt8* script = tsScripts.scripts;
    nlTexture* texuters = &(cxt->texs[0]);
    /**/
    const unsigned int scriptLen = nlStrlen(script);
    /* 全シェーダを作成 */
    ID3D11PixelShader* texturShaders[MAX_TEXTURE_NUM];
    nlMemset( texturShaders, 0, sizeof(ID3D11PixelShader*)*MAX_TEXTURE_NUM );
    /**/
    const unsigned int numTexture = textureScripts.numTexture;
    /**/
    for( unsigned int i=0;i<numTexture;++i)
    {
        ID3DBlob* pBlob = NULL;
        ID3DBlob* pErrorBlob = NULL;
        const nlInt8* funcName = textureScripts.funcs[i];
        const DWORD flag = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_ROW_MAJOR;
        /* ピクセルシェーダの作成 */
        if( FAILED(
            D3D10CompileShader(
            script, scriptLen, funcName, shaderMacros, NULL, 
           "main", "ps_4_0",flag, &pBlob, &pErrorBlob ) ) )
        {
            NL_ERR(ERR_009);
            MessageBoxA( NULL, "load texshader error", "", MB_OK );
            if(pErrorBlob)
            {
                NL_ERR(ERR_003, pErrorBlob->GetBufferPointer() );
                MessageBoxA( NULL, (nlInt8*)pErrorBlob->GetBufferPointer(), "", MB_OK );
            }
            return;
        }
        if( pBlob )
        {
            d3dDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &texturShaders[i] );
        }
        ++i;
    }

    /* 書きこむのに必要なシェーダを作成 */
    ID3D11VertexShader* vsRenderQuad;
    ID3DBlob* pBlob = NULL;
    ID3DBlob* pErrorBlob = NULL;    

    NL_HR_ASSSERT( D3D10CompileShader(script, scriptLen, "vs", shaderMacros, NULL, 
        "main","vs_4_0",(D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_ROW_MAJOR),
        &pBlob, &pErrorBlob ) ) ;
    d3dDevice->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &vsRenderQuad );

    /* 全テクスチャを作成 */
    for(unsigned int i=0;i<numTexture;++i)
    {
        /**/
        nlTexture& tex = texuters[i];
        /**/
        tex.width  = 512; /* HACK サイズは適当 */
        tex.height = 512; /* HACK サイズは適当 */
        int mipLevel = 1;
        int CPUAccessFlags = 0;
        D3D11_TEXTURE2D_DESC descTarget = 
        {
            tex.width, tex.height,
            mipLevel, 1,
            DXGI_FORMAT_B8G8R8A8_UNORM,
            {1,0}, D3D11_USAGE_DEFAULT,
            (D3D11_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE),
            CPUAccessFlags, 0
        };
        d3dDevice->CreateTexture2D( &descTarget, NULL, &tex.texture );
        d3dDevice->CreateRenderTargetView( tex.texture, NULL, &tex.rtView );
        d3dDevice->CreateShaderResourceView( tex.texture, NULL ,&tex.shaderView );
    }

    /* 現在のRasterStateを取得 */
    ID3D11RasterizerState* oldRasterState;
    d3dContext->RSGetState(&oldRasterState);
    /**/
    D3D11_RASTERIZER_DESC rasterDesc;
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_NONE;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;
    ID3D11RasterizerState* rasterState;
    d3dDevice->CreateRasterizerState(&rasterDesc, &rasterState);
    d3dContext->RSSetState(rasterState);
    rasterState->Release();

    /* 全テクスチャを焼き込む */
    for(unsigned int i=0;i<numTexture;++i)
    {
        /**/
        nlTexture& tex = texuters[i];
        /* ビューポートの設定 */
        D3D11_VIEWPORT viewport;
        viewport.Width = tex.width;
        viewport.Height = tex.height;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        d3dContext->RSSetViewports(1, &viewport);
        /* シェーダを設定する */
        d3dContext->VSSetShader( vsRenderQuad, NULL, 0);
        d3dContext->PSSetShader( texturShaders[i], NULL, 0);
        /* レンダーターゲットを設定する */
        const float clearColor[4] = {0.0f, 0.0f, 1.0f, 0.0f};
        d3dContext->ClearRenderTargetView( tex.rtView, clearColor );
        d3dContext->OMSetRenderTargets( 1, &tex.rtView, NULL );

        /* 全てのテクスチャを設定する */
        /* TODO 毎回全てのテクスチャを設定せずに、このループで設定したテクスチャを省くようにだけする？*/
        for( unsigned int j=0;j<numTexture;++j)
        {
            if( i != j )
            {
                nlTexture& texSamp = texuters[j];
                d3dContext->PSSetShaderResources(j, 1, &texSamp.shaderView );
            }
        }

        /* 描画する */
        d3dContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
        d3dContext->Draw( 4, 0 );
    }
    /**/
    d3dContext->VSSetShader( NULL, NULL, 0);
    d3dContext->PSSetShader( NULL, NULL, 0);

    /* ビューポート設定を元に戻す */
    /* 現在のビューポート設定を取得しておく */
    D3D11_VIEWPORT oldViewports = {0.0,0.0,cxt->rendertargets[0].width_,cxt->rendertargets[0].height_,0.0f,1.0f};
    d3dContext->RSSetViewports( 1, &oldViewports );

    /* RasterState設定を元に戻す */
    d3dContext->RSSetState(oldRasterState);
    if( oldRasterState ){ oldRasterState->Release(); }

    /* PSを解放 */
    for(unsigned int i=0;i<numTexture;++i)
    {
        if( texturShaders[i] ){ texturShaders[i]->Release(); }
    }
#endif
}