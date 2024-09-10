// Fill the command list with all the render commands and dependent state.
void D3D12ExecuteIndirect::PopulateCommandLists()
{
	// Command list allocators can only be reset when the associated 
	// command lists have finished execution on the GPU; apps should use 
	// fences to determine GPU execution progress.
	ThrowIfFailed(m_computeCommandAllocators[m_frameIndex]->Reset());
	ThrowIfFailed(m_commandAllocators[m_frameIndex]->Reset());

	// However, when ExecuteCommandList() is called on a particular command 
	// list, that command list can then be reset at any time and must be before 
	// re-recording.
	ThrowIfFailed(m_computeCommandList->Reset(m_computeCommandAllocators[m_frameIndex].Get(), m_computeState.Get()));
	ThrowIfFailed(m_commandList->Reset(m_commandAllocators[m_frameIndex].Get(), m_pipelineState.Get()));

	// Record the compute commands that will cull triangles and prevent them from being processed by the vertex shader.
	if (m_enableCulling)
	{
		UINT frameDescriptorOffset = m_frameIndex * CbvSrvUavDescriptorCountPerFrame;
		D3D12_GPU_DESCRIPTOR_HANDLE cbvSrvUavHandle = m_cbvSrvUavHeap->GetGPUDescriptorHandleForHeapStart();

		m_computeCommandList->SetComputeRootSignature(m_computeRootSignature.Get());

		ID3D12DescriptorHeap* ppHeaps[] = { m_cbvSrvUavHeap.Get() };
		m_computeCommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		m_computeCommandList->SetComputeRootDescriptorTable(
			SrvUavTable,
			CD3DX12_GPU_DESCRIPTOR_HANDLE(cbvSrvUavHandle, CbvSrvOffset + frameDescriptorOffset, m_cbvSrvUavDescriptorSize));

		m_computeCommandList->SetComputeRoot32BitConstants(RootConstants, 4, reinterpret_cast<void*>(&m_csRootConstants), 0);

		// Reset the UAV counter for this frame.
		m_computeCommandList->CopyBufferRegion(m_processedCommandBuffers[m_frameIndex].Get(), CommandBufferCounterOffset, m_processedCommandBufferCounterReset.Get(), 0, sizeof(UINT));

		D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_processedCommandBuffers[m_frameIndex].Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
		m_computeCommandList->ResourceBarrier(1, &barrier);

		m_computeCommandList->Dispatch(static_cast<UINT>(ceil(TriangleCount / float(ComputeThreadBlockSize))), 1, 1);
	}

	ThrowIfFailed(m_computeCommandList->Close());

	// Record the rendering commands.
	{
		// Set necessary state.
		m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());

		ID3D12DescriptorHeap* ppHeaps[] = { m_cbvSrvUavHeap.Get() };
		m_commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		m_commandList->RSSetViewports(1, &m_viewport);
		m_commandList->RSSetScissorRects(1, m_enableCulling ? &m_cullingScissorRect : &m_scissorRect);

		// Indicate that the command buffer will be used for indirect drawing
		// and that the back buffer will be used as a render target.
		D3D12_RESOURCE_BARRIER barriers[2] = {
			CD3DX12_RESOURCE_BARRIER::Transition(
				m_enableCulling ? m_processedCommandBuffers[m_frameIndex].Get() : m_commandBuffer.Get(),
				m_enableCulling ? D3D12_RESOURCE_STATE_UNORDERED_ACCESS : D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
				D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT),
			CD3DX12_RESOURCE_BARRIER::Transition(
				m_renderTargets[m_frameIndex].Get(),
				D3D12_RESOURCE_STATE_PRESENT,
				D3D12_RESOURCE_STATE_RENDER_TARGET)
		};

		m_commandList->ResourceBarrier(_countof(barriers), barriers);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
		m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		// Record commands.
		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		m_commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);

		if (m_enableCulling)
		{
			PIXBeginEvent(m_commandList.Get(), 0, L"Draw visible triangles");

			// Draw the triangles that have not been culled.
			m_commandList->ExecuteIndirect(
				m_commandSignature.Get(),
				TriangleCount,
				m_processedCommandBuffers[m_frameIndex].Get(),
				0,
				m_processedCommandBuffers[m_frameIndex].Get(),
				CommandBufferCounterOffset);
		}
		else
		{
			PIXBeginEvent(m_commandList.Get(), 0, L"Draw all triangles");

			// Draw all of the triangles.
			m_commandList->ExecuteIndirect(
				m_commandSignature.Get(),
				TriangleCount,
				m_commandBuffer.Get(),
				CommandSizePerFrame * m_frameIndex,
				nullptr,
				0);
		}
		PIXEndEvent(m_commandList.Get());

		// Indicate that the command buffer may be used by the compute shader
		// and that the back buffer will now be used to present.
		barriers[0].Transition.StateBefore = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
		barriers[0].Transition.StateAfter = m_enableCulling ? D3D12_RESOURCE_STATE_COPY_DEST : D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		barriers[1].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barriers[1].Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

		m_commandList->ResourceBarrier(_countof(barriers), barriers);

		ThrowIfFailed(m_commandList->Close());
	}
}