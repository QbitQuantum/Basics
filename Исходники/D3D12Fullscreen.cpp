// Fill the command list with all the render commands and dependent state.
void D3D12Fullscreen::PopulateCommandLists()
{
	// Command list allocators can only be reset when the associated 
	// command lists have finished execution on the GPU; apps should use 
	// fences to determine GPU execution progress.
	ThrowIfFailed(m_sceneCommandAllocators[m_frameIndex]->Reset());
	ThrowIfFailed(m_postCommandAllocators[m_frameIndex]->Reset());

	// However, when ExecuteCommandList() is called on a particular command 
	// list, that command list can then be reset at any time and must be before 
	// re-recording.
	ThrowIfFailed(m_sceneCommandList->Reset(m_sceneCommandAllocators[m_frameIndex].Get(), m_scenePipelineState.Get()));
	ThrowIfFailed(m_postCommandList->Reset(m_postCommandAllocators[m_frameIndex].Get(), m_postPipelineState.Get()));

	// Populate m_sceneCommandList to render scene to intermediate render target.
	{
		// Set necessary state.
		m_sceneCommandList->SetGraphicsRootSignature(m_sceneRootSignature.Get());

		ID3D12DescriptorHeap* ppHeaps[] = { m_cbvSrvHeap.Get() };
		m_sceneCommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		CD3DX12_GPU_DESCRIPTOR_HANDLE cbvHandle(m_cbvSrvHeap->GetGPUDescriptorHandleForHeapStart(), m_frameIndex + 1, m_cbvSrvDescriptorSize);
		m_sceneCommandList->SetGraphicsRootDescriptorTable(0, cbvHandle);
		m_sceneCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_sceneCommandList->RSSetViewports(1, &m_sceneViewport);
		m_sceneCommandList->RSSetScissorRects(1, &m_sceneScissorRect);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), FrameCount, m_rtvDescriptorSize);
		m_sceneCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

		// Record commands.
		m_sceneCommandList->ClearRenderTargetView(rtvHandle, ClearColor, 0, nullptr);
		m_sceneCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_sceneCommandList->IASetVertexBuffers(0, 1, &m_sceneVertexBufferView);

		PIXBeginEvent(m_sceneCommandList.Get(), 0, L"Draw a thin rectangle");
		m_sceneCommandList->DrawInstanced(4, 1, 0, 0);
		PIXEndEvent(m_sceneCommandList.Get());
	}

	ThrowIfFailed(m_sceneCommandList->Close());

	// Populate m_postCommandList to scale intermediate render target to screen.
	{
		// Set necessary state.
		m_postCommandList->SetGraphicsRootSignature(m_postRootSignature.Get());

		ID3D12DescriptorHeap* ppHeaps[] = { m_cbvSrvHeap.Get() };
		m_postCommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		// Indicate that the back buffer will be used as a render target and the
		// intermediate render target will be used as a SRV.
		D3D12_RESOURCE_BARRIER barriers[] = {
			CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET),
			CD3DX12_RESOURCE_BARRIER::Transition(m_intermediateRenderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
		};

		m_postCommandList->ResourceBarrier(_countof(barriers), barriers);

		m_postCommandList->SetGraphicsRootDescriptorTable(0, m_cbvSrvHeap->GetGPUDescriptorHandleForHeapStart());
		m_postCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_postCommandList->RSSetViewports(1, &m_postViewport);
		m_postCommandList->RSSetScissorRects(1, &m_postScissorRect);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
		m_postCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

		// Record commands.
		m_postCommandList->ClearRenderTargetView(rtvHandle, LetterboxColor, 0, nullptr);
		m_postCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_postCommandList->IASetVertexBuffers(0, 1, &m_postVertexBufferView);

		PIXBeginEvent(m_postCommandList.Get(), 0, L"Draw texture to screen.");
		m_postCommandList->DrawInstanced(4, 1, 0, 0);
		PIXEndEvent(m_postCommandList.Get());

		// Revert resource states back to original values.
		barriers[0].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barriers[0].Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		barriers[1].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		barriers[1].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		m_postCommandList->ResourceBarrier(_countof(barriers), barriers);
	}

	ThrowIfFailed(m_postCommandList->Close());
}