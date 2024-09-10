	bool D3DShaderObject::try_compile()
	{
		shader.clear();
		info_log_text.clear();

		if (!bytecode)
		{
			load_compiler_dll();

			std::string entry_point = "main";
			std::string shader_model = get_shader_model();

			ComPtr<ID3DBlob> blob;
			ComPtr<ID3DBlob> log;
			HRESULT result = d3dcompile(
				source.data(),
				source.length(),
				0,
				0,
				0,
				entry_point.c_str(),
				shader_model.c_str(),
				D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_OPTIMIZATION_LEVEL3,
				0,
				blob.output_variable(),
				log.output_variable());

			if (log)
				info_log_text = std::string(reinterpret_cast<char*>(log->GetBufferPointer()), log->GetBufferSize());

			if (SUCCEEDED(result))
			{
				bytecode = DataBuffer::create(blob->GetBufferPointer(), blob->GetBufferSize());
			}
			else
			{
				return false;
			}
		}

		try
		{
			create_shader();
			find_locations();
			return true;
		}
		catch (Exception &e)
		{
			if (!info_log_text.empty())
				info_log_text += "\r\n";
			info_log_text += e.message;
			return false;
		}
	}