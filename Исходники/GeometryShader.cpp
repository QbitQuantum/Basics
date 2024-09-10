	GeometryShader	&GeometryShader::operator=( GeometryShader const& shader )
	{
		if (this != &shader)
		{
			memory::SafeRelease(&m_bytecode);
			memory::SafeRelease(&m_shader);

			m_name = shader.m_name;

			D3DCreateBlob(shader.m_bytecode->GetBufferSize(), &m_bytecode);
			memcpy(m_bytecode->GetBufferPointer(), shader.m_bytecode->GetBufferPointer(), m_bytecode->GetBufferSize());
			g_renderer.GetDevice()->CreateGeometryShader(m_bytecode->GetBufferPointer(), m_bytecode->GetBufferSize(), 0, &m_shader);
		}
		return *this;
	}