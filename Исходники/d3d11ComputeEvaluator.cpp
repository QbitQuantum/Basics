bool
D3D11ComputeEvaluator::Compile(BufferDescriptor const &srcDesc,
                               BufferDescriptor const &dstDesc,
                               ID3D11DeviceContext *deviceContext) {

    if (srcDesc.length > dstDesc.length) {
        Far::Error(Far::FAR_RUNTIME_ERROR,
                   "srcDesc length must be less than or equal to "
                   "dstDesc length.\n");
        return false;
    }

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(D3D10_SHADER_RESOURCES_MAY_ALIAS)
     dwShaderFlags |= D3D10_SHADER_RESOURCES_MAY_ALIAS;
#endif

#ifdef _DEBUG
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    std::ostringstream ss;
    ss << srcDesc.length;  std::string lengthValue(ss.str()); ss.str("");
    ss << srcDesc.stride;  std::string srcStrideValue(ss.str()); ss.str("");
    ss << dstDesc.stride;  std::string dstStrideValue(ss.str()); ss.str("");
    ss << _workGroupSize;  std::string workgroupSizeValue(ss.str()); ss.str("");

    D3D_SHADER_MACRO defines[] =
        { "LENGTH", lengthValue.c_str(),
          "SRC_STRIDE", srcStrideValue.c_str(),
          "DST_STRIDE", dstStrideValue.c_str(),
          "WORK_GROUP_SIZE", workgroupSizeValue.c_str(),
          0, 0 };

    ID3DBlob * computeShaderBuffer = NULL;
    ID3DBlob * errorBuffer = NULL;

    HRESULT hr = D3DCompile(shaderSource, strlen(shaderSource),
                            NULL, &defines[0], NULL,
                            "cs_main", "cs_5_0",
                            dwShaderFlags, 0,
                            &computeShaderBuffer, &errorBuffer);
    if (FAILED(hr)) {
        if (errorBuffer != NULL) {
            Far::Error(Far::FAR_RUNTIME_ERROR,
                       "Error compiling HLSL shader: %s\n",
                       (CHAR*)errorBuffer->GetBufferPointer());
            errorBuffer->Release();
            return false;
        }
    }

    ID3D11Device *device = NULL;
    deviceContext->GetDevice(&device);
    assert(device);

    device->CreateClassLinkage(&_classLinkage);
    assert(_classLinkage);

    device->CreateComputeShader(computeShaderBuffer->GetBufferPointer(),
                                computeShaderBuffer->GetBufferSize(),
                                _classLinkage,
                                &_computeShader);
    assert(_computeShader);

    ID3D11ShaderReflection *reflector;
    D3DReflect(computeShaderBuffer->GetBufferPointer(),
               computeShaderBuffer->GetBufferSize(),
               IID_ID3D11ShaderReflection, (void**) &reflector);
    assert(reflector);

    assert(reflector->GetNumInterfaceSlots() == 1);
    reflector->Release();

    computeShaderBuffer->Release();

    _classLinkage->GetClassInstance("singleBufferCompute", 0, &_singleBufferKernel);
    assert(_singleBufferKernel);
    _classLinkage->GetClassInstance("separateBufferCompute", 0, &_separateBufferKernel);
    assert(_separateBufferKernel);

    D3D11_BUFFER_DESC cbDesc;
    ZeroMemory(&cbDesc, sizeof(cbDesc));
    cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbDesc.MiscFlags = 0;
    cbDesc.ByteWidth = sizeof(KernelUniformArgs);
    device->CreateBuffer(&cbDesc, NULL, &_uniformArgs);

    return true;
}