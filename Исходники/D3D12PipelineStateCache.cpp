// Fill the command list with all the render commands and dependent state.
void D3D12PipelineStateCache::PopulateCommandList()
{
	// Command list allocators can only be reset when the associated
	// command lists have finished execution on the GPU; apps should use
	// fences to determine GPU execution progress.
	ThrowIfFailed(m_commandAllocators[m_frameIndex]->Reset());

	// However, when ExecuteCommandList() is called on a particular command
	// list, that command list can then be reset at any time and must be before
	// re-recording.
	ThrowIfFailed(m_commandList->Reset(m_commandAllocators[m_frameIndex].Get(), nullptr));

	// Set necessary state.
	m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());

	ID3D12DescriptorHeap* ppHeaps[] = { m_srvHeap.Get() };
	m_commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_commandList->RSSetViewports(1, &m_viewport);
	m_commandList->RSSetScissorRects(1, &m_scissorRect);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE intermediateRtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), FrameCount, m_rtvDescriptorSize);
	CD3DX12_GPU_DESCRIPTOR_HANDLE srvHandle(m_srvHeap->GetGPUDescriptorHandleForHeapStart());

	m_commandList->OMSetRenderTargets(1, &intermediateRtvHandle, FALSE, nullptr);

	// Record commands.
	m_commandList->ClearRenderTargetView(intermediateRtvHandle, IntermediateClearColor, 0, nullptr);

	// Draw the scene as normal into the intermediate buffer.
	PIXBeginEvent(m_commandList.Get(), 0, L"Draw cube");
	{
		static float rot = 0.0f;
		DrawConstantBuffer* drawCB = (DrawConstantBuffer*)m_dynamicCB.GetMappedMemory(m_drawIndex, m_frameIndex);
		drawCB->worldViewProjection = XMMatrixTranspose(XMMatrixRotationY(rot) * XMMatrixRotationX(-rot) * m_camera.GetViewMatrix() * m_projectionMatrix);

		rot += 0.01f;

		m_commandList->IASetVertexBuffers(0, 1, &m_cubeVbv);
		m_commandList->IASetIndexBuffer(&m_cubeIbv);
		m_psoLibrary.SetPipelineState(m_device.Get(), m_rootSignature.Get(), m_commandList.Get(), BaseNormal3DRender, m_frameIndex);

		m_commandList->SetGraphicsRootConstantBufferView(RootParameterCB, m_dynamicCB.GetGpuVirtualAddress(m_drawIndex, m_frameIndex));
		m_commandList->DrawIndexedInstanced(36, 1, 0, 0, 0);
		m_drawIndex++;
	}
	PIXEndEvent(m_commandList.Get());

	// Set up the state for a fullscreen quad.
	m_commandList->IASetVertexBuffers(0, 1, &m_quadVbv);
	m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Indicate that the back buffer will be used as a render target and the
	// intermediate render target will be used as a SRV.
	D3D12_RESOURCE_BARRIER barriers[] = {
		CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET),
		CD3DX12_RESOURCE_BARRIER::Transition(m_intermediateRenderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
	};

	m_commandList->ResourceBarrier(_countof(barriers), barriers);
	m_commandList->SetGraphicsRootDescriptorTable(RootParameterSRV, m_srvHeap->GetGPUDescriptorHandleForHeapStart());

	const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_commandList->ClearRenderTargetView(rtvHandle, black, 0, nullptr);
	m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	// Draw some quads using the rendered scene with some effect shaders.
	PIXBeginEvent(m_commandList.Get(), 0, L"Post-processing");
	{
		UINT quadCount = 0;
		static const UINT quadsX = 3;
		static const UINT quadsY = 3;

		// Cycle through all of the effects.
		for (UINT i = PostBlit; i < EffectPipelineTypeCount; i++)
		{
			if (m_enabledEffects[i])
			{
				D3D12_VIEWPORT viewport = {};
				viewport.TopLeftX = (quadCount % quadsX) * (m_viewport.Width / quadsX);
				viewport.TopLeftY = (quadCount / quadsY) * (m_viewport.Height / quadsY);
				viewport.Width = m_viewport.Width / quadsX;
				viewport.Height = m_viewport.Height / quadsY;
				viewport.MinDepth = 0.0f;
				viewport.MaxDepth = 0.0f;

				PIXBeginEvent(m_commandList.Get(), 0, g_cEffectNames[i]);
				m_commandList->RSSetViewports(1, &viewport);
				m_psoLibrary.SetPipelineState(m_device.Get(), m_rootSignature.Get(), m_commandList.Get(), static_cast<EffectPipelineType>(i), m_frameIndex);
				m_commandList->DrawInstanced(4, 1, 0, 0);
				PIXEndEvent(m_commandList.Get());
			}

			quadCount++;
		}
	}
	PIXEndEvent(m_commandList.Get());

	// Revert resource states back to original values.
	barriers[0].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barriers[0].Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	barriers[1].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barriers[1].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	m_commandList->ResourceBarrier(_countof(barriers), barriers);

	ThrowIfFailed(m_commandList->Close());
}