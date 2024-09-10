	void D3DShaderObjectProvider::find_locations()
	{
		sampler_locations.clear();
		texture_locations.clear();
		uniform_buffer_locations.clear();

		if (d3dcompiler_dll)	// If the compiler is available, we must use it! This ensures compatility with the blob
		{
			ComPtr<ID3D11ShaderReflection> reflect;
			HRESULT result = d3dreflect(bytecode.get_data(), bytecode.get_size(), IID_ID3D11ShaderReflection, (void**)reflect.output_variable());
			D3DTarget::throw_if_failed("D3DReflect failed", result);

			D3D11_SHADER_DESC desc;
			result = reflect->GetDesc(&desc);
			D3DTarget::throw_if_failed("D3DReflect.GetDesc failed", result);

			for (UINT i = 0; i < desc.BoundResources; i++)
			{
				D3D11_SHADER_INPUT_BIND_DESC binding;
				result = reflect->GetResourceBindingDesc(i, &binding);
				D3DTarget::throw_if_failed("D3DReflect.GetResourceBindingDesc failed", result);

				set_binding(binding);
			}
		}
		else
		{
			DXBC_Reflect reflect(bytecode.get_data(), bytecode.get_size());
			for (size_t cnt = 0; cnt < reflect.binding.size(); cnt++)
			{
				set_binding(reflect.binding[cnt]);
			}
		}

	}