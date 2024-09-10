        std::shared_ptr<GraphicsPipelineState> Device::createGraphicsPipelineState(const GraphicsPipelineStateParams& params)
        {
            ID3D11VertexShader* vertexShader = nullptr;
            if (SUCCEEDED(m_device->CreateVertexShader(params.m_vsParams.m_shaderBytecode, params.m_vsParams.m_bytecodeLength, nullptr, &vertexShader)))
            {
                ID3D11ShaderReflection* vertexShaderReflector = nullptr;
                if (SUCCEEDED(D3DReflect(params.m_vsParams.m_shaderBytecode, params.m_vsParams.m_bytecodeLength, IID_ID3D11ShaderReflection, (void**)&vertexShaderReflector)))
                {
                    ID3D11PixelShader* pixelShader = nullptr;
                    if (SUCCEEDED(m_device->CreatePixelShader(params.m_psParams.m_shaderBytecode, params.m_psParams.m_bytecodeLength, nullptr, &pixelShader)))
                    {
                        ID3D11ShaderReflection* pixelShaderReflector = nullptr;
                        if (SUCCEEDED(D3DReflect(params.m_psParams.m_shaderBytecode, params.m_psParams.m_bytecodeLength, IID_ID3D11ShaderReflection, (void**)&pixelShaderReflector)))
                        {
                            CD3D11_DEPTH_STENCIL_DESC depthStencilDesc(D3D11_DEFAULT);
                            depthStencilDesc.DepthEnable = params.m_depthStencilParams.m_depthEnable;

                            ID3D11DepthStencilState* depthStencilState = nullptr;
                            if (SUCCEEDED(m_device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState)))
                            {
                                D3D11_INPUT_ELEMENT_DESC layout[] =
                                {
                                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                                    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                                };
                                ID3D11InputLayout* inputLayout = nullptr;
                                if (SUCCEEDED(m_device->CreateInputLayout(layout, ARRAYSIZE(layout), params.m_vsParams.m_shaderBytecode, params.m_vsParams.m_bytecodeLength, &inputLayout)))
                                {
                                    return std::make_shared<GraphicsPipelineState>(vertexShader, vertexShaderReflector, pixelShader, pixelShaderReflector, depthStencilState, params.m_stencilRef, inputLayout, params.m_primitiveTopologyType);
                                }
                                depthStencilState->Release();
                            }
                            pixelShaderReflector->Release();
                        }
                        pixelShader->Release();
                    }
                    vertexShaderReflector->Release();
                }
                vertexShader->Release();
            }
            return nullptr;
        }