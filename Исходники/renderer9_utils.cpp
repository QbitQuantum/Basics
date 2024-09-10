void GenerateCaps(IDirect3D9 *d3d9,
                  IDirect3DDevice9 *device,
                  D3DDEVTYPE deviceType,
                  UINT adapter,
                  gl::Caps *caps,
                  gl::TextureCapsMap *textureCapsMap,
                  gl::Extensions *extensions,
                  gl::Limitations *limitations)
{
    D3DCAPS9 deviceCaps;
    if (FAILED(d3d9->GetDeviceCaps(adapter, deviceType, &deviceCaps)))
    {
        // Can't continue with out device caps
        return;
    }

    D3DDISPLAYMODE currentDisplayMode;
    d3d9->GetAdapterDisplayMode(adapter, &currentDisplayMode);

    GLuint maxSamples = 0;
    for (GLenum internalFormat : gl::GetAllSizedInternalFormats())
    {
        gl::TextureCaps textureCaps = GenerateTextureFormatCaps(internalFormat, d3d9, deviceType,
                                                                adapter, currentDisplayMode.Format);
        textureCapsMap->insert(internalFormat, textureCaps);

        maxSamples = std::max(maxSamples, textureCaps.getMaxSamples());

        if (gl::GetSizedInternalFormatInfo(internalFormat).compressed)
        {
            caps->compressedTextureFormats.push_back(internalFormat);
        }
    }

    // GL core feature limits
    caps->maxElementIndex = static_cast<GLint64>(std::numeric_limits<unsigned int>::max());

    // 3D textures are unimplemented in D3D9
    caps->max3DTextureSize = 1;

    // Only one limit in GL, use the minimum dimension
    caps->max2DTextureSize = std::min(deviceCaps.MaxTextureWidth, deviceCaps.MaxTextureHeight);

    // D3D treats cube maps as a special case of 2D textures
    caps->maxCubeMapTextureSize = caps->max2DTextureSize;

    // Array textures are not available in D3D9
    caps->maxArrayTextureLayers = 1;

    // ES3-only feature
    caps->maxLODBias = 0.0f;

    // No specific limits on render target size, maximum 2D texture size is equivalent
    caps->maxRenderbufferSize = caps->max2DTextureSize;

    // Draw buffers are not supported in D3D9
    caps->maxDrawBuffers      = 1;
    caps->maxColorAttachments = 1;

    // No specific limits on viewport size, maximum 2D texture size is equivalent
    caps->maxViewportWidth  = caps->max2DTextureSize;
    caps->maxViewportHeight = caps->maxViewportWidth;

    // Point size is clamped to 1.0f when the shader model is less than 3
    caps->minAliasedPointSize = 1.0f;
    caps->maxAliasedPointSize =
        ((D3DSHADER_VERSION_MAJOR(deviceCaps.PixelShaderVersion) >= 3) ? deviceCaps.MaxPointSize
                                                                       : 1.0f);

    // Wide lines not supported
    caps->minAliasedLineWidth = 1.0f;
    caps->maxAliasedLineWidth = 1.0f;

    // Primitive count limits (unused in ES2)
    caps->maxElementsIndices  = 0;
    caps->maxElementsVertices = 0;

    // Program and shader binary formats (no supported shader binary formats)
    caps->programBinaryFormats.push_back(GL_PROGRAM_BINARY_ANGLE);

    caps->vertexHighpFloat.setIEEEFloat();
    caps->vertexMediumpFloat.setIEEEFloat();
    caps->vertexLowpFloat.setIEEEFloat();
    caps->fragmentHighpFloat.setIEEEFloat();
    caps->fragmentMediumpFloat.setIEEEFloat();
    caps->fragmentLowpFloat.setIEEEFloat();

    // Some (most) hardware only supports single-precision floating-point numbers,
    // which can accurately represent integers up to +/-16777216
    caps->vertexHighpInt.setSimulatedInt(24);
    caps->vertexMediumpInt.setSimulatedInt(24);
    caps->vertexLowpInt.setSimulatedInt(24);
    caps->fragmentHighpInt.setSimulatedInt(24);
    caps->fragmentMediumpInt.setSimulatedInt(24);
    caps->fragmentLowpInt.setSimulatedInt(24);

    // WaitSync is ES3-only, set to zero
    caps->maxServerWaitTimeout = 0;

    // Vertex shader limits
    caps->maxVertexAttributes = 16;
    // Vertex Attrib Binding not supported.
    caps->maxVertexAttribBindings = caps->maxVertexAttributes;

    const size_t MAX_VERTEX_CONSTANT_VECTORS_D3D9 = 256;
    caps->maxVertexUniformVectors =
        MAX_VERTEX_CONSTANT_VECTORS_D3D9 - GetReservedVertexUniformVectors();
    caps->maxShaderUniformComponents[gl::ShaderType::Vertex] = caps->maxVertexUniformVectors * 4;

    caps->maxShaderUniformBlocks[gl::ShaderType::Vertex] = 0;

    // SM3 only supports 12 output variables, but the special 12th register is only for PSIZE.
    const unsigned int MAX_VERTEX_OUTPUT_VECTORS_SM3 = 12 - GetReservedVaryingVectors();
    const unsigned int MAX_VERTEX_OUTPUT_VECTORS_SM2 = 10 - GetReservedVaryingVectors();
    caps->maxVertexOutputComponents =
        ((deviceCaps.VertexShaderVersion >= D3DVS_VERSION(3, 0)) ? MAX_VERTEX_OUTPUT_VECTORS_SM3
                                                                 : MAX_VERTEX_OUTPUT_VECTORS_SM2) *
        4;

    // Only Direct3D 10 ready devices support all the necessary vertex texture formats.
    // We test this using D3D9 by checking support for the R16F format.
    if (deviceCaps.VertexShaderVersion >= D3DVS_VERSION(3, 0) &&
        SUCCEEDED(d3d9->CheckDeviceFormat(adapter, deviceType, currentDisplayMode.Format,
                                          D3DUSAGE_QUERY_VERTEXTEXTURE, D3DRTYPE_TEXTURE,
                                          D3DFMT_R16F)))
    {
        const size_t MAX_TEXTURE_IMAGE_UNITS_VTF_SM3             = 4;
        caps->maxShaderTextureImageUnits[gl::ShaderType::Vertex] = MAX_TEXTURE_IMAGE_UNITS_VTF_SM3;
    }
    else
    {
        caps->maxShaderTextureImageUnits[gl::ShaderType::Vertex] = 0;
    }

    // Fragment shader limits
    const size_t MAX_PIXEL_CONSTANT_VECTORS_SM3 = 224;
    const size_t MAX_PIXEL_CONSTANT_VECTORS_SM2 = 32;
    caps->maxFragmentUniformVectors =
        ((deviceCaps.PixelShaderVersion >= D3DPS_VERSION(3, 0)) ? MAX_PIXEL_CONSTANT_VECTORS_SM3
                                                                : MAX_PIXEL_CONSTANT_VECTORS_SM2) -
        GetReservedFragmentUniformVectors();
    caps->maxShaderUniformComponents[gl::ShaderType::Fragment] =
        caps->maxFragmentUniformVectors * 4;
    caps->maxShaderUniformBlocks[gl::ShaderType::Fragment]     = 0;
    caps->maxFragmentInputComponents                           = caps->maxVertexOutputComponents;
    caps->maxShaderTextureImageUnits[gl::ShaderType::Fragment] = 16;
    caps->minProgramTexelOffset                                = 0;
    caps->maxProgramTexelOffset                                = 0;

    // Aggregate shader limits (unused in ES2)
    caps->maxUniformBufferBindings                                     = 0;
    caps->maxUniformBlockSize                                          = 0;
    caps->uniformBufferOffsetAlignment                                 = 0;
    caps->maxCombinedUniformBlocks                                     = 0;
    caps->maxCombinedShaderUniformComponents[gl::ShaderType::Vertex]   = 0;
    caps->maxCombinedShaderUniformComponents[gl::ShaderType::Fragment] = 0;
    caps->maxVaryingComponents                                         = 0;

    // Aggregate shader limits
    caps->maxVaryingVectors            = caps->maxVertexOutputComponents / 4;
    caps->maxCombinedTextureImageUnits = caps->maxShaderTextureImageUnits[gl::ShaderType::Vertex] +
                                         caps->maxShaderTextureImageUnits[gl::ShaderType::Fragment];

    // Transform feedback limits
    caps->maxTransformFeedbackInterleavedComponents = 0;
    caps->maxTransformFeedbackSeparateAttributes    = 0;
    caps->maxTransformFeedbackSeparateComponents    = 0;

    // Multisample limits
    caps->maxSamples = maxSamples;

    // GL extension support
    extensions->setTextureExtensionSupport(*textureCapsMap);
    extensions->elementIndexUint  = deviceCaps.MaxVertexIndex >= (1 << 16);
    extensions->getProgramBinary  = true;
    extensions->rgb8rgba8         = true;
    extensions->readFormatBGRA    = true;
    extensions->pixelBufferObject = false;
    extensions->mapBuffer         = false;
    extensions->mapBufferRange    = false;

    // textureRG is emulated and not performant.
    extensions->textureRG = false;

    D3DADAPTER_IDENTIFIER9 adapterId = {};
    if (SUCCEEDED(d3d9->GetAdapterIdentifier(adapter, 0, &adapterId)))
    {
        // ATI cards on XP have problems with non-power-of-two textures.
        extensions->textureNPOT = !(deviceCaps.TextureCaps & D3DPTEXTURECAPS_POW2) &&
                                  !(deviceCaps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP_POW2) &&
                                  !(deviceCaps.TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL) &&
                                  !(!isWindowsVistaOrGreater() && IsAMD(adapterId.VendorId));

        // Disable depth texture support on AMD cards (See ANGLE issue 839)
        if (IsAMD(adapterId.VendorId))
        {
            extensions->depthTextures = false;
        }
    }
    else
    {
        extensions->textureNPOT = false;
    }

    extensions->drawBuffers    = false;
    extensions->textureStorage = true;

    // Must support a minimum of 2:1 anisotropy for max anisotropy to be considered supported, per
    // the spec
    extensions->textureFilterAnisotropic =
        (deviceCaps.RasterCaps & D3DPRASTERCAPS_ANISOTROPY) != 0 && deviceCaps.MaxAnisotropy >= 2;
    extensions->maxTextureAnisotropy = static_cast<GLfloat>(deviceCaps.MaxAnisotropy);

    // Check occlusion query support by trying to create one
    IDirect3DQuery9 *occlusionQuery = nullptr;
    extensions->occlusionQueryBoolean =
        SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &occlusionQuery)) && occlusionQuery;
    SafeRelease(occlusionQuery);

    // Check event query support by trying to create one
    IDirect3DQuery9 *eventQuery = nullptr;
    extensions->fence =
        SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_EVENT, &eventQuery)) && eventQuery;
    SafeRelease(eventQuery);

    extensions->disjointTimerQuery = false;
    extensions->robustness         = true;
    // It seems that only DirectX 10 and higher enforce the well-defined behavior of always
    // returning zero values when out-of-bounds reads. See
    // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_robustness.txt
    extensions->robustBufferAccessBehavior = false;
    extensions->blendMinMax                = true;
    extensions->framebufferBlit            = true;
    extensions->framebufferMultisample     = true;
    extensions->instancedArrays            = deviceCaps.PixelShaderVersion >= D3DPS_VERSION(3, 0);
    extensions->packReverseRowOrder        = true;
    extensions->standardDerivatives =
        (deviceCaps.PS20Caps.Caps & D3DPS20CAPS_GRADIENTINSTRUCTIONS) != 0;
    extensions->shaderTextureLOD       = true;
    extensions->fragDepth              = true;
    extensions->textureUsage           = true;
    extensions->translatedShaderSource = true;
    extensions->fboRenderMipmap        = false;
    extensions->discardFramebuffer     = false;  // It would be valid to set this to true, since
                                                 // glDiscardFramebufferEXT is just a hint
    extensions->colorBufferFloat   = false;
    extensions->debugMarker        = true;
    extensions->eglImage           = true;
    extensions->eglImageExternal   = true;
    extensions->unpackSubimage     = true;
    extensions->packSubimage       = true;
    extensions->syncQuery          = extensions->fence;
    extensions->copyTexture        = true;
    extensions->textureBorderClamp = true;

    // D3D9 has no concept of separate masks and refs for front and back faces in the depth stencil
    // state.
    limitations->noSeparateStencilRefsAndMasks = true;

    // D3D9 shader models have limited support for looping, so the Appendix A
    // index/loop limitations are necessary. Workarounds that are needed to
    // support dynamic indexing of vectors on HLSL also don't work on D3D9.
    limitations->shadersRequireIndexedLoopValidation = true;

    // D3D9 cannot support constant color and alpha blend funcs together
    limitations->noSimultaneousConstantColorAndAlphaBlendFunc = true;

    // D3D9 cannot support packing more than one variable to a single varying.
    // TODO(jmadill): Implement more sophisticated component packing in D3D9.
    limitations->noFlexibleVaryingPacking = true;
}