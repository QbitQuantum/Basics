	void overlay::init_buffers(int window_width, int window_height)
	{
		D3D11_BUFFER_DESC vertex_desc, index_desc, const_desc;
		D3D11_SUBRESOURCE_DATA vertex_data, index_data;

		std::array<overlay::vertex_t, 6> vertices;
		std::array<uint32_t, 6> indices;

		zero_memory(vertex_desc);
		zero_memory(index_desc);
		zero_memory(const_desc);
		zero_memory(vertex_data);
		zero_memory(index_data);
		zero_memory(vertices);

		auto device = d3d_device::instance()->raw();
		auto context = d3d_device::instance()->get_context();

		for (uint32_t i = 0; i < vertex_count; i++)
			indices[i] = i;

		vertex_desc.Usage = D3D11_USAGE_DYNAMIC;
		vertex_desc.ByteWidth = sizeof(overlay::vertex_t) * vertex_count;
		vertex_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertex_data.pSysMem = vertices.data();

		index_desc.ByteWidth = sizeof(uint32_t) * vertex_count;
		index_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_data.pSysMem = indices.data();

		const_desc.ByteWidth = sizeof(overlay::matrix_t);
		const_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		device->CreateBuffer(&vertex_desc, &vertex_data, &vertex_buffer);
		device->CreateBuffer(&index_desc, &index_data, &index_buffer);
		device->CreateBuffer(&const_desc, nullptr, &const_buffer);

		overlay::matrix_t matrix_buffer;

		cxmatrix world = XMMatrixIdentity();
		cxmatrix view = XMMatrixLookAtLH(XMVectorZero(), XMVectorSet(0.f, 0.f, 1.f, 0.f), XMVectorSet(0.f, 1.f, 0.f, 0.f));
		cxmatrix ortho = XMMatrixOrthographicLH(static_cast<float>(window_width), static_cast<float>(window_height), 0.1f, 1000.f);

		XMStoreFloat4x4(&matrix_buffer.world, XMMatrixTranspose(world));
		XMStoreFloat4x4(&matrix_buffer.view, XMMatrixTranspose(view));
		XMStoreFloat4x4(&matrix_buffer.ortho, XMMatrixTranspose(ortho));

		context->UpdateSubresource(const_buffer.Get(), 0, nullptr, &matrix_buffer, 0, 0);
	}