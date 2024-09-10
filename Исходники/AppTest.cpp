void AppTest::PopulateCommandListAsync(uint32_t threadID)
{
	CommandAllocatorArray[threadID]->Reset();

	CommandListArray[threadID]->Reset(CommandAllocatorArray[threadID].Get(), PSO.Get());

	Matrix4 view = Matrix4::LookAt(Vector3(0.0f, 6.0f, 2.0f), Vector3(), Vector3(0.0f, 1.0f, 0.0f));
	Matrix4 proj = Matrix4::Perspective(Math::PiOver4, 1280.0f / 720.0f, 0.1f, 1000.0f);

	XMMATRIX viewXM = XMMatrixLookAtRH(XMVectorSet(0.0f, 20.0f, 50.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	XMMATRIX projXM = XMMatrixPerspectiveFovRH(Math::PiOver4, 1280.0f / 720.0f, 1.0f, 10000.0f);

	//Update constant buffer
	CBPerObject perObject;

	void* cbUploadPtr = nullptr;

	const unsigned int start = threadID * (BoxCount / ThreadCount);
	const unsigned int end = start + (BoxCount / ThreadCount);

	//Update the constant buffer view transforms for each object
	for (unsigned int i = start; i < end; i++)
	{
		const float scale = 0.04f * static_cast<float>(i);
		const float timeOffset = 1000.0f;
		const float timeMultiplier = 0.001f;

		XMMATRIX world, invTranspose, worldView, worldViewProj;
		world = XMMatrixScaling(scale, scale, scale) * 
			XMMatrixTranslation(static_cast<float>(i), 0.0f, 0.0f) * 
			XMMatrixRotationY(-static_cast<float>((Timer.GetTotalTime() + timeOffset) * static_cast<float>(i)) * timeMultiplier) * 
			XMMatrixScaling(0.01f, 0.01f, 0.01f);

		worldView = world * viewXM;
		worldViewProj = worldView * projXM;

		memcpy_s(&perObject.World, sizeof(perObject.World), &world, sizeof(world));
		memcpy_s(&perObject.WorldViewProj, sizeof(perObject.WorldViewProj), &worldViewProj, sizeof(worldViewProj));

		//Update the constant buffer data for specified object
		cbUploadPtr = PerObjectConstantBuffers.Map(i);
		memcpy_s(cbUploadPtr, sizeof(CBPerObject), &perObject, sizeof(perObject));
		PerObjectConstantBuffers.Unmap(i);
	}

	if (!UseRootLevelCBV)
	{
		ID3D12DescriptorHeap* descriptorHeap = ConstantBufferDescriptorHeap->GetBaseHeap();
		CommandListArray[threadID]->SetDescriptorHeaps(1, &descriptorHeap);
	}

	CommandListArray[threadID]->SetGraphicsRootSignature(RootSignature.Get());

	CommandListArray[threadID]->RSSetViewports(1, &Viewport);
	CommandListArray[threadID]->RSSetScissorRects(1, &RectScissor);

	SetResourceBarrier(CommandListArray[threadID].Get(), RenderTarget.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	CommandListArray[threadID]->OMSetRenderTargets(1, &DescriptorHeap->GetCPUDescriptorHandleForHeapStart(), true, &DSVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	CommandListArray[threadID]->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CommandListArray[threadID]->IASetVertexBuffers(0, 1, &DescViewBufVert);
	CommandListArray[threadID]->IASetIndexBuffer(&DescViewBufIndex);

	D3D12_GPU_DESCRIPTOR_HANDLE descriptorHandle;
	
	if (!UseBundles)
	{
		if (UseRootLevelCBV)
		{
			for (unsigned int i = start; i < end; i++)
			{
				CommandListArray[threadID]->SetGraphicsRootConstantBufferView(0, PerObjectConstantBuffers.GetGPUHandle(i));
				CommandListArray[threadID]->DrawIndexedInstanced(IndexCount, 1, 0, 0, 0);
			}
		}
		else
		{
			for (unsigned int i = start; i < end; i++)
			{
				descriptorHandle.ptr = ConstantBufferDescriptorHeap->GetDescriptorGPUHandle(i);
				CommandListArray[threadID]->SetGraphicsRootDescriptorTable(0, descriptorHandle);
				CommandListArray[threadID]->DrawIndexedInstanced(IndexCount, 1, 0, 0, 0);
			}
		}
	}
	else
	{
		const unsigned int bundleStart = (BundleCount / ThreadCount) * threadID;
		const unsigned int bundleEnd = bundleStart + BundleCount / ThreadCount;

		for (unsigned int i = bundleStart; i < bundleEnd; i++)
		{
			CommandListArray[threadID]->ExecuteBundle(CommandBundleArray[i].Get());
		}
	}

	SetResourceBarrier(CommandListArray[threadID].Get(), RenderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	CommandListArray[threadID]->Close();
}