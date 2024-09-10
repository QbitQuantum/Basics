// Load the sample assets.
void D3D12HeterogeneousMultiadapter::LoadAssets()
{
	// Create the root signatures.
	{
		CD3DX12_ROOT_PARAMETER rootParameters[2];
		rootParameters[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_VERTEX);
		rootParameters[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_PIXEL);

		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(_countof(rootParameters), rootParameters, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		ThrowIfFailed(m_devices[Primary]->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));

		CD3DX12_DESCRIPTOR_RANGE ranges[1];
		ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

		CD3DX12_ROOT_PARAMETER blurRootParameters[3];
		blurRootParameters[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_PIXEL);
		blurRootParameters[1].InitAsDescriptorTable(_countof(ranges), ranges, D3D12_SHADER_VISIBILITY_PIXEL);
		blurRootParameters[2].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_PIXEL);

		CD3DX12_STATIC_SAMPLER_DESC staticPointSampler(0);
		staticPointSampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		staticPointSampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		CD3DX12_STATIC_SAMPLER_DESC staticLinearSampler(1);
		staticLinearSampler.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		staticLinearSampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		D3D12_STATIC_SAMPLER_DESC staticSamplers[] = { staticPointSampler, staticLinearSampler };
		rootSignatureDesc.Init(_countof(blurRootParameters), blurRootParameters, _countof(staticSamplers), staticSamplers, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		ThrowIfFailed(m_devices[Secondary]->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_blurRootSignature)));
	}

	// Create the pipeline states, which includes compiling and loading shaders.
	{
		ComPtr<ID3DBlob> vertexShader;
		ComPtr<ID3DBlob> pixelShader;
		ComPtr<ID3DBlob> vertexShaderBlur;
		ComPtr<ID3DBlob> pixelShaderBlurU;
		ComPtr<ID3DBlob> pixelShaderBlurV;
		ComPtr<ID3DBlob> error;

#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif

		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"shaders.hlsl").c_str(), nullptr, nullptr, "VShader", "vs_5_0", compileFlags, 0, &vertexShader, &error));
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"shaders.hlsl").c_str(), nullptr, nullptr, "PShader", "ps_5_0", compileFlags, 0, &pixelShader, &error));

		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"blurShaders.hlsl").c_str(), nullptr, nullptr, "VSSimpleBlur", "vs_5_0", compileFlags, 0, &vertexShaderBlur, &error));
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"blurShaders.hlsl").c_str(), nullptr, nullptr, "PSSimpleBlurU", "ps_5_0", compileFlags, 0, &pixelShaderBlurU, &error));
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"blurShaders.hlsl").c_str(), nullptr, nullptr, "PSSimpleBlurV", "ps_5_0", compileFlags, 0, &pixelShaderBlurV, &error));

		// Define the vertex input layouts.
		const D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		const D3D12_INPUT_ELEMENT_DESC blurInputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		// Describe and create the graphics pipeline state objects (PSOs).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = m_rootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;
		ThrowIfFailed(m_devices[Primary]->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)));

		psoDesc.InputLayout = { blurInputElementDescs, _countof(blurInputElementDescs) };
		psoDesc.pRootSignature = m_blurRootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShaderBlur.Get());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShaderBlurU.Get());
		psoDesc.DepthStencilState.DepthEnable = false;
		psoDesc.DSVFormat = DXGI_FORMAT_UNKNOWN;
		ThrowIfFailed(m_devices[Secondary]->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_blurPipelineStates[0])));

		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShaderBlurV.Get());
		ThrowIfFailed(m_devices[Secondary]->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_blurPipelineStates[1])));
	}

	// Create the command lists.
	ThrowIfFailed(m_devices[Primary]->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_directCommandAllocators[Primary][m_frameIndex].Get(), m_pipelineState.Get(), IID_PPV_ARGS(&m_directCommandLists[Primary])));
	ThrowIfFailed(m_devices[Primary]->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COPY, m_copyCommandAllocators[m_frameIndex].Get(), m_pipelineState.Get(), IID_PPV_ARGS(&m_copyCommandList)));
	ThrowIfFailed(m_copyCommandList->Close());

	ThrowIfFailed(m_devices[Secondary]->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_directCommandAllocators[Secondary][m_frameIndex].Get(), m_blurPipelineStates[0].Get(), IID_PPV_ARGS(&m_directCommandLists[Secondary])));

	// Note: ComPtr's are CPU objects but these resources need to stay in scope until
	// the command list that references them has finished executing on the GPU.
	// We will flush the GPU at the end of this method to ensure the resources are not
	// prematurely destroyed.
	ComPtr<ID3D12Resource> vertexBufferUpload;
	ComPtr<ID3D12Resource> fullscreenQuadVertexBufferUpload;

	// Create the vertex buffer for the primary adapter.
	{
		// Define the geometry for a triangle.
		Vertex triangleVertices[] =
		{
			{ { 0.0f, TriangleHalfWidth, TriangleDepth } },
			{ { TriangleHalfWidth, -TriangleHalfWidth, TriangleDepth } },
			{ { -TriangleHalfWidth, -TriangleHalfWidth, TriangleDepth } }
		};

		const UINT vertexBufferSize = sizeof(triangleVertices);

		ThrowIfFailed(m_devices[Primary]->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)));

		ThrowIfFailed(m_devices[Primary]->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&vertexBufferUpload)));

		// Copy data to the intermediate upload heap and then schedule a copy
		// from the upload heap to the vertex buffer.
		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData = reinterpret_cast<UINT8*>(triangleVertices);
		vertexData.RowPitch = vertexBufferSize;
		vertexData.SlicePitch = vertexData.RowPitch;

		UpdateSubresources<1>(m_directCommandLists[Primary].Get(), m_vertexBuffer.Get(), vertexBufferUpload.Get(), 0, 0, 1, &vertexData);
		m_directCommandLists[Primary]->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

		// Initialize the vertex buffer view.
		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.StrideInBytes = sizeof(Vertex);
		m_vertexBufferView.SizeInBytes = sizeof(triangleVertices);
	}

	// Create the vertex buffer for the secondary adapter.
	{
		// Define the geometry for a fullscreen triangle.
		VertexPositionUV quadVertices[] =
		{
			{ { -1.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },	// Bottom left.
			{ { -1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },	// Top left.
			{ { 1.0f, -1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },	// Bottom right.
			{ { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },		// Top right.
		};

		const UINT vertexBufferSize = sizeof(quadVertices);

		ThrowIfFailed(m_devices[Secondary]->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&m_fullscreenQuadVertexBuffer)));

		ThrowIfFailed(m_devices[Secondary]->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&fullscreenQuadVertexBufferUpload)));

		// Copy data to the intermediate upload heap and then schedule a copy
		// from the upload heap to the vertex buffer.
		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData = reinterpret_cast<UINT8*>(quadVertices);
		vertexData.RowPitch = vertexBufferSize;
		vertexData.SlicePitch = vertexData.RowPitch;

		UpdateSubresources<1>(m_directCommandLists[Secondary].Get(), m_fullscreenQuadVertexBuffer.Get(), fullscreenQuadVertexBufferUpload.Get(), 0, 0, 1, &vertexData);
		m_directCommandLists[Secondary]->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_fullscreenQuadVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

		// Initialize the vertex buffer view.
		m_fullscreenQuadVertexBufferView.BufferLocation = m_fullscreenQuadVertexBuffer->GetGPUVirtualAddress();
		m_fullscreenQuadVertexBufferView.StrideInBytes = sizeof(VertexPositionUV);
		m_fullscreenQuadVertexBufferView.SizeInBytes = sizeof(quadVertices);
	}

	// Create the depth stencil view.
	{
		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

		const CD3DX12_CLEAR_VALUE clearValue(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

		ThrowIfFailed(m_devices[Primary]->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, m_width, m_height, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&clearValue,
			IID_PPV_ARGS(&m_depthStencil)
			));

		m_devices[Primary]->CreateDepthStencilView(m_depthStencil.Get(), &depthStencilDesc, m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
	}

	// Create the constant buffers.
	{
		{
			const UINT64 constantBufferSize = sizeof(ConstantBufferData) * MaxTriangleCount * FrameCount;

			ThrowIfFailed(m_devices[Primary]->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(constantBufferSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_constantBuffer)));

			// Setup constant buffer data.
			for (UINT n = 0; n < MaxTriangleCount; n++)
			{
				m_constantBufferData[n].velocity = XMFLOAT4(GetRandomFloat(0.01f, 0.02f), 0.0f, 0.0f, 0.0f);
				m_constantBufferData[n].offset = XMFLOAT4(GetRandomFloat(-5.0f, -1.5f), GetRandomFloat(-1.0f, 1.0f), GetRandomFloat(0.0f, 2.0f), 0.0f);
				m_constantBufferData[n].color = XMFLOAT4(GetRandomFloat(0.5f, 1.0f), GetRandomFloat(0.5f, 1.0f), GetRandomFloat(0.5f, 1.0f), 1.0f);
				XMStoreFloat4x4(&m_constantBufferData[n].projection, XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV4, m_aspectRatio, 0.01f, 20.0f)));
			}

			// Map the constant buffer. We don't unmap this until the app closes.
			// Keeping things mapped for the lifetime of the resource is okay.
			CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
			ThrowIfFailed(m_constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_pCbvDataBegin)));
			memcpy(m_pCbvDataBegin, &m_constantBufferData[0], constantBufferSize / FrameCount);
		}

		{
			const UINT64 workloadConstantBufferSize = sizeof(WorkloadConstantBufferData) * FrameCount;

			ThrowIfFailed(m_devices[Primary]->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(workloadConstantBufferSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_workloadConstantBuffer)));

			// Setup constant buffer data.
			m_workloadConstantBufferData.loopCount = m_psLoopCount;

			// Map the constant buffer. We don't unmap this until the app closes.
			// Keeping things mapped for the lifetime of the resource is okay.
			CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
			ThrowIfFailed(m_workloadConstantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_pWorkloadCbvDataBegin)));
			memcpy(m_pWorkloadCbvDataBegin, &m_workloadConstantBufferData, workloadConstantBufferSize / FrameCount);
		}

		{
			const UINT64 blurWorkloadConstantBufferSize = sizeof(WorkloadConstantBufferData) * FrameCount;

			ThrowIfFailed(m_devices[Secondary]->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(blurWorkloadConstantBufferSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_blurWorkloadConstantBuffer)));

			// Setup constant buffer data.
			m_blurWorkloadConstantBufferData.loopCount = m_blurPSLoopCount;

			// Map the constant buffer. We don't unmap this until the app closes.
			// Keeping things mapped for the lifetime of the resource is okay.
			CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
			ThrowIfFailed(m_blurWorkloadConstantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_pBlurWorkloadCbvDataBegin)));
			memcpy(m_pBlurWorkloadCbvDataBegin, &m_blurWorkloadConstantBufferData, blurWorkloadConstantBufferSize / FrameCount);
		}

		{
			ThrowIfFailed(m_devices[Secondary]->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(sizeof(BlurConstantBufferData)),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_blurConstantBuffer)));

			// Map the constant buffer.
			CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
			ThrowIfFailed(m_blurConstantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_pBlurCbvDataBegin)));

			// Setup constant buffer data.
			m_pBlurCbvDataBegin[0].offset = 0.5f;
			m_pBlurCbvDataBegin[0].textureDimensions.x = static_cast<float>(m_width);
			m_pBlurCbvDataBegin[0].textureDimensions.y = static_cast<float>(m_height);

			// Unmap the constant buffer because we don't update this again.
			// If we ever do, it should be buffered by the number of frames like other constant buffers.
			const CD3DX12_RANGE emptyRange(0, 0);
			m_blurConstantBuffer->Unmap(0, &emptyRange);
			m_pBlurCbvDataBegin = nullptr;
		}
	}

	// Close the command lists and execute them to begin the vertex buffer copies into the default heaps.
	for (UINT i = 0; i < GraphicsAdaptersCount; i++)
	{
		ThrowIfFailed(m_directCommandLists[i]->Close());
		ID3D12CommandList* ppCommandLists[] = { m_directCommandLists[i].Get() };
		m_directCommandQueues[i]->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	}

	// Create synchronization objects and wait until assets have been uploaded to the GPU.
	// We use a cross-adapter fence for handling Signals and Waits between adapters.
	// We use regular fences for things that don't need to be cross adapter because they don't need the additional overhead associated with being cross-adapter.
	{
		// Fence used to control CPU pacing.
		ThrowIfFailed(m_devices[Secondary]->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_frameFence)));

		// Fence used by the primary adapter to signal its copy queue that it has completed rendering.
		// When this is signaled, the primary adapter's copy queue can begin copying to the cross-adapter shared resource.
		ThrowIfFailed(m_devices[Primary]->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_renderFence)));	

		// Cross-adapter shared fence used by both adapters.
		// Used by the primary adapter to signal the secondary adapter that it has completed copying to the cross-adapter shared resource.
		// When this is signaled, the secondary adapter can begin its work.
		ThrowIfFailed(m_devices[Primary]->CreateFence(0, D3D12_FENCE_FLAG_SHARED | D3D12_FENCE_FLAG_SHARED_CROSS_ADAPTER, IID_PPV_ARGS(&m_crossAdapterFences[Primary]))); 

		// For now, require GENERIC_ALL access.
		HANDLE fenceHandle = nullptr;
		ThrowIfFailed(m_devices[Primary]->CreateSharedHandle(
			m_crossAdapterFences[Primary].Get(),
			nullptr,
			GENERIC_ALL,
			nullptr,
			&fenceHandle));

		HRESULT openSharedHandleResult = m_devices[Secondary]->OpenSharedHandle(fenceHandle, IID_PPV_ARGS(&m_crossAdapterFences[Secondary]));

		// We can close the handle after opening the cross-adapter shared fence.
		CloseHandle(fenceHandle);

		ThrowIfFailed(openSharedHandleResult);

		for (UINT i = 0; i < GraphicsAdaptersCount; i++)
		{
			// Create an event handle to use for frame synchronization.
			m_fenceEvents[i] = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);
			if (m_fenceEvents == nullptr)
			{
				ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
			}

			// Wait for the command list to execute; we are reusing the same command 
			// list in our main loop but for now, we just want to wait for setup to 
			// complete before continuing.
			WaitForGpu(static_cast<GraphicsAdapter>(i));
		}
	}
}