/// @copydoc ResourceHandler::CacheResource()
bool MaterialResourceHandler::CacheResource(
    AssetPreprocessor* pAssetPreprocessor,
    Resource* pResource,
    const String& /*rSourceFilePath*/ )
{
    HELIUM_ASSERT( pAssetPreprocessor );
    HELIUM_ASSERT( pResource );

    Material* pMaterial = Reflect::AssertCast< Material >( pResource );
    Shader* pShader = pMaterial->GetShader();
    bool failedToWriteASubdata = false;
    
    StrongPtr< Material::PersistentResourceData > resource_data( new Material::PersistentResourceData() );

    // Compute the shader variant indices from the user options selected in the material, as the array of indices in
    // the material is not yet initialized.
    //uint32_t shaderVariantIndices[ RShader::TYPE_MAX ];
    if( pShader )
    {
        const Shader::Options& rShaderUserOptions = pShader->GetUserOptions();
        const DynamicArray< Shader::SelectPair >& rMaterialUserOptions = pMaterial->GetUserOptions();

        for( size_t shaderTypeIndex = 0; shaderTypeIndex < RShader::TYPE_MAX; ++shaderTypeIndex )
        {
            size_t optionSetIndex = rShaderUserOptions.GetOptionSetIndex(
                static_cast< RShader::EType >( shaderTypeIndex ),
                rMaterialUserOptions.GetData(),
                rMaterialUserOptions.GetSize() );
            resource_data->m_shaderVariantIndices[ shaderTypeIndex ] = static_cast< uint32_t >( optionSetIndex );
        }
    }
    else
    {
        MemoryZero( resource_data->m_shaderVariantIndices, sizeof( resource_data->m_shaderVariantIndices ) );
    }

    size_t float1ParameterCount = pMaterial->GetFloat1ParameterCount();
    size_t float2ParameterCount = pMaterial->GetFloat2ParameterCount();
    size_t float3ParameterCount = pMaterial->GetFloat3ParameterCount();
    size_t float4ParameterCount = pMaterial->GetFloat4ParameterCount();

    Name parameterConstantBufferName = Material::GetParameterConstantBufferName();
    
    for( size_t platformIndex = 0; platformIndex < static_cast< size_t >( Cache::PLATFORM_MAX ); ++platformIndex )
    {
        PlatformPreprocessor* pPreprocessor = pAssetPreprocessor->GetPlatformPreprocessor(
            static_cast< Cache::EPlatform >( platformIndex ) );

        if( !pPreprocessor )
        {
            continue;
        }

        Resource::PreprocessedData& rPreprocessedData = pResource->GetPreprocessedData(
            static_cast< Cache::EPlatform >( platformIndex ) );
        SaveObjectToPersistentDataBuffer(resource_data.Get(), rPreprocessedData.persistentDataBuffer);
        rPreprocessedData.bLoaded = true;

        // Write out the parameter constant buffer data as the resource sub-data.
        size_t shaderProfileCount = pPreprocessor->GetShaderProfileCount();

        DynamicArray< DynamicArray< uint8_t > >& rSubDataBuffers = rPreprocessedData.subDataBuffers;
        rSubDataBuffers.Clear();
        rSubDataBuffers.Reserve( shaderProfileCount * RShader::TYPE_MAX );
        rSubDataBuffers.Resize( shaderProfileCount * RShader::TYPE_MAX );

        if( pShader )
        {
    //        deserializer.SetByteSwapping( bSwapBytes );

            for( size_t shaderTypeIndex = 0; shaderTypeIndex < RShader::TYPE_MAX; ++shaderTypeIndex )
            {
                RShader::EType shaderType = static_cast< RShader::EType >( shaderTypeIndex );
                size_t variantLoadId = pShader->BeginLoadVariant(
                    shaderType,
                    resource_data->m_shaderVariantIndices[ shaderTypeIndex ] );
                if( IsInvalid( variantLoadId ) )
                {
                    continue;
                }

                ShaderVariantPtr spVariant;
                while( !pShader->TryFinishLoadVariant( variantLoadId, spVariant ) )
                {
                }

                ShaderVariant* pVariant = spVariant;
                if( !pVariant )
                {
                    continue;
                }

                const Resource::PreprocessedData& rVariantData = pVariant->GetPreprocessedData(
                    static_cast< Cache::EPlatform >( platformIndex ) );
                HELIUM_ASSERT( rVariantData.bLoaded );

                const DynamicArray< DynamicArray< uint8_t > >& rVariantSubDataBuffers = rVariantData.subDataBuffers;
                size_t variantSubDataCount = rVariantSubDataBuffers.GetSize();
                HELIUM_ASSERT( variantSubDataCount != 0 );
                HELIUM_ASSERT( variantSubDataCount % shaderProfileCount == 0 );
                size_t systemOptionSetCount = variantSubDataCount / shaderProfileCount;

                for( size_t profileIndex = 0; profileIndex < shaderProfileCount; ++profileIndex )
                {
                    // Get the first option set of each profile
                    const DynamicArray< uint8_t >& rVariantSubData =
                        rVariantSubDataBuffers[ profileIndex * systemOptionSetCount ];

                    Reflect::ObjectPtr variantSubDataObjectPtr = 
                        Cache::ReadCacheObjectFromBuffer(rVariantSubData);

                    if (!variantSubDataObjectPtr.ReferencesObject())
                    {
                        HELIUM_TRACE(
                            TraceLevels::Error,
                            "MaterialResourceHandler: A shader variant subdata could not be read. (Option Set: %d Profile: %d)",
                            0,
                            profileIndex );

                        failedToWriteASubdata = true;
                    }
                    else if (!variantSubDataObjectPtr->IsA(Reflect::GetMetaClass<CompiledShaderData>()))
                    {
                        HELIUM_TRACE(
                            TraceLevels::Error,
                            "MaterialResourceHandler: A shader variant subdata was of an unexpected type. (Option Set: %d Profile: %d)\n",
                            0,
                            profileIndex );

                        failedToWriteASubdata = true;

                    }
                    else
                    {
                        CompiledShaderData &csd = *Reflect::AssertCast<CompiledShaderData>(variantSubDataObjectPtr.Get());
                        

                        size_t bufferCount = csd.constantBuffers.GetSize();
                        for( size_t bufferIndex = 0; bufferIndex < bufferCount; ++bufferIndex )
                        {
                            const ShaderConstantBufferInfo& rBufferInfo = csd.constantBuffers[ bufferIndex ];
                            if( rBufferInfo.name != parameterConstantBufferName )
                            {
                                continue;
                            }

                            size_t bufferSize = rBufferInfo.size;

                            DynamicArray< uint8_t >& rMaterialSubData =
                                rSubDataBuffers[ profileIndex * RShader::TYPE_MAX + shaderTypeIndex ];
                            rMaterialSubData.Clear();
                            rMaterialSubData.Reserve( bufferSize );
                            rMaterialSubData.Add( 0, bufferSize );

                            DynamicMemoryStream memoryStream( &rMaterialSubData );
                            ByteSwappingStream byteSwapStream( &memoryStream );
                            Stream& rOutputStream = memoryStream;
                            //Stream& rOutputStream =
                            //    ( bSwapBytes
                            //    ? static_cast< Stream& >( byteSwapStream )
                            //    : static_cast< Stream& >( memoryStream ) );

                            const DynamicArray< ShaderConstantInfo >& rConstants = rBufferInfo.constants;
                            size_t constantCount = rConstants.GetSize();
                            for( size_t constantIndex = 0; constantIndex < constantCount; ++constantIndex )
                            {
                                const ShaderConstantInfo& rConstantInfo = rConstants[ constantIndex ];
                                Name constantName = rConstantInfo.name;

                                size_t parameterIndex;
                                for( parameterIndex = 0; parameterIndex < float1ParameterCount; ++parameterIndex )
                                {
                                    const Material::Float1Parameter& rParameter = pMaterial->GetFloat1Parameter(
                                        parameterIndex );
                                    if( rParameter.name == constantName )
                                    {
                                        rOutputStream.Seek( rConstantInfo.offset, SeekOrigins::Begin );
                                        rOutputStream.Write(
                                            &rParameter.value,
                                            sizeof( float32_t ),
                                            Min< size_t >( 1, rConstantInfo.size / sizeof( float32_t ) ) );

                                        break;
                                    }
                                }

                                if( parameterIndex >= float1ParameterCount )
                                {
                                    for( parameterIndex = 0; parameterIndex < float2ParameterCount; ++parameterIndex )
                                    {
                                        const Material::Float2Parameter& rParameter = pMaterial->GetFloat2Parameter(
                                            parameterIndex );
                                        if( rParameter.name == constantName )
                                        {
                                            rOutputStream.Seek( rConstantInfo.offset, SeekOrigins::Begin );
                                            rOutputStream.Write(
                                                &rParameter.value,
                                                sizeof( float32_t ),
                                                Min< size_t >( 2, rConstantInfo.size / sizeof( float32_t ) ) );

                                            break;
                                        }
                                    }

                                    if( parameterIndex >= float2ParameterCount )
                                    {
                                        for( parameterIndex = 0;
                                            parameterIndex < float3ParameterCount;
                                            ++parameterIndex )
                                        {
                                            const Material::Float3Parameter& rParameter = pMaterial->GetFloat3Parameter(
                                                parameterIndex );
                                            if( rParameter.name == constantName )
                                            {
                                                rOutputStream.Seek( rConstantInfo.offset, SeekOrigins::Begin );
                                                rOutputStream.Write(
                                                    &rParameter.value,
                                                    sizeof( float32_t ),
                                                    Min< size_t >( 3, rConstantInfo.size / sizeof( float32_t ) ) );

                                                break;
                                            }
                                        }

                                        if( parameterIndex >= float3ParameterCount )
                                        {
                                            for( parameterIndex = 0;
                                                parameterIndex < float4ParameterCount;
                                                ++parameterIndex )
                                            {
                                                const Material::Float4Parameter& rParameter =
                                                    pMaterial->GetFloat4Parameter( parameterIndex );
                                                if( rParameter.name == constantName )
                                                {
                                                    rOutputStream.Seek(
                                                        rConstantInfo.offset,
                                                        SeekOrigins::Begin );
                                                    rOutputStream.Write(
                                                        &rParameter.value,
                                                        sizeof( float32_t ),
                                                        Min< size_t >( 4, rConstantInfo.size / sizeof( float32_t ) ) );

                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            break;
                        }
                    }
                }
            }
        }
    }


    return !failedToWriteASubdata;
}