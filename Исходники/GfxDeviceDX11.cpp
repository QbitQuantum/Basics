    static void dx11_fill_constant_table(ShaderConstantTable& out_constants, ShaderConstantTable& out_samplers, const ShaderCode& bytecode)
    {
        out_constants.clear();
        out_samplers.clear();

        ID3D11ShaderReflection* refl = NULL; 
        D3DReflect( bytecode.data(), bytecode.size(), IID_ID3D11ShaderReflection, (void**)&refl);

        if( refl )
        {
            HRESULT hr = S_OK;
            D3D11_SHADER_DESC refl_desc;
            hr = refl->GetDesc(&refl_desc);

            for( uint32 i=0; i<refl_desc.ConstantBuffers; ++i )
            {
                ID3D11ShaderReflectionConstantBuffer* cb = refl->GetConstantBufferByIndex(i);

                D3D11_SHADER_BUFFER_DESC sb_desc;
                cb->GetDesc(&sb_desc);

                for( uint32 j=0; j<sb_desc.Variables; ++j )
                {
                    ID3D11ShaderReflectionVariable* var = cb->GetVariableByIndex(j);
                    D3D11_SHADER_VARIABLE_DESC var_desc;
                    var->GetDesc(&var_desc);

                    ShaderConstantDescr scd;
                    scd.name = var_desc.Name;
                    scd.register_index = var_desc.StartOffset/16;
                    scd.register_count = var_desc.Size/16;

                    out_constants.push_back(scd);
                }
            }

            for( uint32 i=0; i<refl_desc.BoundResources; ++i )
            {
                D3D11_SHADER_INPUT_BIND_DESC desc;
                refl->GetResourceBindingDesc(i, &desc);
                if( desc.Type == D3D10_SIT_SAMPLER )
                {
                    ShaderConstantDescr scd;
                    scd.name = desc.Name;
                    scd.register_index = desc.BindPoint;
                    scd.register_count = desc.BindCount;
                }
            }

            refl->Release();
        }
    }