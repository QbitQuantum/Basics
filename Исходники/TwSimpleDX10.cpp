// Initialize the 3D objects & effects
HRESULT InitScene()
{
    HRESULT hr = S_OK;

    // Create effect
    DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
    #if defined( DEBUG ) || defined( _DEBUG )
    //  shaderFlags |= D3D10_SHADER_DEBUG;
    #endif

    // DX10 requires shaders (no fixed function anymore). We will read the shaders from the following string.
    char shaderFX[] = " struct PSInput { float4 Pos : SV_POSITION; float4 Col : COLOR0; }; \n"
                      " PSInput VertShad(float4 pos : POSITION, float4 col : COLOR) { \n"
                      "   PSInput ps; ps.Pos=pos; ps.Col=col; return ps; } \n"
                      " float4 PixShad(PSInput input) : SV_Target { return input.Col; } \n"
                      " technique10 Render { pass P0 { \n"
                      "   SetVertexShader( CompileShader( vs_4_0, VertShad() ) ); \n"
                      "   SetGeometryShader( NULL ); \n"
                      "   SetPixelShader( CompileShader( ps_4_0, PixShad() ) ); \n"
                      " } }\n";

    ID3D10Blob *compiledFX = NULL;
    ID3D10Blob *errors = NULL;
    hr = D3D10CompileEffectFromMemory(shaderFX, strlen(shaderFX), "TestDX10", 
                                      NULL, NULL, shaderFlags, 0, &compiledFX, &errors);
    if( FAILED(hr) )
    {
        char *errMsg = static_cast<char *>(errors->GetBufferPointer());
        errMsg[errors->GetBufferSize()-1] = '\0';
        MessageBoxA( NULL, errMsg, "Effect compilation failed", MB_OK|MB_ICONERROR );
        errors->Release();
        return hr;
    }
    hr = D3D10CreateEffectFromMemory(compiledFX->GetBufferPointer(), compiledFX->GetBufferSize(), 
                                     0, g_D3DDevice, NULL, &g_Effect);
    compiledFX->Release();

    if( FAILED( hr ) )
    {
        MessageBox( NULL, L"Effect creation failed", L"Error", MB_OK );
        return hr;
    }

    // Obtain the technique
    g_Technique = g_Effect->GetTechniqueByName("Render");

    // Define the input layout
    D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },  
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 3*sizeof(float), D3D10_INPUT_PER_VERTEX_DATA, 0 }
    };

    // Create the input layout
    D3D10_PASS_DESC passDesc;
    g_Technique->GetPassByIndex(0)->GetDesc(&passDesc);
    hr = g_D3DDevice->CreateInputLayout(layout, sizeof(layout)/sizeof(layout[0]), passDesc.pIAInputSignature,
                                        passDesc.IAInputSignatureSize, &g_VertexLayout);
    if( FAILED( hr ) )
        return hr;
    const int VERTEX_SIZE = (3 + 4)*sizeof(float); // 3 floats for POSITION + 4 floats for COLOR

    // Set the input layout
    g_D3DDevice->IASetInputLayout(g_VertexLayout);

    // Create vertex buffer
    D3D10_BUFFER_DESC bd;
    bd.Usage = D3D10_USAGE_DYNAMIC;
    bd.ByteWidth = VERTEX_SIZE * NB_VERTS;
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;
    hr = g_D3DDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    UINT stride = VERTEX_SIZE;
    UINT offset = 0;
    g_D3DDevice->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

    // Set primitive topology
    g_D3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Blend state
    D3D10_BLEND_DESC bsd;
    bsd.AlphaToCoverageEnable = FALSE;
    for(int i=0; i<8; ++i)
    {
        bsd.BlendEnable[i] = TRUE;
        bsd.RenderTargetWriteMask[i] = D3D10_COLOR_WRITE_ENABLE_ALL;
    }
    bsd.SrcBlend = D3D10_BLEND_SRC_ALPHA;
    bsd.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
    bsd.BlendOp =  D3D10_BLEND_OP_ADD;
    bsd.SrcBlendAlpha = D3D10_BLEND_SRC_ALPHA;
    bsd.DestBlendAlpha = D3D10_BLEND_INV_SRC_ALPHA;
    bsd.BlendOpAlpha = D3D10_BLEND_OP_ADD;
    g_D3DDevice->CreateBlendState(&bsd, &g_BlendState);
    float blendFactors[4] = { 1, 1, 1, 1 };
    g_D3DDevice->OMSetBlendState(g_BlendState, blendFactors, 0xffffffff);

    // Rasterizer state
    D3D10_RASTERIZER_DESC rs;
    ZeroMemory(&rs, sizeof(rs));
    rs.FillMode = D3D10_FILL_SOLID;
    rs.CullMode = D3D10_CULL_NONE;
    g_D3DDevice->CreateRasterizerState(&rs, &g_RasterState);
    g_D3DDevice->RSSetState(g_RasterState);

    return S_OK;
}