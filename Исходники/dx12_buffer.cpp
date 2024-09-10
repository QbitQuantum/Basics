	int BaseBuffer::Initialize(ID3D12Device& device, const GfxBufferDesc& desc)
	{
		D3D12_HEAP_PROPERTIES heapProperties = {};
		heapProperties.Type = GetDx12HeapType(desc.m_heapType);
		heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProperties.CreationNodeMask = 1;
		heapProperties.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Alignment = 0;
		resourceDesc.Width = desc.m_bufferSizeInByte;
		resourceDesc.Height = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.Flags = GetDx12ResourceFlags(desc.m_resourceFlags);
		
		D3D12_RESOURCE_STATES resourceState = GetDx12ResourceStates(desc.m_resourceStates);

		HRESULT hr = device.CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			resourceState,
			nullptr,
			IID_PPV_ARGS(&m_resource));
		if(FAILED(hr))
		{
			SI_ASSERT(0, "error device.CreateCommittedResource", _com_error(hr).ErrorMessage());
			return -1;
		}

		m_bufferSizeInByte = desc.m_bufferSizeInByte;
		m_location         = m_resource->GetGPUVirtualAddress();
		
		if(desc.m_name)
		{
			wchar_t wName[64];
			wName[0] = 0;
			size_t num = 0;
			errno_t ret = mbstowcs_s(&num, wName, desc.m_name, ArraySize(wName));
			if(ret == 0)
			{
				m_resource->SetName(wName);
			}
		}

		return 0;
	}