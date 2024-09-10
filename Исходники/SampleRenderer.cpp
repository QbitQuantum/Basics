		void SampleRenderer::Initialize()
		{
			m_RenderQueue = new ::Dispatch::WorkQueue("RenderQueue", ::Concurrency::ThreadPriority::High);
			m_RenderQueue->Loop();
			isInitialized = false;

			float aspectRatio = 1900.f/700;
			float fovAngleY = 70.0f * XM_PI / 180.0f;

			if (aspectRatio < 1.0f)
			{
				fovAngleY *= 2.0f;
			}

			XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(fovAngleY, aspectRatio, 0.01f, 100.0f);
			XMStoreFloat4x4(&m_MVP.projection, XMMatrixTranspose(perspectiveMatrix));

			static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
			static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
			static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };
			XMStoreFloat4x4(&m_MVP.model, XMMatrixTranspose(XMMatrixRotationY(1.57)));
			XMStoreFloat4x4(&m_MVP.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

			auto d3dDevice = gD3DDevice->GetD3DDevice();


			CD3DX12_ROOT_PARAMETER parameter[3];

			CD3DX12_DESCRIPTOR_RANGE range;
			range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
			parameter[0].InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_VERTEX);

			CD3DX12_DESCRIPTOR_RANGE range2;
			range2.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
			parameter[1].InitAsDescriptorTable(1, &range2, D3D12_SHADER_VISIBILITY_PIXEL);

			CD3DX12_DESCRIPTOR_RANGE range3;
			range3.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, 0);
			parameter[2].InitAsDescriptorTable(1, &range3, D3D12_SHADER_VISIBILITY_PIXEL);

			D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

			CD3DX12_ROOT_SIGNATURE_DESC descRootSignature;
			descRootSignature.Init(3, parameter, 0, nullptr, rootSignatureFlags);

			PtrBlob pSignature, pError;
			ThrowIfFailed(D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, pSignature.GetInitReference(), pError.GetInitReference()));
			ThrowIfFailed(d3dDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(m_RootSignature.GetInitReference())));
			
			m_CopyQueue = new CopyQueue_tr(d3dDevice);
			m_CopyQueue->StartLoop();


			m_RenderQueue->Queue(::Dispatch::Bind([this, d3dDevice]() {
				m_VS.Load("/Data/Test/Test.vso");
				m_PS.Load("/Data/Test/Test.pso");

				static const D3D12_INPUT_ELEMENT_DESC inputLayout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
					{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				};

				D3D12_GRAPHICS_PIPELINE_STATE_DESC state = {};
				state.InputLayout = { inputLayout, _countof(inputLayout) };
				state.pRootSignature = m_RootSignature;
				state.VS = { m_VS.GetBlob()->GetBufferPointer(), m_VS.GetBlob()->GetBufferSize() };
				state.PS = { m_PS.GetBlob()->GetBufferPointer(), m_PS.GetBlob()->GetBufferSize() };
				state.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
				state.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
				state.DepthStencilState.DepthEnable = FALSE;
				state.DepthStencilState.StencilEnable = FALSE;
				state.SampleMask = UINT_MAX;
				state.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				state.NumRenderTargets = 1;
				state.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
				state.SampleDesc.Count = 1;

				ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&state, IID_PPV_ARGS(m_PipeLineState.GetInitReference())));

				LogUtil::Out("Renderer", ::Concurrency::Thread::GetCurrentThreadName());

			}));

			m_RenderQueue->Queue(::Dispatch::Bind([this, d3dDevice]() {
				ThrowIfFailed(d3dDevice->CreateCommandList(1, D3D12_COMMAND_LIST_TYPE_DIRECT, gD3DDevice->GetCommandAllocator(), m_PipeLineState, IID_PPV_ARGS(m_CmdList.GetInitReference())));

				D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
				heapDesc.NumDescriptors = DeviceManager::GetFrameCount();
				heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
				ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_CBVHeap.GetInitReference())));
				m_CBVHeap->SetName(L"Constant Buffer Heap");
				
				m_samplerHeap.Create(d3dDevice, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, 1, true);
				D3D12_SAMPLER_DESC samplerDesc = {};
				samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
				samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				samplerDesc.MipLODBias = 0.0f;
				samplerDesc.MaxAnisotropy = 1;
				samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
				samplerDesc.MinLOD = 0;
				samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
				d3dDevice->CreateSampler(&samplerDesc, m_samplerHeap.hCPU(0));

				m_CubeMesh = new CubeMesh(d3dDevice, m_CmdList);

				this->m_CopyQueue->SubmitTexture(L"\\Data\\Test\\seafloor2bc1.dds", m_CubeMesh);

				m_CBO = new UniformBuffer<ModelViewProjectionConstantBuffer>("ModeViewMatrix", d3dDevice, 1U);
				m_CBO->CreateOnHeap(m_CBVHeap, d3dDevice);

				m_ConstantBuffer = m_CBO->Map();
				ZeroMemory(m_ConstantBuffer, DeviceManager::GetFrameCount() * m_CBO->sAlignedConstantBufferSize);

				ThrowIfFailed(m_CmdList->Close());
				ID3D12CommandList* ppCommandLists[] = { m_CmdList };
				gD3DDevice->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
				gD3DDevice->WaitForGPU();

				isInitialized = true; 
			}));
		}